#include "GDEW029Z10_GUI.h"
#include "GDEW029Z10_Font.h"
#include "GDEW029Z10.h"

#define _mode_cover_ =
#define _mode_trans_ |=

#define FONT_OFFSET -32





G_Picture pic1;
G_Picture pic2;
G_Picture pic3;
G_Picture pic4;

G_String str1;
G_String str2;
G_String str3;
G_String str4;

G_Battery bat1;
G_Battery bat2;
G_Battery bat3;
G_Battery bat4;

G_Icon IconDegreeCelsius;
G_Icon IconDegreeFahrenheit;
G_Icon IconHumidity;

G_Number num1;

G_Block line1;

G_Block line2;

G_Block line3;
G_Block line4;
G_Block line5;
G_Block line6;


unsigned int ax,ay,bx,by;

unsigned char checkarea(unsigned int curx,unsigned int cury,G_Picture res)
{
	unsigned char data;
	if((curx>=res.xstart)&&(cury>=res.ystart))
	{
		unsigned int x_end,y_end;
		x_end=res.xstart+res.xsize;
		y_end=res.ystart+res.ysize;
		if((curx<x_end)&&(cury<y_end))
		{
			data=1;
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
}

//BITMAP
unsigned char PixelCheckBMP(unsigned int curx,unsigned int cury,unsigned char color,G_Picture res)
{
	unsigned char data;
	unsigned char pixflag;
	if((curx>=res.xstart)&&(cury>=res.ystart)&&(res.color==color)&&res.enable)
	{
	unsigned int x_end,y_end;
	x_end=res.xstart+res.xsize;
	y_end=res.ystart+res.ysize;
	if((curx<x_end)&&(cury<y_end))
		{
			pixflag=0x80;
			data=res.pic[((cury-res.ystart)/8)+((curx-res.xstart)*( (res.ysize/8)+(res.ysize%8!=0) ))];
			data&=(pixflag>>((cury-res.ystart)%8));
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
	
}

//Icon
unsigned char PixelCheckIcon(unsigned int curx,unsigned int cury,unsigned char color,G_Icon *res)
{
	unsigned char data;
	unsigned char pixflag;
	if((curx>=res->xstart)&&(cury>=res->ystart)&&(res->color==color)&&res->enable)
	{
	unsigned int x_end,y_end;
	x_end=res->xstart+res->xsize;
	y_end=res->ystart+res->ysize;
	if((curx<x_end)&&(cury<y_end))
		{
			pixflag=0x80;
			data=res->pic[((cury-res->ystart)/8)+((curx-res->xstart)*( (res->ysize/8)+(res->ysize%8!=0) ))];
			data&=(pixflag>>((cury-res->ystart)%8));
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
	
}

//STRING
unsigned char PixelCheckString(unsigned int curx,unsigned int cury,unsigned char color,G_String *res)
{
	unsigned char data;
	unsigned char pixflag;
	unsigned char font_height,font_wide;
	unsigned int array_of_each_char;
	unsigned char font_pos_x;
	
	font_height=res->ysize;
	font_wide=res->xsize;
	array_of_each_char=font_height/8;
	font_pos_x=(curx-res->xstart)%font_wide;

	if((curx>=res->xstart)&&(cury>=res->ystart)&&(res->color==color)&&res->enable)
	{
	unsigned int x_end,y_end;
	x_end=res->xstart+(res->xsize*res->numofstring);
	y_end=res->ystart+res->ysize;
	if((curx<x_end)&&(cury<y_end))
		{
			pixflag=0x80;
			data=res->font[((cury-res->ystart)/8)+(  font_pos_x+ ((res->strbuf[(curx-res->xstart)/font_wide]+FONT_OFFSET)*font_wide)  ) *array_of_each_char];
			data&=pixflag>>(cury-res->ystart)%8;
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
}




//NUM
unsigned char PixelCheckNumber(unsigned int curx,unsigned int cury,unsigned char color,G_Number *res)
{
	unsigned char buf[7];
	unsigned char data;
	unsigned char pixflag;
	unsigned char font_height,font_wide;
	unsigned int array_of_each_char;
	unsigned char font_pos_x;
	
	buf[6]=(res->number/1000000)%10;
	buf[5]=(res->number/100000)%10;
	buf[4]=(res->number/10000)%10;
	buf[3]=(res->number/1000)%10;
	buf[2]=(res->number/100)%10;
	buf[1]=(res->number/10)%10;
	buf[0]=res->number%10;
	
	font_height=res->ysize;
	font_wide=res->xsize;
	array_of_each_char=font_height/8;
	font_pos_x=(curx-res->xstart)%font_wide;

	if((curx>=res->xstart)&&(cury>=res->ystart)&&(res->color==color)&&res->enable)
	{
	unsigned int x_end,y_end;
	x_end=res->xstart+(res->xsize*res->numofnumber);
	y_end=res->ystart+res->ysize;
	if((curx<x_end)&&(cury<y_end))
		{
			pixflag=0x80;
			data=res->font[((cury-res->ystart)/8)+(  font_pos_x+ ( buf[(res->numofnumber-1)-((curx-res->xstart)/font_wide)] *font_wide)  ) *array_of_each_char];
			data&=pixflag>>(cury-res->ystart)%8;
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
}

//BATTERY
unsigned char PixelCheckBattrey(unsigned int curx,unsigned int cury,unsigned char color,G_Battery *res)
{
	unsigned char data;
	data=0;
	if((curx>=res->xstart)&&(cury>=res->ystart)&&(res->color==color)&&res->enable)
	{
	unsigned int x_end,y_end;
	unsigned int bat_siz_x,bat_siz_y;
	unsigned int bat_pos_x,bat_pos_y;
	unsigned int bat_inside_siz;
	x_end=res->xstart+res->xsize;
	y_end=res->ystart+res->ysize;
	
	bat_pos_x=curx-res->xstart;
	bat_pos_y=cury-res->ystart;
		
	bat_siz_x=res->xsize;
	bat_siz_y=res->ysize;		
		
	bat_inside_siz=(res->percent*(bat_siz_x-5))/100;

		if((curx<x_end)&&(cury<y_end))
		{
			if(res->dir)//帽子朝左
			{
				//电池帽子
				data|=( bat_pos_x==0&&bat_pos_y>((bat_siz_y/5)-1)&&bat_pos_y<(bat_siz_y-(bat_siz_y/5)) );
				//电池上边框
				data|=( bat_pos_y==0&&bat_pos_x>0 );
				//电池左边框
				data|=( bat_pos_x==1&&bat_pos_y>0 );
				//电池下边框
			  data|=( bat_pos_y==bat_siz_y-1&&bat_pos_x>0 );
				//电池右边框
				data|=( bat_pos_x==bat_siz_x-1&&bat_pos_y>0 );
			  //电池内芯
				data|=( (bat_pos_x>=(bat_siz_x-bat_inside_siz)-2) &&(bat_pos_x<bat_siz_x-2)&&(bat_pos_y>1)&&(bat_pos_y<bat_siz_y-2) );
				
				
			}
			else
			{
				//电池帽子
				data|=( bat_pos_x==(bat_siz_x-1)&&bat_pos_y>((bat_siz_y/5)-1)&&bat_pos_y<(bat_siz_y-(bat_siz_y/5)) );
				//电池右边框
				data|=( bat_pos_x==bat_siz_x-2&&bat_pos_y>0 );
				//电池左边框
				data|=( bat_pos_x==0&&bat_pos_y>0 );
				//电池上边框
				data|=( bat_pos_y==0&&bat_pos_x<bat_siz_x-1 );
				//电池下边框
				data|=( bat_pos_y==bat_siz_y-1&&bat_pos_x<bat_siz_x-1 );
				//电池内芯
				data|=( (bat_pos_x>1) &&(bat_pos_x<=bat_inside_siz+1)&&(bat_pos_y>1)&&(bat_pos_y<bat_siz_y-2) );	
			}
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
}

//BLOCK
unsigned char PixelCheckBlock(unsigned int curx,unsigned int cury,unsigned char color,G_Block *res)
{
	unsigned char data;
	if((curx>=res->xstart)&&(cury>=res->ystart)&&(res->color==color)&&res->enable)
	{
	unsigned int x_end,y_end;
	x_end=res->xstart+res->xsize;
	y_end=res->ystart+res->ysize;
	if((curx<x_end)&&(cury<y_end))
		{
			data=1;
		}
		else
		{
			data=0;
		}
	}
	else
	{
		data=0;
	}
	return data;
	
}



unsigned char PixelMatchingGcolor_black(unsigned int curx,unsigned int cury)
{
	unsigned char data;
	data=0;
	if(checkarea(curx,cury,pic1))data _mode_cover_ PixelCheckBMP(curx,cury,Gcolor_black,pic1);//匹配BMP
	if(checkarea(curx,cury,pic2))data _mode_trans_ PixelCheckBMP(curx,cury,Gcolor_black,pic2);//匹配BMP
	if(checkarea(curx,cury,pic3))data _mode_trans_ PixelCheckBMP(curx,cury,Gcolor_black,pic3);//匹配BMP
	data _mode_trans_ PixelCheckString(curx,cury,Gcolor_black,&str1);//匹配字符串
	data _mode_trans_ PixelCheckString(curx,cury,Gcolor_black,&str2);//匹配字符
	data _mode_trans_ PixelCheckString(curx,cury,Gcolor_black,&str3);//匹配字符
	
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_black,&bat1);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_black,&bat2);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_black,&bat3);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_black,&bat4);
	data _mode_trans_ PixelCheckIcon(curx,cury,Gcolor_black,&IconDegreeCelsius);//匹配BMP
	data _mode_trans_ PixelCheckIcon(curx,cury,Gcolor_black,&IconDegreeFahrenheit);//匹配BMP
	data _mode_trans_ PixelCheckIcon(curx,cury,Gcolor_black,&IconHumidity);//匹配BMP
	
	data _mode_trans_ PixelCheckNumber(curx,cury,Gcolor_black,&num1);//匹配BMP
	
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_black,&line2);
	
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_black,&line3);
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_black,&line4);
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_black,&line5);
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_black,&line6);
	


	data=(data? 0xff:0x00);
	return data;
}


unsigned char PixelMatchingGcolor_red(unsigned int curx,unsigned int cury)
{
	unsigned char data;
	data=0;
	data|=PixelCheckBMP(curx,cury,Gcolor_red,pic4);//匹配BMP
	data _mode_trans_ PixelCheckString(curx,cury,Gcolor_red,&str4);//匹配字符
	
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_red,&bat1);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_red,&bat2);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_red,&bat3);
	data _mode_trans_ PixelCheckBattrey(curx,cury,Gcolor_red,&bat4);
	
	data _mode_trans_ PixelCheckBlock(curx,cury,Gcolor_red,&line1);
	
	data=(data? 0xff:0x00);
	return data;
}

