# changes

## include dir
![image](https://github.com/magnate3/raspberry-pi3-mini-os/blob/qemu/4.interrupt/pic/include.png)
 
include is copy from [raspberry-pi-os/exercises/lesson03/3/bl4ckout31/include](https://github.com/s-matyukevich/raspberry-pi-os/tree/master/exercises/lesson03/3/bl4ckout31)

## linker.ld

```
SECTIONS
{
     . = 0x80000;
        .text.boot : { *(.text.boot) }
        .text : { *(.text) }
        .rodata : { *(.rodata) }
        .data : { *(.data) }
        . = ALIGN(0x8);
        bss_begin = .;
        .bss : { *(.bss*) } 
        bss_end = .;
}

```

add start addr:  . = 0x80000;

##  mini_uart.c

mini_uart.c is copy from [raspberry-pi-os/exercises/lesson03/3/bl4ckout31/src/mini_uart.c](https://github.com/s-matyukevich/raspberry-pi-os/tree/master/exercises/lesson03/3/bl4ckout31/src)

## boot.S

boot.S is copy from [raspberry-pi-os/exercises/lesson03/3/bl4ckout31/src/boot.S](https://github.com/fxlin/p1-kernel/tree/master/src/lesson02)


```
root@ubuntu:~/arm/raspberry-pi3-mini-os/2.exception_level/el_1# cat boot.S 
#include "arm_v8/sysregs.h"

#include "mm.h"

.section ".text.boot"

.globl _start
_start:
        mrs     x0, mpidr_el1
        and     x0, x0,#0xFF            // Check processor id
        cbz     x0, master              // Hang for all non-primary CPU
        b       proc_hang

proc_hang: 
        b       proc_hang

master:
        ldr     x0, =SCTLR_VALUE_MMU_DISABLED // System control register
        msr     sctlr_el1, x0

        ldr     x0, =HCR_VALUE          // Hypervisor Configuration (EL2) 
        msr     hcr_el2, x0  

#ifdef USE_QEMU                 // xzl: qemu boots from EL2. cannot do things to EL3
        ldr     x0, =SPSR_VALUE
        msr     spsr_el2, x0

        #adr    x0, el1_entry
        adr x0, el1_entry_another
        msr     elr_el2, x0
#else                                   // xzl: Rpi3 hw boots from EL3. 
        ldr     x0, =SCR_VALUE  // Secure config register. Only at EL3.
        msr     scr_el3, x0

        ldr     x0, =SPSR_VALUE
        msr     spsr_el3, x0

        adr     x0, el1_entry
        msr     elr_el3, x0
#endif
  
        eret

el1_entry:
        adr     x0, bss_begin
        adr     x1, bss_end
        sub     x1, x1, x0
        bl      memzero

el1_entry_another:
        mov     sp, #LOW_MEMORY
        bl      kernel_main
        b       proc_hang               // should never come here
```

# make
```
root@ubuntu:~/arm/raspberry-pi3-mini-os/2.exception_level/el_1# make
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -DUSE_QEMU  -MMD -c mini_uart.c -o objects/mini_uart_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -DUSE_QEMU  -MMD -c printf.c -o objects/printf_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -DUSE_QEMU  -MMD -c kernel.c -o objects/kernel_c.o
aarch64-linux-gnu-gcc -Iinclude -DUSE_QEMU -MMD -c utils.S -o objects/utils_s.o
aarch64-linux-gnu-gcc -Iinclude -DUSE_QEMU -MMD -c mm.S -o objects/mm_s.o
aarch64-linux-gnu-gcc -Iinclude -DUSE_QEMU -MMD -c boot.S -o objects/boot_s.o
aarch64-linux-gnu-ld -T linker.ld -o objects/kernel8.elf  objects/mini_uart_c.o objects/printf_c.o objects/kernel_c.o objects/utils_s.o objects/mm_s.o objects/boot_s.o -Map System.map
aarch64-linux-gnu-objcopy objects/kernel8.elf -O binary kernel8.img 
```

# run

```

root@ubuntu:~/arm/raspberry-pi3-mini-os/2.exception_level/el_1#  qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img
Exception level: 1 

```

 


 