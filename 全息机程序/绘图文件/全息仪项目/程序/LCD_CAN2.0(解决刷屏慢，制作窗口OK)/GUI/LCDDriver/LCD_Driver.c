#include "stm32f10x_conf.h"
#include "LCD_Driver.h"
#include "string.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //Disp Data ADDR  RAM
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //Disp Reg ADDR 

static void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable the FSMC Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    
    /* config lcd gpio clock base on FSMC */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		
    GPIO_Init(GPIOD, &GPIO_InitStructure);    //PD13?aresetD?o?￡?????3é?aí?íìê?3?
    
    /* config tft BL gpio */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 	 
    GPIO_Init(GPIOC, &GPIO_InitStructure);  	//PC5?aPWMD?o?￡?????3é?aí?íìê?3?	   
    
    /* config tft data lines base on FSMC
	 * data lines,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10
	 */	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    /* config tft control lines base on FSMC
	 * PD4-FSMC_NOE  :LCD-RD
   * PD5-FSMC_NWE  :LCD-WR
	 * PD7-FSMC_NE1  :LCD-CS
   * PD11-FSMC_A16 :LCD-C&D
	   PD13-RESET    :LCD-RST
	 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    /* tft control gpio init */	 
    GPIO_SetBits(GPIOD, GPIO_Pin_13);		 // RST				
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		 // RD = 1  
    GPIO_SetBits(GPIOD, GPIO_Pin_5);		 // WR = 1 
		GPIO_SetBits(GPIOD, GPIO_Pin_11);		 // RS = 1
    GPIO_SetBits(GPIOD, GPIO_Pin_7);		 //	CS = 1

		GPIO_SetBits(GPIOC, GPIO_Pin_5);	 	 //	BL = 1 
		
		
	/*	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;		
    GPIO_Init(GPIOA, &GPIO_InitStructure);  */
}
static void LCD_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p; 
    
    
    p.FSMC_AddressSetupTime = 0x02;	 //μ??·?¨á￠ê±??
    p.FSMC_AddressHoldTime = 0x00;	 //μ??·±￡3?ê±??
    p.FSMC_DataSetupTime = 0x05;		 //êy?Y?¨á￠ê±??
    p.FSMC_BusTurnAroundDuration = 0x00;
    p.FSMC_CLKDivision = 0x00;
    p.FSMC_DataLatency = 0x00;

    p.FSMC_AccessMode = FSMC_AccessMode_B;	 // ò?°?ê1ó??￡ê?Bà′????LCD
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p; 
    
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
    
    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}
 void LCD_delay(char j)  //1ms delay volatile
{
    volatile u16 i;	
	  while(j--)
    for(i=5143;i>0;i--);
}
static void LCD_Rst(void)
{			
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    LCD_delay(10);					   
    GPIO_SetBits(GPIOD, GPIO_Pin_13 );		 	 
    LCD_delay(10);	
}
static void WriteCmd(unsigned short CMD)
{			
	  *(__IO u16 *) (Bank1_LCD_C) = CMD;
}
static void WriteData(unsigned short tem_data)
{			
	  *(__IO u16 *) (Bank1_LCD_D) = tem_data;
}	
/**************************************************************************************************************
 * 函数名：LCD_WriteReg()
 * 输入  ：uint8_t LCD_Reg 寄存器地址, uint16_t LCD_RegValue 寄存器的值
 * 输出  ：void
 * 描述  ：写LCD寄存器函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /*写寄存器地址*/
	*(__IO u16 *) (Bank1_LCD_C) = LCD_Reg;
  /*写入寄存器值*/
	*(__IO u16 *) (Bank1_LCD_D) = LCD_RegValue;
}
/**************************************************************************************************************
 * 函数名：LCD_ReadReg()
 * 输入  ：uint8_t LCD_Reg 需要读取的寄存器地址
 * 输出  ：uint16_t 寄存器的值
 * 描述  ：读取LCD寄存器的值
 * 调用  ：外部调用        
 *****************************************************************************************************************/
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
  /*写寄存器地址*/
  *(__IO u16 *) (Bank1_LCD_C) = LCD_Reg;
  /*读出寄存器值并返回*/
  return (*(__IO u16 *)Bank1_LCD_D);
}
/**************************************************************************************************************
 * 函数名：LCD_SetCursor()
 * 输入  ：uint16_t Xpos, uint16_t Ypos 设定的屏幕的X值和Y值
 * 输出  ：void
 * 描述  ：LCD设置光标位置函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
//	WriteCmd(0x2a);   
//	WriteData(Xpos>>8);
//	WriteData(Xpos&0xff);
//	WriteData((Xpos+1)>>8);
//	WriteData((Xpos+1)&0xff);

//	WriteCmd(0x2b);   
//	WriteData(Ypos>>8);
//	WriteData(Ypos&0xff);
//	WriteData((Ypos+1)>>8);
//	WriteData((Ypos+1)&0xff);
//	
//	WriteCmd(0x2c);
	
		WriteCmd(0x2a);   
	WriteData(Xpos>>8);
	WriteData(Xpos&0xff);
	WriteData((Xpos)>>8);
	WriteData((Xpos)&0xff);

	WriteCmd(0x2b);   
	WriteData(Ypos>>8);
	WriteData(Ypos&0xff);
	WriteData((Ypos)>>8);
	WriteData((Ypos)&0xff);
	
	WriteCmd(0x2c);
}
void set_position(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
{
	//HX8352-C

	WriteCmd(0x2a);   
	WriteData(Xstart>>8);
	WriteData(Xstart&0xff);
	WriteData(Xend>>8);
	WriteData(Xend&0xff);

	WriteCmd(0x2b);   
	WriteData(Ystart>>8);
	WriteData(Ystart&0xff);
	WriteData(Yend>>8);
	WriteData(Yend&0xff);
	
	WriteCmd(0x2c);
}
/***************************************************************
*填充一个像素，带颜色
*Xpos和Ypos是坐标点
*Color是颜色值
****************************************************************/
void lcd_wr_point(unsigned int Xpos,unsigned int Ypos,unsigned int Color)
{
	LCD_SetCursor(Xpos,Ypos);
	*(__IO u16 *) (Bank1_LCD_D) = Color;
}

