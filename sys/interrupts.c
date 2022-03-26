#include <sys/interrupts.h>
#include <sys/ports.h>
#include <io.h>

struct idt_entry {
    uint16_t offset_lo;
    uint16_t cs;
    uint8_t ist;        
    uint8_t type;
    uint16_t offset_mid;
    uint32_t offset_hi;
    uint32_t zero_32;
} __attribute((packed));

struct idt_reg {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256

static struct idt_entry idt[IDT_ENTRIES];
struct idt_reg idtr;

typedef void (*int_handler_t)(struct regs_t*);
static int_handler_t handlers[IDT_ENTRIES];

static void set_entry(int idx, size_t handler) {
    uint16_t low    = (uint16_t)(handler >> 0);
    uint32_t mid    = (uint16_t)(handler >> 16);
    uint64_t high   = (uint64_t)(handler >> 32);

    idt[idx].offset_lo  = low;
    idt[idx].cs         = 0x8;
    idt[idx].ist        = 0;
    idt[idx].type       = 0b10001110;
    idt[idx].offset_mid = mid;
    idt[idx].offset_hi  = high;
}

static void load_idt() {
    idtr.limit = IDT_ENTRIES * sizeof(struct idt_entry) - 1;
    idtr.base = (uint64_t)&idt;

    asm volatile("lidt %0" :: "m"(idtr));
}

static char* exceptions[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(struct regs_t* regs) {
    #undef __MODULE__
    #define __MODULE__ "err"

    if (regs->int_no >= 32) {
        if (handlers[regs->int_no]) {
            handlers[regs->int_no](regs);
        }
    } else {
        asm volatile("cli");

        size_t cr2 = 0;
        asm volatile("mov %%cr2, %0"
                    : 
                    "=a"(cr2));

        size_t off;
        char* name = trace_addr(&off, regs->rip);

        ERR("%s (int %#lx, <%s+%#lx>, e=%u)\n",
            exceptions[regs->int_no],
            regs->int_no,
            name, off,
            regs->err_code);

        ERR("\trax: %#16lx     r8:  %#16lx\n",
            regs->rax,
            regs->r8);
        ERR("\trbx: %#16lx     r9:  %#16lx\n",
            regs->rbx,
            regs->r9);
        ERR("\trcx: %#16lx     r10: %#16lx\n",
            regs->rcx,
            regs->r10);
        ERR("\trdx: %#16lx     r11: %#16lx\n",
            regs->rdx,
            regs->r11);
        ERR("\trsp: %#16lx     r12: %#16lx\n",
            regs->rsp,
            regs->r12);
        ERR("\trbp: %#16lx     r13: %#16lx\n",
            regs->rbp,
            regs->r13);
        ERR("\trsi: %#16lx     r14: %#16lx\n",
            regs->rsi,
            regs->r14);
        ERR("\trdi: %#16lx     r15: %#16lx\n",
            regs->rdi,
            regs->r15);
        ERR("\trip: %#16lx     cr2: %#16lx\n",
            regs->rip,
            cr2);

        stacktrace(regs->rbp);

        struct color_t bg = {252, 90, 75};
        clear_screen(&bg);
        
        asm volatile("hlt");
    }

    x2apic_write(0xb0, 0); // EOI
}

void register_handler(uint8_t int_no, int_handler_t handler) {
    handlers[int_no] = handler;
}

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();
extern void isr48();
extern void isr49();
extern void isr50();
extern void isr51();
extern void isr52();
extern void isr53();
extern void isr54();
extern void isr55();
extern void isr56();
extern void isr57();
extern void isr58();
extern void isr59();
extern void isr60();
extern void isr61();
extern void isr62();
extern void isr63();
extern void isr64();
extern void isr65();
extern void isr66();
extern void isr67();
extern void isr68();
extern void isr69();
extern void isr70();
extern void isr71();
extern void isr72();
extern void isr73();
extern void isr74();
extern void isr75();
extern void isr76();
extern void isr77();
extern void isr78();
extern void isr79();
extern void isr80();
extern void isr81();
extern void isr82();
extern void isr83();
extern void isr84();
extern void isr85();
extern void isr86();
extern void isr87();
extern void isr88();
extern void isr89();
extern void isr90();
extern void isr91();
extern void isr92();
extern void isr93();
extern void isr94();
extern void isr95();
extern void isr96();
extern void isr97();
extern void isr98();
extern void isr99();
extern void isr100();
extern void isr101();
extern void isr102();
extern void isr103();
extern void isr104();
extern void isr105();
extern void isr106();
extern void isr107();
extern void isr108();
extern void isr109();
extern void isr110();
extern void isr111();
extern void isr112();
extern void isr113();
extern void isr114();
extern void isr115();
extern void isr116();
extern void isr117();
extern void isr118();
extern void isr119();
extern void isr120();
extern void isr121();
extern void isr122();
extern void isr123();
extern void isr124();
extern void isr125();
extern void isr126();
extern void isr127();
extern void isr128();
extern void isr129();
extern void isr130();
extern void isr131();
extern void isr132();
extern void isr133();
extern void isr134();
extern void isr135();
extern void isr136();
extern void isr137();
extern void isr138();
extern void isr139();
extern void isr140();
extern void isr141();
extern void isr142();
extern void isr143();
extern void isr144();
extern void isr145();
extern void isr146();
extern void isr147();
extern void isr148();
extern void isr149();
extern void isr150();
extern void isr151();
extern void isr152();
extern void isr153();
extern void isr154();
extern void isr155();
extern void isr156();
extern void isr157();
extern void isr158();
extern void isr159();
extern void isr160();
extern void isr161();
extern void isr162();
extern void isr163();
extern void isr164();
extern void isr165();
extern void isr166();
extern void isr167();
extern void isr168();
extern void isr169();
extern void isr170();
extern void isr171();
extern void isr172();
extern void isr173();
extern void isr174();
extern void isr175();
extern void isr176();
extern void isr177();
extern void isr178();
extern void isr179();
extern void isr180();
extern void isr181();
extern void isr182();
extern void isr183();
extern void isr184();
extern void isr185();
extern void isr186();
extern void isr187();
extern void isr188();
extern void isr189();
extern void isr190();
extern void isr191();
extern void isr192();
extern void isr193();
extern void isr194();
extern void isr195();
extern void isr196();
extern void isr197();
extern void isr198();
extern void isr199();
extern void isr200();
extern void isr201();
extern void isr202();
extern void isr203();
extern void isr204();
extern void isr205();
extern void isr206();
extern void isr207();
extern void isr208();
extern void isr209();
extern void isr210();
extern void isr211();
extern void isr212();
extern void isr213();
extern void isr214();
extern void isr215();
extern void isr216();
extern void isr217();
extern void isr218();
extern void isr219();
extern void isr220();
extern void isr221();
extern void isr222();
extern void isr223();
extern void isr224();
extern void isr225();
extern void isr226();
extern void isr227();
extern void isr228();
extern void isr229();
extern void isr230();
extern void isr231();
extern void isr232();
extern void isr233();
extern void isr234();
extern void isr235();
extern void isr236();
extern void isr237();
extern void isr238();
extern void isr239();
extern void isr240();
extern void isr241();
extern void isr242();
extern void isr243();
extern void isr244();
extern void isr245();
extern void isr246();
extern void isr247();
extern void isr248();
extern void isr249();
extern void isr250();
extern void isr251();
extern void isr252();
extern void isr253();
extern void isr254();
extern void isr255();

void init_isrs() {
    set_entry(0, (uint64_t)isr0);
    set_entry(1, (uint64_t)isr1);
    set_entry(2, (uint64_t)isr2);
    set_entry(3, (uint64_t)isr3);
    set_entry(4, (uint64_t)isr4);
    set_entry(5, (uint64_t)isr5);
    set_entry(6, (uint64_t)isr6);
    set_entry(7, (uint64_t)isr7);
    set_entry(8, (uint64_t)isr8);
    set_entry(9, (uint64_t)isr9);
    set_entry(10, (uint64_t)isr10);
    set_entry(11, (uint64_t)isr11);
    set_entry(12, (uint64_t)isr12);
    set_entry(13, (uint64_t)isr13);
    set_entry(14, (uint64_t)isr14);
    set_entry(15, (uint64_t)isr15);
    set_entry(16, (uint64_t)isr16);
    set_entry(17, (uint64_t)isr17);
    set_entry(18, (uint64_t)isr18);
    set_entry(19, (uint64_t)isr19);
    set_entry(20, (uint64_t)isr20);
    set_entry(21, (uint64_t)isr21);
    set_entry(22, (uint64_t)isr22);
    set_entry(23, (uint64_t)isr23);
    set_entry(24, (uint64_t)isr24);
    set_entry(25, (uint64_t)isr25);
    set_entry(26, (uint64_t)isr26);
    set_entry(27, (uint64_t)isr27);
    set_entry(28, (uint64_t)isr28);
    set_entry(29, (uint64_t)isr29);
    set_entry(30, (uint64_t)isr30);
    set_entry(31, (uint64_t)isr31);
    set_entry(32, (uint64_t)isr32);
    set_entry(33, (uint64_t)isr33);
    set_entry(34, (uint64_t)isr34);
    set_entry(35, (uint64_t)isr35);
    set_entry(36, (uint64_t)isr36);
    set_entry(37, (uint64_t)isr37);
    set_entry(38, (uint64_t)isr38);
    set_entry(39, (uint64_t)isr39);
    set_entry(40, (uint64_t)isr40);
    set_entry(41, (uint64_t)isr41);
    set_entry(42, (uint64_t)isr42);
    set_entry(43, (uint64_t)isr43);
    set_entry(44, (uint64_t)isr44);
    set_entry(45, (uint64_t)isr45);
    set_entry(46, (uint64_t)isr46);
    set_entry(47, (uint64_t)isr47);
    set_entry(48, (uint64_t)isr48);
    set_entry(49, (uint64_t)isr49);
    set_entry(50, (uint64_t)isr50);
    set_entry(51, (uint64_t)isr51);
    set_entry(52, (uint64_t)isr52);
    set_entry(53, (uint64_t)isr53);
    set_entry(54, (uint64_t)isr54);
    set_entry(55, (uint64_t)isr55);
    set_entry(56, (uint64_t)isr56);
    set_entry(57, (uint64_t)isr57);
    set_entry(58, (uint64_t)isr58);
    set_entry(59, (uint64_t)isr59);
    set_entry(60, (uint64_t)isr60);
    set_entry(61, (uint64_t)isr61);
    set_entry(62, (uint64_t)isr62);
    set_entry(63, (uint64_t)isr63);
    set_entry(64, (uint64_t)isr64);
    set_entry(65, (uint64_t)isr65);
    set_entry(66, (uint64_t)isr66);
    set_entry(67, (uint64_t)isr67);
    set_entry(68, (uint64_t)isr68);
    set_entry(69, (uint64_t)isr69);
    set_entry(70, (uint64_t)isr70);
    set_entry(71, (uint64_t)isr71);
    set_entry(72, (uint64_t)isr72);
    set_entry(73, (uint64_t)isr73);
    set_entry(74, (uint64_t)isr74);
    set_entry(75, (uint64_t)isr75);
    set_entry(76, (uint64_t)isr76);
    set_entry(77, (uint64_t)isr77);
    set_entry(78, (uint64_t)isr78);
    set_entry(79, (uint64_t)isr79);
    set_entry(80, (uint64_t)isr80);
    set_entry(81, (uint64_t)isr81);
    set_entry(82, (uint64_t)isr82);
    set_entry(83, (uint64_t)isr83);
    set_entry(84, (uint64_t)isr84);
    set_entry(85, (uint64_t)isr85);
    set_entry(86, (uint64_t)isr86);
    set_entry(87, (uint64_t)isr87);
    set_entry(88, (uint64_t)isr88);
    set_entry(89, (uint64_t)isr89);
    set_entry(90, (uint64_t)isr90);
    set_entry(91, (uint64_t)isr91);
    set_entry(92, (uint64_t)isr92);
    set_entry(93, (uint64_t)isr93);
    set_entry(94, (uint64_t)isr94);
    set_entry(95, (uint64_t)isr95);
    set_entry(96, (uint64_t)isr96);
    set_entry(97, (uint64_t)isr97);
    set_entry(98, (uint64_t)isr98);
    set_entry(99, (uint64_t)isr99);
    set_entry(100, (uint64_t)isr100);
    set_entry(101, (uint64_t)isr101);
    set_entry(102, (uint64_t)isr102);
    set_entry(103, (uint64_t)isr103);
    set_entry(104, (uint64_t)isr104);
    set_entry(105, (uint64_t)isr105);
    set_entry(106, (uint64_t)isr106);
    set_entry(107, (uint64_t)isr107);
    set_entry(108, (uint64_t)isr108);
    set_entry(109, (uint64_t)isr109);
    set_entry(110, (uint64_t)isr110);
    set_entry(111, (uint64_t)isr111);
    set_entry(112, (uint64_t)isr112);
    set_entry(113, (uint64_t)isr113);
    set_entry(114, (uint64_t)isr114);
    set_entry(115, (uint64_t)isr115);
    set_entry(116, (uint64_t)isr116);
    set_entry(117, (uint64_t)isr117);
    set_entry(118, (uint64_t)isr118);
    set_entry(119, (uint64_t)isr119);
    set_entry(120, (uint64_t)isr120);
    set_entry(121, (uint64_t)isr121);
    set_entry(122, (uint64_t)isr122);
    set_entry(123, (uint64_t)isr123);
    set_entry(124, (uint64_t)isr124);
    set_entry(125, (uint64_t)isr125);
    set_entry(126, (uint64_t)isr126);
    set_entry(127, (uint64_t)isr127);
    set_entry(128, (uint64_t)isr128);
    set_entry(129, (uint64_t)isr129);
    set_entry(130, (uint64_t)isr130);
    set_entry(131, (uint64_t)isr131);
    set_entry(132, (uint64_t)isr132);
    set_entry(133, (uint64_t)isr133);
    set_entry(134, (uint64_t)isr134);
    set_entry(135, (uint64_t)isr135);
    set_entry(136, (uint64_t)isr136);
    set_entry(137, (uint64_t)isr137);
    set_entry(138, (uint64_t)isr138);
    set_entry(139, (uint64_t)isr139);
    set_entry(140, (uint64_t)isr140);
    set_entry(141, (uint64_t)isr141);
    set_entry(142, (uint64_t)isr142);
    set_entry(143, (uint64_t)isr143);
    set_entry(144, (uint64_t)isr144);
    set_entry(145, (uint64_t)isr145);
    set_entry(146, (uint64_t)isr146);
    set_entry(147, (uint64_t)isr147);
    set_entry(148, (uint64_t)isr148);
    set_entry(149, (uint64_t)isr149);
    set_entry(150, (uint64_t)isr150);
    set_entry(151, (uint64_t)isr151);
    set_entry(152, (uint64_t)isr152);
    set_entry(153, (uint64_t)isr153);
    set_entry(154, (uint64_t)isr154);
    set_entry(155, (uint64_t)isr155);
    set_entry(156, (uint64_t)isr156);
    set_entry(157, (uint64_t)isr157);
    set_entry(158, (uint64_t)isr158);
    set_entry(159, (uint64_t)isr159);
    set_entry(160, (uint64_t)isr160);
    set_entry(161, (uint64_t)isr161);
    set_entry(162, (uint64_t)isr162);
    set_entry(163, (uint64_t)isr163);
    set_entry(164, (uint64_t)isr164);
    set_entry(165, (uint64_t)isr165);
    set_entry(166, (uint64_t)isr166);
    set_entry(167, (uint64_t)isr167);
    set_entry(168, (uint64_t)isr168);
    set_entry(169, (uint64_t)isr169);
    set_entry(170, (uint64_t)isr170);
    set_entry(171, (uint64_t)isr171);
    set_entry(172, (uint64_t)isr172);
    set_entry(173, (uint64_t)isr173);
    set_entry(174, (uint64_t)isr174);
    set_entry(175, (uint64_t)isr175);
    set_entry(176, (uint64_t)isr176);
    set_entry(177, (uint64_t)isr177);
    set_entry(178, (uint64_t)isr178);
    set_entry(179, (uint64_t)isr179);
    set_entry(180, (uint64_t)isr180);
    set_entry(181, (uint64_t)isr181);
    set_entry(182, (uint64_t)isr182);
    set_entry(183, (uint64_t)isr183);
    set_entry(184, (uint64_t)isr184);
    set_entry(185, (uint64_t)isr185);
    set_entry(186, (uint64_t)isr186);
    set_entry(187, (uint64_t)isr187);
    set_entry(188, (uint64_t)isr188);
    set_entry(189, (uint64_t)isr189);
    set_entry(190, (uint64_t)isr190);
    set_entry(191, (uint64_t)isr191);
    set_entry(192, (uint64_t)isr192);
    set_entry(193, (uint64_t)isr193);
    set_entry(194, (uint64_t)isr194);
    set_entry(195, (uint64_t)isr195);
    set_entry(196, (uint64_t)isr196);
    set_entry(197, (uint64_t)isr197);
    set_entry(198, (uint64_t)isr198);
    set_entry(199, (uint64_t)isr199);
    set_entry(200, (uint64_t)isr200);
    set_entry(201, (uint64_t)isr201);
    set_entry(202, (uint64_t)isr202);
    set_entry(203, (uint64_t)isr203);
    set_entry(204, (uint64_t)isr204);
    set_entry(205, (uint64_t)isr205);
    set_entry(206, (uint64_t)isr206);
    set_entry(207, (uint64_t)isr207);
    set_entry(208, (uint64_t)isr208);
    set_entry(209, (uint64_t)isr209);
    set_entry(210, (uint64_t)isr210);
    set_entry(211, (uint64_t)isr211);
    set_entry(212, (uint64_t)isr212);
    set_entry(213, (uint64_t)isr213);
    set_entry(214, (uint64_t)isr214);
    set_entry(215, (uint64_t)isr215);
    set_entry(216, (uint64_t)isr216);
    set_entry(217, (uint64_t)isr217);
    set_entry(218, (uint64_t)isr218);
    set_entry(219, (uint64_t)isr219);
    set_entry(220, (uint64_t)isr220);
    set_entry(221, (uint64_t)isr221);
    set_entry(222, (uint64_t)isr222);
    set_entry(223, (uint64_t)isr223);
    set_entry(224, (uint64_t)isr224);
    set_entry(225, (uint64_t)isr225);
    set_entry(226, (uint64_t)isr226);
    set_entry(227, (uint64_t)isr227);
    set_entry(228, (uint64_t)isr228);
    set_entry(229, (uint64_t)isr229);
    set_entry(230, (uint64_t)isr230);
    set_entry(231, (uint64_t)isr231);
    set_entry(232, (uint64_t)isr232);
    set_entry(233, (uint64_t)isr233);
    set_entry(234, (uint64_t)isr234);
    set_entry(235, (uint64_t)isr235);
    set_entry(236, (uint64_t)isr236);
    set_entry(237, (uint64_t)isr237);
    set_entry(238, (uint64_t)isr238);
    set_entry(239, (uint64_t)isr239);
    set_entry(240, (uint64_t)isr240);
    set_entry(241, (uint64_t)isr241);
    set_entry(242, (uint64_t)isr242);
    set_entry(243, (uint64_t)isr243);
    set_entry(244, (uint64_t)isr244);
    set_entry(245, (uint64_t)isr245);
    set_entry(246, (uint64_t)isr246);
    set_entry(247, (uint64_t)isr247);
    set_entry(248, (uint64_t)isr248);
    set_entry(249, (uint64_t)isr249);
    set_entry(250, (uint64_t)isr250);
    set_entry(251, (uint64_t)isr251);
    set_entry(252, (uint64_t)isr252);
    set_entry(253, (uint64_t)isr253);
    set_entry(254, (uint64_t)isr254);
    set_entry(255, (uint64_t)isr255);

    load_idt();
    
    #undef __MODULE__
    #define __MODULE__ "int"

    TRACE("Initialized\n");
}
