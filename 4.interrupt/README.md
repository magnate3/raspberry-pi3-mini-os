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

boot.S is copy from [raspberry-pi-os/exercises/lesson03/3/bl4ckout31/src/boot.S](https://github.com/s-matyukevich/raspberry-pi-os/tree/master/exercises/lesson03/3/bl4ckout31/src)

![image](https://github.com/magnate3/raspberry-pi3-mini-os/blob/qemu/4.interrupt/pic/boot_cp.png)

![image](https://github.com/magnate3/raspberry-pi3-mini-os/blob/qemu/4.interrupt/pic/boot.png)


# el1_irq

![image](https://github.com/magnate3/raspberry-pi3-mini-os/blob/qemu/4.interrupt/pic/el1_irq.png)

# install irq vector

```
.globl irq_vector_init
irq_vector_init:
        adr     x0, vectors             // load VBAR_EL1 with virtual
        msr     vbar_el1, x0            // vector table address
        ret

```

#  Rapberry pi  IO memory base address
```
#define PBASE  0x3F000000
#define TIMER_CLO       (PBASE+0x00003004)
#define TIMER_C1        (PBASE+0x00003010)
#define TIMER_CS        (PBASE+0x00003000)
#define TIMER_CS_M3      (1 << 3)

void timer_init ( void )
{
        curVal = get32(TIMER_CLO);
        curVal += interval;
        put32(TIMER_C1, curVal);
}

void handle_timer_irq_3( void )
{
        curVal_3 += interval;
        put32(TIMER_C3, curVal_3);
        put32(TIMER_CS, TIMER_CS_M3);
        printf("Timer 3 interrupt received\n\r");
}
```




# make and run

```
no changes added to commit (use "git add" and/or "git commit -a")
root@ubuntu:~/arm/raspberry-pi3-mini-os/4.interrupt# ls
boot.S  config.txt  entry.S  include  irq.c  irq.S  kernel.c  linker.ld  Makefile  mini_uart.c  mm.S  printf.c  System.map  timer.c  utils.S
root@ubuntu:~/arm/raspberry-pi3-mini-os/4.interrupt# make 
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c kernel.c -o objects/kernel_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c irq.c -o objects/irq_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c mini_uart.c -o objects/mini_uart_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c printf.c -o objects/printf_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c timer.c -o objects/timer_c.o
aarch64-linux-gnu-gcc -Iinclude -MMD -c utils.S -o objects/utils_s.o
aarch64-linux-gnu-gcc -Iinclude -MMD -c irq.S -o objects/irq_s.o
aarch64-linux-gnu-gcc -Iinclude -MMD -c entry.S -o objects/entry_s.o
aarch64-linux-gnu-gcc -Iinclude -MMD -c mm.S -o objects/mm_s.o
aarch64-linux-gnu-gcc -Iinclude -MMD -c boot.S -o objects/boot_s.o
aarch64-linux-gnu-ld -T linker.ld -o objects/kernel8.elf   objects/kernel_c.o  objects/irq_c.o  objects/mini_uart_c.o  objects/printf_c.o  objects/timer_c.o  objects/utils_s.o  objects/irq_s.o  objects/entry_s.o  objects/mm_s.o  objects/boot_s.o -Map System.map
aarch64-linux-gnu-objcopy objects/kernel8.elf -O binary kernel8.img
root@ubuntu:~/arm/raspberry-pi3-mini-os/4.interrupt#  qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img
hello 
If you want stop timer，just enter any key
Please choose a timer number 1 or 3
Your choice:1
Timer 1 interrupt received
If you want stop timer，just enter any key
Please choose a timer number 1 or 3
Your choice:1
Timer 1 interrupt received
If you want stop timer，just enter any key
Please choose a timer number 1 or 3
Your choice:3
Timer 1 interrupt received
Timer 3 interrupt received
If you want stop timer，just enter any key
Please choose a timer number 1 or 3
Your choice:3
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
Timer 3 interrupt received
QEMU: Terminated
root@ubuntu:~/arm/raspberry-pi3-mini-os/4.interrupt#
```