/***************************************************************
*读出一个点的颜色
*x和y是坐标点 
****************************************************************/ 
unsigned int lcd_get_point(unsigned int Xpos,unsigned int Ypos)
{ 
	unsigned int temp=0;//,temp_R=0,temp_G=0,temp_B=0
	LCD_SetCursor(Xpos,Ypos);

//	WriteCmd(0x2e);
//	temp=*(__IO u16 *) (Bank1_LCD_D);//读取的第一个数，无效 
//	temp=*(__IO u16 *) (Bank1_LCD_D);
	
	return (((temp&0x001f)<<11)|(temp&0x07e0)|((temp&0xf800)>>11));
}
/****************************************************************
*中层功能函数，将一块区域用某种颜色覆盖
*****************************************************************/
void Lcd_ColorBox(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong,unsigned short Color) 
{
	u32 temp;

	set_position(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	for (temp=0; temp<xLong*yLong; temp++)
	{
		*(__IO u16 *) (Bank1_LCD_D) = Color;
	}
}
void Dis_image(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong,const unsigned char *image)
{
	unsigned short H_count,V_count;	   
	unsigned short i=0,j=0;
	i=xLong*2;
	set_position(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	for(H_count=0;H_count<yLong;H_count++)
	{
		 for(V_count=0;V_count<i;V_count=V_count+2)
		 {
				j=(image[i-1+H_count*i-V_count-1]<<8)+image[i-1+H_count*i-V_count];
				*(__IO u16 *) (Bank1_LCD_D)=j;
		 }
	}
	 //4位灰度时使用
	 /* for(H_count=0;H_count<320;H_count++)
	  {
      for(V_count=0;V_count<120;V_count++)
			{
        i=gImage_111[119+H_count*120-V_count];
				*(__IO u16 *) (Bank1_LCD_D) = log_color[i&0x03] ;
				*(__IO u16 *) (Bank1_LCD_D) = log_color[(i&0x0c)>>2] ;
				*(__IO u16 *) (Bank1_LCD_D) = log_color[(i&0x30)>>4] ;
				*(__IO u16 *) (Bank1_LCD_D) = log_color[(i&0xc0)>>6] ;
      }
    } */
	  //16位灰度时使用
//	  for(H_count=0;H_count<320;H_count++)
//	  {
//       for(V_count=0;V_count<960;V_count=V_count+2)
//			 {
//          j=(image[959+H_count*960-V_count-1]<<8)+image[959+H_count*960-V_count];
//				  *(__IO u16 *) (Bank1_LCD_D)=j;
//       }
//    }
	
}
void LCD_test()
{
	unsigned char i;
	for(i=0;i<100;i++)
	{
		lcd_wr_point(10,150,0xf800);
		lcd_wr_point(300+i,150,lcd_get_point(10,150));
	}
}
void LCD_Setup(void)
{
   
	  
	  LCD_GPIO_Config();
    LCD_FSMC_Config();
    LCD_delay(20);   
    LCD_Rst();
	
	  WriteCmd(0x11);
		LCD_delay(20);     //延迟20ms
		WriteCmd(0xD0);
		WriteData(0x07);
		WriteData(0x42);
		WriteData(0x18);
		
		WriteCmd(0xD1);
		WriteData(0x00);
		WriteData(0x07);//07
		WriteData(0x10);
		
		WriteCmd(0xD2);
		WriteData(0x01);
		WriteData(0x02);
		
		WriteCmd(0xC0);
		WriteData(0x10);
		WriteData(0x3B);
		WriteData(0x00);
		WriteData(0x02);
		WriteData(0x11);
		
//		WriteCmd(0x0D);
//		WriteData(0x10);
//		WriteData(0x10);
		
		WriteCmd(0xC5);
		WriteData(0x03);

	  WriteCmd(0x00C8);//Gamma Setting，有12个参数，P114
	  WriteData(0x0000);//P114
	  WriteData(0x0014);//P114
	  WriteData(0x0033);//P114
	  WriteData(0x0010);//P114
	  WriteData(0x0000);//P114
	  WriteData(0x0016);//P114
	  WriteData(0x0044);//P114
	  WriteData(0x0036);//P114
  	WriteData(0x0077);//P114
	  WriteData(0x0000);//P114
	  WriteData(0x000F);//P114
	  WriteData(0x0000);//P114
		
		WriteCmd(0x36);
		WriteData(0x0A);
		
		WriteCmd(0x3A);
		WriteData(0x55);
		
		WriteCmd(0x2A);
		WriteData(0x00);
		WriteData(0x00);
		WriteData(0x01);
		WriteData(0x3f);
		
		WriteCmd(0x2B);
		WriteData(0x00);
		WriteData(0x00);
		WriteData(0x01);
		WriteData(0xE0);
		LCD_delay(120);     //延迟120ms
		WriteCmd(0x29);
		WriteCmd(0x002c);

    LCD_delay(10);
		WriteCmd(0x36); //Set_address_mode
   	WriteData(0x68); //横屏，从左下角开始，从左到右，从下到上
	  GPIO_SetBits(GPIOC, GPIO_Pin_5); 
		
		//LCD_test();//初始化测试
}

