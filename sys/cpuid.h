#pragma once
#include <stdbool.h>
#include <stdint.h>

static inline bool cpuid(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t cpuid_max;
    __asm__ __volatile__("cpuid" : "=a" (cpuid_max) : "a" (leaf & 0x80000000) : "ebx", "ecx", "edx");
    
	if (leaf > cpuid_max) {
        return false;
	}

    __asm__ __volatile__ ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "a" (leaf), "c" (subleaf));
    return true;
}
