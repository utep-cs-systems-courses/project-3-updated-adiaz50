#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"
 
#define LED_GREEN BIT6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler(){
  static int secCount = 0;

  secCount++;
  if(secCount == 250){
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}


int main() {

  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  configureClocks();

  led_init();

  switch_init();

  buzzer_init();  

  enableWDTInterrupts();


  or_sr(0x18);

  clearScreen(COLOR_BLACK);

  while(1){
    if(redrawScreen) {
      redrawScreen = 0;
      drawString5x7(30, 30, "Hello_World!", fontFgColor, COLOR_WHITE);
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
