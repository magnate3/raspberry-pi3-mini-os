#ifndef	_P_IRQ_H
#define	_P_IRQ_H

#include <stdint.h>
#include "peripherals/base.h"
enum vc_irqs {
	    AUX_IRQ = (1 << 29)
};
#define AUX_MU_IO   ((volatile uint32_t *)(0x3F215040))
typedef uint32_t u32;
typedef volatile u32 reg32;
struct AuxRegs {
	    reg32 irq_status;  
	    reg32 enables;
	    reg32 reserved[14];
	    reg32 mu_io;  
	    reg32 mu_ier;
	    reg32 mu_iir;
	    reg32 mu_lcr;
            reg32 mu_mcr;
	    reg32 mu_lsr;
            reg32 mu_msr;
	    reg32 mu_scratch;
            reg32 mu_control;
	    reg32 mu_status;
            reg32 mu_baud_rate;
};
#define REGS_AUX ((struct AuxRegs *)(PBASE + 0x00215000))
#define IRQ_BASIC_PENDING	(PBASE+0x0000B200)
#define IRQ_PENDING_1		(PBASE+0x0000B204)
#define IRQ_PENDING_2		(PBASE+0x0000B208)
#define FIQ_CONTROL		    (PBASE+0x0000B20C)
#define ENABLE_IRQS_1		(PBASE+0x0000B210)
#define ENABLE_IRQS_2		(PBASE+0x0000B214)
#define ENABLE_BASIC_IRQS	(PBASE+0x0000B218)
#define DISABLE_IRQS_1		(PBASE+0x0000B21C)
#define DISABLE_IRQS_2		(PBASE+0x0000B220)
#define DISABLE_BASIC_IRQS	(PBASE+0x0000B224)

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)

// See BCM2836 ARM-local peripherals at
// https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/QA7_rev3.4.pdf

#define TIMER_INT_CTRL_0    (0x40000040)
#define INT_SOURCE_0        (LPBASE+0x60)

#define TIMER_INT_CTRL_0_VALUE  (1 << 1)
#define GENERIC_TIMER_INTERRUPT (1 << 1)

#endif  /*_P_IRQ_H */
