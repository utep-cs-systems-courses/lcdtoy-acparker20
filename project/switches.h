#ifndef switches_included
#define switches_included
#include "msp430.h"


static unsigned char switch_mask;
unsigned int p2sw_read();
void switch_init(unsigned char mask);
void switch_interrupt_handler();
void switch_state_machine(int state);
#endif
