#include <drivers/apic.h>
#include <sys/cpuid.h>

#define APIC_ACTIVE_HIGH        (1 << 1)
#define APIC_LEVEL_TRIGGERED    (1 << 3)
#define APIC_REDIR_BAD_READ     0xFFFFFFFFFFFFFFFF

static volatile const uint64_t ia32_apic_base = 0x1b;


uint64_t x2apic_read(uint16_t offset) {
	return rdmsr(0x800 + (offset >> 4));
}

void x2apic_write(uint16_t offset, uint64_t val) {
	wrmsr(0x800 + (offset >> 4), val);
}

static void set_lapic_timer_mask(size_t mask) {
    uint32_t entry = x2apic_read(LAPIC_REG_LVT_TIMER);
    if(mask) {
        entry |= 1UL << 16;
    } else {
        entry &= ~(1UL << 16);
    }

    x2apic_write(LAPIC_REG_LVT_TIMER, entry);
}

void init_lapic_timer() {
    x2apic_write(LAPIC_REG_TIMER_DIVCONF, 0x3);
    x2apic_write(LAPIC_REG_TIMER_INITCNT, 0xFFFFFFFF);
    set_lapic_timer_mask(0);
    hpet_poll_and_sleep(10);
    set_lapic_timer_mask(1);

    size_t num_ticks = x2apic_read(LAPIC_REG_TIMER_CURCNT);
    size_t ticks_p_ms = (0xFFFFFFFF - num_ticks) / 10;

    uint32_t entry = x2apic_read(LAPIC_REG_LVT_TIMER);
    entry &= ~(3 << 17);
    entry |= (1 << 17);
    entry = ((entry & 0xFFFFFF00) | 32);

    x2apic_write(LAPIC_REG_LVT_TIMER, entry);
    x2apic_write(LAPIC_REG_TIMER_DIVCONF, 0x3);
    x2apic_write(LAPIC_REG_TIMER_INITCNT, ticks_p_ms);

    set_lapic_timer_mask(0);
    TRACE("Timer Initialized\n", num_ticks);
}

bool x2apic_check() {
	uint32_t eax, ebx, ecx, edx;
	if (!cpuid(1, 0, &eax, &ebx, &ecx, &edx)) {
		return false;
	}

	if (!(ecx & (1 << 21))) {
		return false;
	}

	// we should check stuff in the dmar table here too but idc its just a test

	return true;
}

void x2apic_enable() {
	TRACE("Enabling x2APIC YAY!\n");

	uint64_t ia32_apic_base = rdmsr(0x1b);
	ia32_apic_base |= (1 << 10);
	wrmsr(0x1b, ia32_apic_base);
}

void init_apic() {
	if (x2apic_check()) {
		TRACE("X2APIC Detected\n");
		x2apic_enable();
	} else {
		ERR("X2APIC Not Detected\n");
		while (1) {
			__asm__ __volatile__("cli; hlt");
		}
	}

    // Remap the PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Disable the PIC
    outb(0xA1, 0xFF);
    outb(0x21, 0xFF);
}
