/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
/** Initializes everything, clears the screen, draws "hello" and a square */
void diamond()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  // edge limit for x is 0 - 127
  // edge limit for y is 0 - 157
  clearScreen(COLOR_BLACK);

  int edgex;
  int edgey;
  int x;
  int y;

  // diamond
  for( x = 0; x <= 50; x++ ){
    //shaded diamond
    /*for( x = 0; x <= y; x++){
      drawPixel(63 + x ,78 + y, COLOR_RED);
      drawPixel(53 + x, 68 + y, COLOR_BLUE);
      }*/
    
    //53 68    yellow and white 63,58 and 63,78
    drawPixel(13 + x, 68 + x, COLOR_RED);
    drawPixel(13+ x, 68 - x, COLOR_BLUE);
    drawPixel(63 + x, x + 18, COLOR_YELLOW);
    drawPixel(x + 63, 118 - x, COLOR_WHITE);
    
  }
  // crosshair
  /*
  for( y = 0; y <= 99; y++){
    drawPixel(64, y + 18, COLOR_RED);
    drawPixel(14 + y, 68, COLOR_WHITE);
  }
  */
  drawString5x7(33, 58, "PROJECT: 3", COLOR_WHITE, COLOR_BLACK);
  // Switch 1 = show diamond plain white
  // Switch 2 = show crosshairs
  // Switch 3 = change colors
  // Switch 4 = clear all and flash goodbye world
  or_sr(0x8);/* GIE (enable interrupts) */
  /*
  while (1) {

    u_int switches = p2sw_read(), i;

    char str[5];

    for (i = 0; i < 4; i++)

      str[i] = (switches & (1<<i)) ? '-' : '0'+i;

    str[4] = 0;

    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLACK);

  } 
  */
}
