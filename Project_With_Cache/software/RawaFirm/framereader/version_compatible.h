#include <sys/alt_irq.h>

#undef PRE_V91_HAL

#ifdef PRE_V91_HAL
#define alt_ic_isr_register( ic_id, irq, isr, isr_context, flags) alt_irq_register( irq, isr_context, ((void (*)(void*,alt_u32) ) isr) )
#endif

