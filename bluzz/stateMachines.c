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

void state2(){ // green light on and make bigger sound
  toggle_red();
  //buzzer_set_period(100);
  leds_changed = 1;
  led_update();
}

void state3(){ // leds turn on at the same time, sound turns on when leds are off
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
/*
void state4(){ // everything turns on simultaniously
  static short change = 0;
  
  switch(change){
    case 0:
      red_on = 0;
      buzzer_set_period(0);
      change++;
      break;

    case 1:
      dim_25();
      buzzer_set_period(50);
      change++;
      break;

    case 2:
      dim_50();
      change++;
      buzzer_set_period(100);
      break;

    case 3:
      dim_75();
      change = 0;
      buzzer_set_period(350);
      break;
  }
  leds_changed = 1;
  led_update();
}
*/
/*
char dim_state_advance(){
  switch(dim_select){
  case 0:
    dim_select++;
    red_on = 0;
    break;
  case 1:
    dim_select++;
    dim_25();
    break;
  case 2:
    dim_select++;
    dim_50();
    break;
  case 3:
    dim_select++;
    dim_75();
    break;
  case 4:
    dim_select = 0;
    red_on = 1;
    break;
  }
  return 1;
}
*/

void dim_25(){
  switch(dimState){
  case 0:
    red_on = 1;
    break;
  case 1:
  case 2:
  case 3:
    red_on = 0;
    break;
  default: dimState = 0;
  }
  leds_changed = 1;
  led_update();
}

void dim_50(){
  switch(dimState){
  case 0:
  case 1:
    red_on = 1;
    break;
  case 2:
  case 3:
    red_on = 0;
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
    break;
  case 1:
  case 2:
  case 3:
    red_on = 1;
    break;
  default: dimState = 0;
  }
  leds_changed = 1;
  led_update();
}

void state4(){
  static short change = 0;

  switch(change){
  case 0:
    red_on = 0;
    buzzer_set_period(0);
    change++;
    break;
    
  case 1:
    dim_25();
    buzzer_set_period(50);
    change++;
    break;

  case 2:
    dim_50();
    change++;
    buzzer_set_period(100);
    break;

  case 3:
    dim_75();
    change = 0;
    buzzer_set_period(350);
    break;
  }
  leds_changed = 1;
  led_update();
}
/*
void state_advance(char ssc){
  char changed = 0;
  
  switch(ssc){

    case 1:
      changed = state1();
      break;
      
    case 2:
      
      changed = state2();
      break;

    case 3:

      changed = state3();
      break;

    case 4:

      changed = state4();
      break;
  }
}
*/