void EGuiSendBw(void)//黑白像素数据匹配与发送
{
	unsigned int curx,cury;          //当前所匹配的实时X/Y
	unsigned char bytepos;           //纵向扫描，8个像素拼成一个byte，此数据代表当前所在bit，0--7对应D7--D0
	unsigned char bytebuf;           //字节缓存，拼凑成一个byte后送给屏幕
	unsigned char byteflag;          //此数据用于字节移位          
	EPD_WriteCmd(EPD_Reg_BlackPix);  //写命令，地址选中黑白像素区域
	curx=0;                          //当前X坐标清零
	while(curx<EPD_WIDE)             //X小于屏幕宽度时循环处理
	{
		cury=0;                        //Y坐标起始或跑完0--127后清零
		while(cury<EPD_HEIGHT)         //屏幕IC为竖屏，作为横屏使用为纵向扫描，此处先处理Y，Y小于屏幕高度时循环处理
		{
			bytebuf=0x00;                     //清零字节缓存
			byteflag=0x80;                    //移位标记位置位
			for(bytepos=0;bytepos<8;bytepos++)//将像素匹配结果拼凑为字节，8个一组发送给屏幕
			{
				bytebuf|=(byteflag&PixelMatchingGcolor_black(curx,cury));//黑白像素匹配
				byteflag>>=1;                                  //高位在前，匹配一次标记位右移一个bit
				cury++;                                        //每匹配一次将Y自加，对应实际所在坐标，用于下次匹配
			}
			EPD_SendImageData(bytebuf);                      //上面for循环跑完后即凑够一个字节，发送给屏幕
		}
		curx++;//将X自加
	}
}

