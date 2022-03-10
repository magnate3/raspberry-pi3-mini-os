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

##  uart.c

uart.c is copy from [raspberry-pi-os/exercises/lesson03/3/bl4ckout31/src/mini_uart.c](https://github.com/s-matyukevich/raspberry-pi-os/tree/master/exercises/lesson03/3/bl4ckout31/src)
