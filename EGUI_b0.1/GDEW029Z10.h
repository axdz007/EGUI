#ifndef __GDEW029Z10_H
#define __GDEW029Z10_H

#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"

//接口模式，决定是否使用硬件SPI，不使用则会使用软件模拟SPI
#define EPD_HW_SPI

//片选引脚，决定是否使用，不使用则需要把CS接地（未验证是否能直接点亮）
#define EPD_USE_CS

//屏幕图像数据反色处理
#define EPD_IMAGE_DATA_REV

//BUSY
#define EPD_BUSY_PORT   GPIOA        	//引脚所在GPIO组
#define EPD_BUSY_PIN    GPIO_Pin_10   //引脚所在Pin

//RST
#define EPD_RST_PORT    GPIOA
#define EPD_RST_PIN     GPIO_Pin_9

//DC
#define EPD_DC_PORT     GPIOA
#define EPD_DC_PIN      GPIO_Pin_6

//CS
#ifdef  EPD_USE_CS//如果使用CS引脚，则定义CS所在的GPIO
#define EPD_CS_PORT     GPIOB
#define EPD_CS_PIN      GPIO_Pin_1
#endif

//SCK
#define EPD_SCK_PORT    GPIOA
#define EPD_SCK_PIN     GPIO_Pin_5

//MOSI
//Software SPI MOSI
#define EPD_SDA_PORT    GPIOA
#define EPD_SDA_PIN     GPIO_Pin_7

//硬件SPI所在GPIO组
//Which GPIO Port the hardware SPI used
#define EPD_HW_SPI_PORT GPIOA

//定义绘制GUI所使用的寄存器
//define registers used to draw GUI
#define EPD_Reg_BlackPix 0x10
#define EPD_Reg_RedPix   0x13
#define EPD_Reg_Refresh  0x12

//初始化墨水屏GPIO与寄存器
void EPD_Init(void);

//写命令
void EPD_WriteCmd (unsigned char command);

//写数据
void EPD_WriteData (unsigned char data);

//写图像数据
void EPD_SendImageData(unsigned char data);

//休眠屏幕
void EPD_Sleep(void);

void EPD_Release_IO(void);


#endif

