#ifndef	_TIMER_H
#define	_TIMER_H

void timer_init ( void );
void timer_init_3 ( void );
void handle_timer_irq ( void );
void handle_timer_irq_3 ( void );

void generic_timer_init ( void );
void handle_generic_timer_irq ( void );

extern void gen_timer_init();
extern void gen_timer_reset();

#endif  /*_TIMER_H */
