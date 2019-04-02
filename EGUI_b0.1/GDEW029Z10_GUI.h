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

//图片控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;
unsigned int ysize;
unsigned char color;
unsigned char enable;
const unsigned char *pic;	

}G_Picture;

//图标控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;
unsigned int ysize;
unsigned char color;
unsigned char enable;
const unsigned char *pic;	

}G_Icon;

//字符串控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;
unsigned int ysize;
unsigned char color;
unsigned char enable;
const unsigned char *font;
unsigned char numofstring; 
char strbuf[MAX_SIZE_OF_STRING];	

}G_String;



//数字显示控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;
unsigned int ysize;
unsigned char color;
unsigned char enable;
const unsigned char *font;
unsigned char numofnumber;
unsigned long number;
}G_Number;

//电池图标控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;	
unsigned int ysize;
unsigned char dir;
unsigned char color;
unsigned char enable;
unsigned char percent;
}G_Battery;

//色块控件
typedef struct 
{
unsigned int xstart;	
unsigned int ystart;
unsigned int xsize;	
unsigned int ysize;
unsigned char color;
unsigned char enable;
}G_Block;





void EGuiInit(void);
void EGuiProcess(void);
void EGuiUpdate(void);
#endif