void EGuiSendRed(void)//红色像素数据匹配与发送
{
	unsigned int curx,cury;          //当前所匹配的实时X/Y
	unsigned char bytepos;           //纵向扫描，8个像素拼成一个byte，此数据代表当前所在bit，0--7对应D7--D0
	unsigned char bytebuf;           //字节缓存，拼凑成一个byte后送给屏幕
	unsigned char byteflag;          //此数据用于字节移位          
	EPD_WriteCmd(EPD_Reg_RedPix);  //写命令，地址选中黑白像素区域
	curx=0;                          //当前X坐标清零
	while(curx<EPD_WIDE)             //X小于屏幕宽度时循环处理
	{
		cury=0;                        //Y坐标起始或跑完0--127后清零
		while(cury<EPD_HEIGHT)         //屏幕IC为竖屏，作为横屏使用为纵向扫描，此处先处理Y，Y小于屏幕高度时循环处理
		{
			bytebuf=0x00;                     //清零字节缓存
			byteflag=0x80;                    //移位标记位置位
			for(bytepos=0;bytepos<8;bytepos++)//将像素匹配结果拼凑为字节，8个一组发送给屏幕
			{
				bytebuf|=(byteflag&PixelMatchingGcolor_red(curx,cury));//黑白像素匹配
				byteflag>>=1;                                  //高位在前，匹配一次标记位右移一个bit
				cury++;                                        //每匹配一次将Y自加，对应实际所在坐标，用于下次匹配
			}
			EPD_SendImageData(bytebuf);                      //上面for循环跑完后即凑够一个字节，发送给屏幕
		}
		curx++;//将X自加
	}
}

