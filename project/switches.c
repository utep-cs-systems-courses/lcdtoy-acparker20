#include <msp430.h>
#include "switches.h"
#include "shapemotion.h"
#include "buzzer.h"
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
void twinkle();

int state = 0;


static unsigned char switches_current, switch_state_changed, switch_mask, switches_last_reported;
static char switch_update_interrupt_sense(){
  switches_current = P2IN & switch_mask;
  // update switch interrupt to detect changes from current button
  P2IES |= (switches_current); // if switch up, sense down
  P2IES &= (switches_current | ~switch_mask); // if switch down, sense up
}
void switch_init(unsigned char mask){ // setup switch

  switch_mask = mask; // enables resistors for switches
  P2REN |= mask; // enable interrupts from from switches 
  P2IE = mask; // pull-ups for switches
  P2OUT |= mask;
  P2DIR &= ~mask; // set switches' bits for input
  switch_update_interrupt_sense(); //initially read switchesss 
}

unsigned int p2sw_read(){

  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);

}
void switch_interrupt_handler(){
  if(switch_state_changed){
    unsigned int switches = p2sw_read(),i;
    char str[5];
    for(i = 0; i < 4; i++)
      str[i] = (switches & (1 << i)) ? '-' : '0'+i;
    str[4] = 0;

    if(str [0] != '-'){
      state = 01;
      switch_state_machine(state);
    }
    else if(str[1] != '-'){
      state = 02;
      switch_state_machine(state);
      
    }
    else if(str[2] != '-'){
      state = 03;
      switch_state_machine(state);
    }
    else if(str[3] != '-'){
      state = 04;
      switch_state_machine(state);

    }
    switch_state_changed = 0;
  }
}
 
void switch_state_machine(int state){

  switch(state){

  case 01:
    switch_state_changed = 1;
    int count = 0;
    twinkle();
      movScreen();
      break;

  case 02:
    // or_sr(0x8);
    switch_state_changed = 1;
    //drawString5x7(20,20, "*twinkle*", COLOR_YELLOW, COLOR_BLUE);
    movScreen();
    break;


  case 03:
    switch_state_changed = 1;
    drawString5x7(20,20, "*twinkle*", COLOR_YELLOW, COLOR_BLUE);
    // uniqueShape();
    movScreen();
    break;

  case 04:
    switch_state_changed = 1;
    twinkle();
    movScreen();
    break;
  
  default:
    movScreen();
    break;
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & switch_mask){

    P2IFG &= ~switch_mask;
    switch_state_changed = 1;
    switch_update_interrupt_sense();
    switch_interrupt_handler();
    
  }

}
