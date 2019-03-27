#ifndef __GDEW029Z10_H
#define __GDEW029Z10_H

#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"

//�ӿ�ģʽ�������Ƿ�ʹ��Ӳ��SPI����ʹ�����ʹ�����ģ��SPI
//#define EPD_HW_SPI

//Ƭѡ���ţ������Ƿ�ʹ�ã���ʹ������Ҫ��CS�ӵأ�δ��֤�Ƿ���ֱ�ӵ�����
#define EPD_USE_CS

//��Ļͼ�����ݷ�ɫ����
#define EPD_IMAGE_DATA_REV

//BUSY
#define EPD_BUSY_PORT   GPIOA        	//��������GPIO��
#define EPD_BUSY_PIN    GPIO_Pin_10   //��������Pin

//RST
#define EPD_RST_PORT    GPIOA
#define EPD_RST_PIN     GPIO_Pin_9

//DC
#define EPD_DC_PORT     GPIOA
#define EPD_DC_PIN      GPIO_Pin_6

//CS
#ifdef  EPD_USE_CS//���ʹ��CS���ţ�����CS���ڵ�GPIO
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

//Ӳ��SPI����GPIO��
//Which GPIO Port the hardware SPI used
#define EPD_HW_SPI_PORT GPIOA

//�������GUI��ʹ�õļĴ���
//define registers used to draw GUI
#define EPD_Reg_BlackPix 0x10
#define EPD_Reg_RedPix   0x13
#define EPD_Reg_Refresh  0x12

//��ʼ��īˮ��GPIO��Ĵ���
void EPD_Init(void);

//д����
void EPD_WriteCmd (unsigned char command);

//д����
void EPD_WriteData (unsigned char data);

//дͼ������
void EPD_SendImageData(unsigned char data);

//������Ļ
void EPD_Sleep(void);


#endif

