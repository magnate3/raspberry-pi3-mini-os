# uart intrrupt handle

```
void handle_irq(void)
{
        unsigned int irq = get32(IRQ_PENDING_1);
        if (irq & AUX_IRQ) { // if it's AUX interrupt
            //printf("uart irq \n");
            irq &= ~AUX_IRQ;
            if ((REGS_AUX->mu_iir & 4) == 4) { // if UART received
                   char c;
                   c = *AUX_MU_IO;  /* read for clear tx interrupt. */
                   printf("uart irq \n");
            }
            return ;
        }
 ……
}
```

# make and run

```
aarch64-linux-gnu-objcopy objects/kernel8.elf -O binary kernel8.img
root@ubuntu:~/arm/raspberry-pi3-mini-os/4.interrupt# qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img
Exception level: 1 
uart irq 
uart irq 
uart irq 
uart irq 
uart irq 
uart irq 
uart irq 
uart irq 
uart irq 

```
 
