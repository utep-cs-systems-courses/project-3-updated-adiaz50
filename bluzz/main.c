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
static int x, y;

  /*  
  if(secCount == 250){
    state_advance();
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  */

void diamond(){
  for( x = 0; x <= 50; x++){
    drawPixel(13 + x, 68 + x, COLOR_RED);
    drawPixel(13 + x, 68 - x, COLOR_BLUE);
    drawPixel(63 + x, x + 18, COLOR_YELLOW);
    drawPixel(x + 63, 118 - x, COLOR_WHITE);
  }
}
void colorDiamond(){
  for (x = 0; x <= 50; x++){
    drawPixel(13 + x, 68 + x, COLOR_WHITE);
    drawPixel(13 + x, 68 - x, COLOR_RED);
    drawPixel(63 + x, x + 18, COLOR_BLUE);
    drawPixel(x + 63, 118 - x, COLOR_YELLOW);
  }
}
void clear(){
  clearScreen(COLOR_BLACK);
}

void word(){
  for( y = 0; y<= 99; y++ ){
    drawPixel(64, y + 18, COLOR_RED);
    drawPixel(14 + y, 68, COLOR_WHITE);
  }
  drawString5x7(33, 58, "AXEL DIAZ", COLOR_WHITE, COLOR_BLACK);
}

void wdt_c_handler(){
  static int secCount = 0;
  
  secCount++;
  if(secCount == 125){
    redrawScreen = 1;
    secCount = 0;
  }
  /*
  if(++secCount == 125 && switch_state_changed == 1 ){
    redrawScreen = 1;
    secCount = 0;
  }else if(secCount == 250 && switch_state_changed == 2){
    redrawScreen = 1;
    secCount = 0;
  }else if(secCount == 250 && switch_state_changed == 3){
    redrawScreen = 1;
    secCount = 0;
  }else if(secCount == 250 && switch_state_changed == 4){
    redrawScreen = 1;
    secCount = 0;
    }*/
}  
  /*  if(secCount == 125 && switch_state_changed == 1){
    secCount = 0;
    state_advance();
    fontFgColor = COLOR_WHITE;
    redrawScreen = 1;
  }else if(secCount == 250 && switch_state_changed == 2){
    secCount = 0;
    fontFgColor = COLOR_YELLOW;
    redrawScreen = 1;
  }else if(secCount == 250 && switch_state_changed == 3){
    secCount = 0;
    fontFgColor = COLOR_BLACK;
    redrawScreen = 1;
  }else if((secCount == 3) && switch_state_changed == 4){
    secCount = 0;
    fontFgColor = COLOR_BLUE;
    redrawScreen = 1;
    }*/


int main() {

  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  configureClocks();

  led_init();
  lcd_init();
  switch_init();
  //  p2sw_init();
  buzzer_init();  

  enableWDTInterrupts();

  or_sr(0x18);
   
  clearScreen(COLOR_BLACK);
  
  while(1){
    if(redrawScreen) {
      
      switch(switch_state_changed){
      case 1:
	state1();
	diamond();
	break;
      case 2:
	colorDiamond();
	state2();
	break;
      case 3:
	clear();
	state3();
	break;
      case 4:
	diamond();
	state4();
	word();
      }
      redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
