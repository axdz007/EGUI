# EGUI
当前版本：b0.1  
    An EPD Driver for GOOD-DISPLAY 2.9-Inch B-W-G color screen without full_screen buffer,to use low-end microprocessor like STM32F030F4P6.   
佳显2.9寸三色EPD驱动，牺牲处理速度但无需开全屏缓冲，以便使用低RAM单片机，比如STM32F030F4P6。  
调用：显示驱动"GDEW029Z10.h"中的EPD_Init()，"GDEW029Z10_GUI.h"中的EGuiInit()与EGuiUpdate()即可按照设置好的GUI刷新屏幕。  
        
