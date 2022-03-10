# changes

## include dir
![image](https://github.com/magnate3/raspberry-pi3-mini-os/blob/qemu/1.hello_world/pic/changes.png)
 
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



# make and run

```
root@ubuntu:~/arm/raspberry-pi3-mini-os/1.hello_world# make
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c uart.c -o objects/uart_c.o
mkdir -p objects
aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c kernel.c -o objects/kernel_c.o
aarch64-linux-gnu-gcc -Iinclude  -MMD -c utils.S -o objects/utils_s.o
aarch64-linux-gnu-gcc -Iinclude  -MMD -c mm.S -o objects/mm_s.o
aarch64-linux-gnu-gcc -Iinclude  -MMD -c boot.S -o objects/boot_s.o
aarch64-linux-gnu-ld -T linker.ld -o objects/kernel8.elf  objects/uart_c.o objects/kernel_c.o  objects/utils_s.o  objects/mm_s.o  objects/boot_s.o -Map system.map
aarch64-linux-gnu-objcopy objects/kernel8.elf -O binary kernel8.img
root@ubuntu:~/arm/raspberry-pi3-mini-os/1.hello_world# qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img
Hello, world!
QEMU: Terminated
root@ubuntu:~/arm/raspberry-pi3-mini-os/1.hello_world# 
```
