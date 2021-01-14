#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

static char dim_select = 0;
static char do_dim = 0;
static char dimState = 0;

char toggle_red(){
  static char state = 0;

  switch(state){
  case 0:
    red_on = 1;
    buzzer_set_period(100);
    state = 1;
    break;
  case 1:
    red_on = 0;
    buzzer_set_period(0);
    state = 0;
    break;
  }
  return 1;
}

char toggle_green(){
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    buzzer_set_period(0);
    changed = 1;
  }
  return changed;
}

void state1(){ 
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  switch(color){
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  leds_changed = changed;
  led_update();
}

void state2(){ // toggle red just bigger sound
  toggle_red();
  //buzzer_set_period(100);
  leds_changed = 1;
  led_update();
}

void state3(){ // when red led on no sound and when off sound is on
  static short state_change = 0;
  
  switch(state_change){
    case 0:
      
      red_on = 1;
      state_change = 1;
      buzzer_set_period(0);
      break;

    case 1:

      red_on = 0;
      state_change = 0;
      buzzer_set_period(2000);
      break;
  }
  leds_changed = 1;
  led_update();
}

void dim_25(){
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 0;
    dimState = 3;
    break;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  default: dimState = 0;
  }
  leds_changed = 1;
  led_update();
}

void dim_50(){
  switch(dimState){
  case 0:
    red_on = 0;
    dimState = 1;
    break;
  case 1:
    red_on = 1;
    dimState = 2;
    break;
  case 2:
    red_on = 0;
    dimState = 3;
    break;
  case 3:
    red_on = 1;
    dimState = 0;
    break;
  default: dimState = 0;
  }
  leds_changed = 1;
  led_update();
}

void dim_75(){
  switch(dimState){
  case 0:
    red_on = 0;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 0;
    dimState = 3;
    break;
  case 3:
    red_on = 1;
    dimState = 0;
    break;
  default: dimState = 0;
  }
  leds_changed = 1;
  led_update();
}

char dim_state_advance(){
  char ch = 1;
  switch(ch){
  case 1:
    ch = 2;
    dim_25();
   
  case 2:
    ch = 3;
    dim_50();
   
  case 3:
    ch = 1;
    dim_75();
   
  }
  leds_changed = 1;
  led_update();
  return 1;
}

void state4(){
  static short change = 0;

  switch(change){
  case 0:
    red_on = 0;
    buzzer_set_period(0);
    change = 1;
    break;
    
  case 1:
    dim_state_advance();
    buzzer_set_period(250);
    change = 0;
    break;
  }
  leds_changed = 1;
  led_update();
}