void EGuiWidgetSetPicture(unsigned int xstart, unsigned int ystart, \
	                   unsigned int xsize, unsigned int ysize,   \
										 unsigned char color, unsigned char enable, \
										 const unsigned char *pic, G_Picture *res)
{

	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->color=color;
	res->enable=enable;
	res->pic=pic;
}

void EGuiWidgetSetIcon(unsigned int xstart, unsigned int ystart, \
	                   unsigned int xsize, unsigned int ysize,   \
										 unsigned char color, unsigned char enable, \
										 const unsigned char *pic, G_Icon *res)
{

	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->color=color;
	res->enable=enable;
	res->pic=pic;
}

void EGuiWidgetSetString(unsigned int xstart, unsigned int ystart, \
	                   unsigned int xsize, unsigned int ysize,   \
										 unsigned char color, unsigned char enable, \
										 const unsigned char *font, \
										 char str[], G_String *res)
{
	unsigned char pos;
	pos=0;
	while(str[pos]!='\0')
	{
		res->strbuf[pos]=str[pos];
		if(pos<MAX_SIZE_OF_STRING)
		{
		pos+=1;
		res->numofstring=pos;
		}
	}
	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->font=font;
	res->color=color;
	res->enable=enable;
}


void EGuiWidgetSetNumber(unsigned int xstart, unsigned int ystart, \
	                   unsigned int xsize, unsigned int ysize,   \
										 unsigned char color, unsigned char enable, \
										 const unsigned char *font, unsigned char numofnumber, \
										 unsigned long  number, G_Number *res )
{
	
	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->font=font;
	res->color=color;
	res->enable=enable;
	res->numofnumber=numofnumber;
	res->number=number;
}


void EGuiWidgetSetBattery(unsigned int xstart,   unsigned int ystart,  \
	                        unsigned int xsize,    unsigned int ysize,   \
													unsigned char color,   unsigned char enable, \
										      unsigned char dir,    \
													unsigned char percent, G_Battery *res)												
{
	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->dir=dir;
	res->color=color;
	res->enable=enable;
	res->percent=percent;
}


