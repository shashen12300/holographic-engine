#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

#define  gpioOutBit(GPIOp,BIT)  (*((unsigned int *)(((unsigned  int )(&GPIOp->ODR)-0X40000000)*32+BIT*4+0X42000000)))
#define  gpioInBit(GPIOp,BIT)   (*((unsigned int *)(((unsigned  int )(&GPIOp->IDR)-0X40000000)*32+BIT*4+0X42000000)))


#define LED_OUT(a)	gpioOutBit(GPIOC,9)=a
#define LCD_RS(a)	gpioOutBit(GPIOB,12)=a
					
#define LCD_WR(a)	gpioOutBit(GPIOB,13)=a
#define LCD_RD(a)	gpioOutBit(GPIOB,14)=a
#define LCD_CS(a)	gpioOutBit(GPIOB,15)=a
#define LCD_RST(a)	gpioOutBit(GPIOC,12)=a			


#define LCD_BUSY		(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
					
//#define WRITE_DATA(data)   GPIO_Write(GPIOC, data)			
#define WRITE_DATA(data)   GPIOC->ODR&=0XFF00,GPIOC->ODR|=data&0X00FF				
				
#define READ_DATA    (GPIOC->ODR&0x00ff)

//#define LED_OUT(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_5)
//					
//#define LCD_RS(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_12)
//					
//#define LCD_WR(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_13)
//					
//#define LCD_RD(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_14)
//					
//#define LCD_CS(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_15)
//					
//#define LCD_RST(a)	if (a)	\
//					GPIO_SetBits(GPIOC,GPIO_Pin_12);\
//					else		\
//					GPIO_ResetBits(GPIOC,GPIO_Pin_12)
//					
//#define LCD_BUSY		(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
//					
////#define WRITE_DATA(data)   GPIO_Write(GPIOC, data)
//#define WRITE_DATA(data)   GPIOC->ODR&=0XFF00,GPIOC->ODR|=data&0X00FF
//					
//#define READ_DATA    (GPIO_ReadInputData(GPIOC)&0x00ff)
					
void lcd_wr_point(unsigned int Xpos,unsigned int Ypos,unsigned int Color);
unsigned int lcd_get_point(unsigned int Xpos,unsigned int Ypos);
/****************************************************************
*中层功能函数，将一块区域用某种颜色覆盖
*****************************************************************/
void Lcd_ColorBox(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong,unsigned short Color) ;
void Dis_image(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong, const unsigned char *image);
void LCD_Setup(void);
void LCD_GPIO_Config(void);
void LCD_GPIOC_input(void);
void LCD_GPIOC_output(void);

#endif
