#include "GDEW029Z10.h"
#include "delay.h"	

#define RST_L EPD_RST_PORT->BRR  = EPD_RST_PIN
#define RST_H EPD_RST_PORT->BSRR = EPD_RST_PIN

#define DC_L  EPD_DC_PORT-> BRR  = EPD_DC_PIN
#define DC_H  EPD_DC_PORT-> BSRR = EPD_DC_PIN

#ifdef EPD_USE_CS
#define CS_L  EPD_CS_PORT-> BRR  = EPD_CS_PIN
#define CS_H  EPD_CS_PORT-> BSRR = EPD_CS_PIN
#else
#define CS_L  ;
#define CS_H  ;
#endif

#ifndef EPD_HW_SPI
#define SCK_L  EPD_SCK_PORT->BRR  = EPD_SCK_PIN
#define SCK_H  EPD_SCK_PORT->BSRR = EPD_SCK_PIN

#define SDA_L  EPD_SDA_PORT->BRR  = EPD_SDA_PIN
#define SDA_H  EPD_SDA_PORT->BSRR = EPD_SDA_PIN
#endif

#ifdef EPD_HW_SPI
void EPD_SpiWrite(unsigned char data)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){;}    //检查发送是否完成 
    SPI_SendData8(SPI1, data);
}
#else
void EPD_SpiWrite(unsigned char data)
{
	unsigned char i;
    for(i=0;i<8;i++)
	{			  
		SCK_L;
		if(data&0x80)
		{
		SDA_H;
		}
		else 
		{
		SDA_L;
		}
		SCK_H;
		data<<=1;   
	}			
}
#endif

void EPD_WriteCmd (unsigned char command)
{
	CS_L;
	//delay_us(10);
	DC_L;
	EPD_SpiWrite(command);
	//delay_us(10);
	CS_H;
}

void EPD_WriteData (unsigned char data)
{
	CS_L;
	//delay_us(10);
	DC_H;
	EPD_SpiWrite(data);
	//delay_us(10);
	CS_H;
}

unsigned char EPD_CheckBusy(void)
{ 
	unsigned char busy;
	if(GPIO_ReadInputDataBit(EPD_BUSY_PORT,EPD_BUSY_PIN))
	{
		busy=1;
	}
	else
	{
		busy=0;
	}
	return busy;
}

void EPD_GPIOConfig(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	#ifdef EPD_HW_SPI
	SPI_InitTypeDef   SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	#endif
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB,ENABLE);
	
	//BUSY
	GPIO_InitStructure.GPIO_Pin =EPD_BUSY_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EPD_BUSY_PORT, &GPIO_InitStructure);
	
	//RST
	GPIO_InitStructure.GPIO_Pin =EPD_RST_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(EPD_RST_PORT, &GPIO_InitStructure);
	RST_H;
	
	//DC
	GPIO_InitStructure.GPIO_Pin =EPD_DC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(EPD_DC_PORT, &GPIO_InitStructure);
	DC_H;
	
	#ifdef EPD_USE_CS
	//CS
	GPIO_InitStructure.GPIO_Pin =EPD_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(EPD_CS_PORT, &GPIO_InitStructure);
	CS_H;
	#endif
	
	#ifdef EPD_HW_SPI
	//HW SPI
	GPIO_InitStructure.GPIO_Pin = EPD_SCK_PIN | EPD_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    	//复用
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;   //下拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //中速
  GPIO_Init(EPD_HW_SPI_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(EPD_HW_SPI_PORT, EPD_SCK_PIN, GPIO_AF_0);
	GPIO_PinAFConfig(EPD_HW_SPI_PORT, EPD_SDA_PIN, GPIO_AF_0);
	
	
	SPI_I2S_DeInit(SPI1);    //将寄存器重设为缺省值
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;    //双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;    //主机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;    //8 位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;    //通信空闲时 SCK 为低电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;    //第一个时钟沿捕获
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;    //软件控制 NSS
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;    //SPI 速度 2 分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //数据传输从 MSB 开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;    //CRC 校验
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_Cmd(SPI1,ENABLE);
	#else
	//SOFT SCK
	GPIO_InitStructure.GPIO_Pin =EPD_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(EPD_SCK_PORT, &GPIO_InitStructure);
	SCK_L;
	//SOFT SDA
	GPIO_InitStructure.GPIO_Pin =EPD_SDA_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(EPD_SDA_PORT, &GPIO_InitStructure);
	SDA_L;
	#endif
}

void EPD_Reset(void)
{
	RST_H;
	delay_ms(20);
	RST_L;
	delay_ms(20);
	RST_H;
	delay_ms(20);
}


void EPD_Init(void)
{
	EPD_GPIOConfig();
	EPD_Reset();
	
	//Booster Soft Start
	//软件开启内部BOOST
	EPD_WriteCmd(0x06);                                                    
	EPD_WriteData (0x17);
	EPD_WriteData (0x17);
	EPD_WriteData (0x17);
	
  //Power On
  //开启电源	
	EPD_WriteCmd(0x04); 

  //等待芯片处理完毕	
	while(EPD_CheckBusy());  
	
  //Panel Setting
	EPD_WriteCmd(0X00);
	EPD_WriteData(0x07);//UD=0,SHL=1,SHD_N=1,RST_N=1  从屏幕左下角至右上角扫描（竖屏观察）
	
  //VCom and data interval setting	
	EPD_WriteCmd(0X50);
	EPD_WriteData(0x77);
	
  //Resolution Setting	
	EPD_WriteCmd(0x61);	
	EPD_WriteData (0x80); 
  EPD_WriteData (0x01);
  EPD_WriteData (0x28);
	
}

void EPD_Sleep(void)
{
	EPD_WriteCmd(0x02);
	
	//等待芯片处理完毕	
	while(EPD_CheckBusy()){;}
  EPD_WriteCmd(0x07);	
	EPD_WriteData (0xA5);
}


void EPD_SendImageData(unsigned char data)
{
	#ifdef EPD_IMAGE_DATA_REV
	EPD_WriteData(~data);
	#else
	EPD_WriteData(data);
	#endif
}