void EGuiWidgetSetBlock(unsigned int xstart, unsigned int ystart,  \
	                      unsigned int xsize, unsigned int ysize,    \
										    unsigned char color, unsigned char enable, \
										    G_Block *res)
{
	res->xstart=xstart;
	res->ystart=ystart;
	res->xsize=xsize;
	res->ysize=ysize;
	res->color=color;
	res->enable=enable;
}


void EGuiInit(void)
{
  
 
	EGuiWidgetSetPicture ( 50  , 17 , 40 , 40 , Gcolor_black , Widget_show , EPD_BMP_TEST , &pic2 );
	EGuiWidgetSetPicture ( 91  , 17 , 40 , 40 , Gcolor_red   , Widget_show , EPD_BMP_TEST , &pic4 );
	
  //EGuiWidgetSetString  ( 2   , 57 , 8  , 16 , Gcolor_black , Widget_show , EPD_ASC0816  ,"ASCII Font 8*16 WidgetStr"      , &str1 );
  //EGuiWidgetSetString  ( 2   , 73 , 12 , 24 , Gcolor_black , Widget_show , EPD_ASC1224  ,"ASCII Font 12*24"               , &str2 );
	//EGuiWidgetSetString  ( 2   , 97 , 16 , 32 , Gcolor_black , Widget_show , EPD_ASC1632  ,"ASCII Font 16*32"               , &str3 );
	EGuiWidgetSetString  ( 30  , 0  , 8  , 16 , Gcolor_red   , Widget_show , EPD_ASC0816  ,"EGUI b0.1 Based on STM32F030F4" , &str4 );

	EGuiWidgetSetBattery ( 5   , 16 , 40 , 20 , Gcolor_black , Widget_show , Gbatt_right  ,75 , &bat1 );
	EGuiWidgetSetBattery ( 5   , 37 , 40 , 20 , Gcolor_black , Widget_show , Gbatt_left   ,75 , &bat2 );
	EGuiWidgetSetBattery ( 1   , 1  , 20 , 10 , Gcolor_black , Widget_show , Gbatt_right  ,50 , &bat3 );
	EGuiWidgetSetBattery ( 275 , 1  , 20 , 10 , Gcolor_red   , Widget_show , Gbatt_left   ,50 , &bat4 );
	
	EGuiWidgetSetIcon    ( 128 , 17 , 32 , 36 , Gcolor_black , Widget_show , EPD_Icon_DegreeCelsius3236    , &IconDegreeCelsius    );
	EGuiWidgetSetIcon    ( 160 , 17 , 32 , 36 , Gcolor_black , Widget_show , EPD_Icon_DegreeFahrenheit3236 , &IconDegreeFahrenheit );
	EGuiWidgetSetIcon    ( 192 , 17 , 32 , 36 , Gcolor_black , Widget_show , EPD_Icon_PercentRH            , &IconHumidity         );

	EGuiWidgetSetNumber  ( 2   , 64 , 40 , 64 , Gcolor_black , Widget_show , EPD_Num_4064 , 7 , 1234567 ,&num1);
	
	EGuiWidgetSetBlock   ( 0   , 60 , 296 , 3  , Gcolor_red  , Widget_show ,&line1);
	
	EGuiWidgetSetBlock   ( 260 , 17 , 3   , 42 , Gcolor_black, Widget_show ,&line2);
	
	EGuiWidgetSetBlock   ( 232 , 25 , 64  , 1  , Gcolor_black, Widget_show ,&line3);
	EGuiWidgetSetBlock   ( 232 , 31 , 64  , 2  , Gcolor_black, Widget_show ,&line4);
	EGuiWidgetSetBlock   ( 232 , 38 , 64  , 3  , Gcolor_black, Widget_show ,&line5);
	EGuiWidgetSetBlock   ( 232 , 46 , 64  , 4  , Gcolor_black, Widget_show ,&line6);
	


}


void EGuiUpdate(void)
{
	EGuiSendBw();
	EGuiSendRed();
	EPD_WriteCmd(EPD_Reg_Refresh);
}





