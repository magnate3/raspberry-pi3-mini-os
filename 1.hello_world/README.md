# changes

## include dir
![image](https://github.com/tina0405/raspberry-pi3-mini-os/blob/master/Screenshot%20from%202020-04-09%2015-35-30.png)
 
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
