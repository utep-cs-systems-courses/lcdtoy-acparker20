#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h" // setPeriod
#include "switches.h"
#include <lcdutils.h>
#include <lcddraw.h>
#include <shape.h>
#include <abCircle.h>
#include "shapemotion.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

  configureClocks(); // setup oscillator, CPU and clocks
  switch_init(15);
  lcd_init();
  setScreen();

  or_sr(0x8); //CPU off, GIE on

}
