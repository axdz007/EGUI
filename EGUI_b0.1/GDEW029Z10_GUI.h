#ifndef __GDEW029Z10_GUI_H
#define __GDEW029Z10_GUI_H
#include "GDEW029Z10.h"

#define FONT_ENABLE_ASC0816
#define FONT_ENABLE_ASC1224
#define FONT_ENABLE_ASC1632

#define EPD_WIDE 296
#define EPD_HEIGHT 128

#define Gcolor_black 0
#define Gcolor_red   1

#define Gbatt_left   1
#define Gbatt_right   0

#define Widget_show   1
#define Widget_hide   0

#define MAX_SIZE_OF_STRING 40

	





void EGuiInit(void);
void EGuiUpdate(void);
#endif
