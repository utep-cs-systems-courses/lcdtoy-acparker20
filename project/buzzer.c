#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include <stdio.h>
#include <stdlib.h>

//note frequencies

#define c 1911
#define d 1702
#define e 1516
#define f 1431//changed
#define g 1275
#define gS 415
#define a 1136
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

void buzzer_init(){
  timerAUpmode(); // used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL  &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // enable output to speaker P2.6
  



}
// song begins here
void twinkle(){

  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2DIR = BIT6;
  P2SEL |= BIT6;//buzzer on

  int song[] = {c, 0, c, 0,  g, 0, g, 0,  a, 0, a, 0, 0, g, 0, f, 0, f, 0, e, 0, e, 0, d, 0, d, 0,0, c, 0, 0, g, 0, g, f, 0,  f, 0, e, 0, e, 0, d, 0, g, 0, g, 0, f, 0,  f, 0, e, 0, e, 0, d, 0, 0, c, 0, c, 0, g, 0, g, 0, a, 0, a, 0, g, 0, 0, f, 0, f, 0, e, 0, e, 0, d, 0, d, 0, c};

    int keys = 0;
  for(int i =  0; i < 90; i++){
    keys = song[i];
    buzzer_set_period(keys);
    __delay_cycles(2500000);
    P2SEL &= ~BIT7; // turn off buzzer

  }
  P2DIR &= ~BIT6; //stops buzzer
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;

}
