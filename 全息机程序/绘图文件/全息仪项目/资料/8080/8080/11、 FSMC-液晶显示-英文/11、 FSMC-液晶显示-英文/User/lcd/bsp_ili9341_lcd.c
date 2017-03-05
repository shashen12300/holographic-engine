#include "bsp_ili9341_lcd.h"
#include "ascii.h"
#include "bmp.h"






#define DEBUG_DELAY()

void Lcd_Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

 /**
  * @brief  初始化控制LcD的IO
  * @param  无
  * @retval 无
  */
void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 使能FSMC时钟*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD 
                            | RCC_APB2Periph_GPIOE 
	                          | RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    /* 配置LCD背光控制管脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* 配置LCD复位控制管脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 	 
    GPIO_Init(GPIOE, &GPIO_InitStructure);  		   
    
    /* 配置FSMC相对应的数据线,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10*/	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
		/* 配置FSMC相对应的控制线
		 * PD4-FSMC_NOE   :LCD-RD
		 * PD5-FSMC_NWE   :LCD-WR
		 * PD7-FSMC_NE1   :LCD-CS
		 * PD11-FSMC_A16  :LCD-DC
		*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    /* tft control gpio init */	 
    /* 开背光 */
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);  
}

 /**
  * @brief  LCD  FSMC 模式配置
  * @param  无
  * @retval 无
  */
void LCD_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p; 
    
    
    p.FSMC_AddressSetupTime = 0x02;	 //地址建立时间
    p.FSMC_AddressHoldTime = 0x00;	 //地址保持时间
    p.FSMC_DataSetupTime = 0x05;		 //数据建立时间
    p.FSMC_BusTurnAroundDuration = 0x00;
    p.FSMC_CLKDivision = 0x00;
    p.FSMC_DataLatency = 0x00;
    p.FSMC_AccessMode = FSMC_AccessMode_B;	 // 一般使用模式B来控制LCD
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    //FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
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
    
    /* 使能 FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

/**
 * @brief  LCD 软件复位
 * @param  无
 * @retval 无
 */
void LCD_Rst(void)
{			
		GPIO_ResetBits(GPIOE, GPIO_Pin_1);	 //低电平复位
    Lcd_Delay(0xAFFf<<2); 					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1);		 	 
    Lcd_Delay(0xAFFf<<2); 	
}

/**
 * @brief  配置lcd初始化寄存器
 * @param  无
 * @retval 无
 */


/*
void LCD_PutChar_12_24(u16 x, u16 y, u8 c, u16 fColor, u16 bColor)
{
  unsigned int i,j;
	unsigned char m1;
	unsigned char m2;
	unsigned short m;
  set_position(x-12+1,x,y-24+1,y);
  for(i=0; i<24;i++)
	{
		m=(my_ASC[c*48+i*2]<<8)|my_ASC[c*48+i*2+1];  //高12位有效
		
		
		for(j=0;j<12;j++) 
		{
			if((m&0x0010)==0x0010) 
			{
				*(__IO u16 *) (Bank1_LCD_D)=fColor;
			}
			else
			{
				*(__IO u16 *) (Bank1_LCD_D)=bColor;
			}
			m>>=1;
		}
	}
}

*/
void LCD_REG_Config(void)
{
	unsigned short aa[6];
	unsigned short ii;
	unsigned int jj;
	unsigned short kk;
	unsigned char *s="TFT2K2056";
	unsigned char s1='2';
	unsigned char gen_zifu[288];
	unsigned char xieru[144];
	unsigned short m;
	unsigned char cc;
	unsigned char pos_x;
	unsigned short pos_y;
	unsigned char offset=0;
	
	/*  Power control B (CFh)  */
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x5e);                 //软件复位
	LCD_ILI9341_Parameter(0xa5);
	
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x91);                 //x、y方向都显示320*320
	LCD_ILI9341_Parameter(0x01);
	LCD_ILI9341_Parameter(0x3f);
	LCD_ILI9341_Parameter(0x01);
	LCD_ILI9341_Parameter(0x3f); 
	
	DEBUG_DELAY();                         //内部RAM设置
	LCD_ILI9341_CMD(0x21);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY();
	for(ii=0;ii<50000;ii++);
	for(ii=0;ii<50000;ii++);
	for(ii=0;ii<50000;ii++);
	
	LCD_ILI9341_CMD(0x24);                    //帧设置 为00
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x25);                   //bpp设置 4bit模式
	LCD_ILI9341_Parameter(0x02);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	
	/*  Power control A (CBh) */
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x26);                  //数据屏蔽 不屏蔽
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x49);
	LCD_ILI9341_Parameter(0x0a);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	
	DEBUG_DELAY();                        //扫描模式
	LCD_ILI9341_CMD(0xa2);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	LCD_ILI9341_Parameter(0xa5);
	
	
	
	DEBUG_DELAY();
  LCD_ILI9341_CMD(0x15);                 //退出翻转模式
	LCD_ILI9341_Parameter(0xa5);
	
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x13);
	LCD_ILI9341_Parameter(0xa5);
	DEBUG_DELAY();
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x22);                 //页地址设置
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x9f);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	DEBUG_DELAY();
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x23);                 //设置column显示的起始和终止地址
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x01);
	LCD_ILI9341_Parameter(0x3f);

	/* Driver timing control B */
	
	
	DEBUG_DELAY();                         //写RAM
	LCD_ILI9341_CMD(0x3a);
	LCD_ILI9341_Parameter(0xa5);
	
	
	for(ii=0;ii<6400;ii++)
	{
    LCD_ILI9341_Parameter(0xff);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=6400;ii<12800;ii++)
	{
    LCD_ILI9341_Parameter(0x00);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=12800;ii<19200;ii++)
	{
    LCD_ILI9341_Parameter(0xff);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=19200;ii<25600;ii++)
	{
    LCD_ILI9341_Parameter(0x00);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=25600;ii<32000;ii++)
	{
    LCD_ILI9341_Parameter(0xff);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=32000;ii<38400;ii++)
	{
    LCD_ILI9341_Parameter(0x00);
	//	LCD_ILI9341_Parameter(0xff);
  }
	for(ii=38400;ii<44800;ii++)
	{
    LCD_ILI9341_Parameter(0xff);
	//	LCD_ILI9341_Parameter(0xff);
  }
		for(ii=44800;ii<51200;ii++)
	{
    LCD_ILI9341_Parameter(0x00);
	//	LCD_ILI9341_Parameter(0xff);
  }
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x12);
	LCD_ILI9341_Parameter(0xa5);
	/*for(ii=960;ii<102400;ii++)
	{
    LCD_ILI9341_Parameter(0xff);
		LCD_ILI9341_Parameter(0xff);
  }*/
	 
	DEBUG_DELAY();                         //写RAM
	LCD_ILI9341_CMD(0x3a);
	LCD_ILI9341_Parameter(0xa5);
	for(kk=0;kk<10;kk++)
	{
    for(ii=0;ii<16;ii++)
	  {
       for(jj=0;jj<320;jj++)
			 LCD_ILI9341_Parameter(ii); 
    }
  }
	
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x12);
	LCD_ILI9341_Parameter(0xa5);
	
	
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x22);                 //页地址设置
	LCD_ILI9341_Parameter(12);
	LCD_ILI9341_Parameter(23);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xa5);
	DEBUG_DELAY();
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x23);                 //设置column显示的起始和终止地址
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(12);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(23);
	
	DEBUG_DELAY();                         //写RAM
	LCD_ILI9341_CMD(0x3a);
	LCD_ILI9341_Parameter(0xa5);
	for(ii=0;ii<144;ii++)
	{
     	LCD_ILI9341_Parameter(0xff);
  }
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x12);
	LCD_ILI9341_Parameter(0xa5);
	
	for(ii=0; ii<24;ii++)
	{
		m=(my_ASC[s1*48+ii*2]<<8)|my_ASC[s1*48+ii*2+1];  //高12位有效
		
		
		for(jj=0;jj<12;jj++) 
		{
			if((m&0x8000)==0x8000) 
			{
				gen_zifu[ii*12+jj]=0x00;
			}
			else
			{
				gen_zifu[ii*12+jj]=0xff;
			}
			m<<=1;
		}
	}
  for(ii=0;ii<12;ii++)
	{
     for(jj=0;jj<12;jj++)
		 {
        xieru[ii*12+jj]= (gen_zifu[ii*24+jj]&0x0f)|(gen_zifu[ii*24+jj+12]&0xf0);
     }
  }
	LCD_ILI9341_CMD(0x3a);
	LCD_ILI9341_Parameter(0xa5);
	for(ii=0;ii<144;ii++)
	{
     	LCD_ILI9341_Parameter(xieru[ii]);
  }
	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x12);
	LCD_ILI9341_Parameter(0xa5);
	//xieru
	
	
	pos_x=0;
	pos_y=0;
	offset=0;

	for(kk=0;kk<13;kk++)
	{
	pos_y=0;
	offset=0;
	pos_x=12*kk;
	s="TFT2K2056";
	while(*s)
	{   
		  
		  pos_y=0+offset*12;
		  DEBUG_DELAY();
	    LCD_ILI9341_CMD(0x22);                 //页地址设置
    	LCD_ILI9341_Parameter(pos_x);
	    LCD_ILI9341_Parameter(pos_x+11);
	    LCD_ILI9341_Parameter(0x00);
	    LCD_ILI9341_Parameter(0xa5);
	    DEBUG_DELAY();
		  LCD_ILI9341_CMD(0x23);                 //设置column显示的起始和终止地址
		 LCD_ILI9341_Parameter((pos_y&0xff00)>>8);
	    LCD_ILI9341_Parameter(pos_y&0x00ff);
	    LCD_ILI9341_Parameter(((pos_y+11)&0xff00)>>8);
	    LCD_ILI9341_Parameter((pos_y+11)&0x00ff);
	   
      cc=*s;
		  s++;
		  offset++;
		  for(ii=0; ii<24;ii++)
			{
				m=(my_ASC[cc*48+ii*2]<<8)|my_ASC[cc*48+ii*2+1];  //高12位有效
				
				
				for(jj=0;jj<12;jj++) 
				{
					if((m&0x8000)==0x8000) 
					{
						gen_zifu[ii*12+jj]=0x00;
					}
					else
					{
						gen_zifu[ii*12+jj]=0xff;
					}
					m<<=1;
				}
			}
			for(ii=0;ii<12;ii++)
			{
				 for(jj=0;jj<12;jj++)
				 {
						xieru[ii*12+jj]= (gen_zifu[ii*24+jj]&0x0f)|(gen_zifu[ii*24+jj+12]&0xf0);
				 }
			}
			LCD_ILI9341_CMD(0x3a);
			LCD_ILI9341_Parameter(0xa5);
			for(ii=0;ii<144;ii++)
			{
					LCD_ILI9341_Parameter(xieru[ii]);
			}
			DEBUG_DELAY();
			LCD_ILI9341_CMD(0x12);
			LCD_ILI9341_Parameter(0xa5);
	}
	
}
		
	
}

/**
 * @brief  lcd初始化，如果要用到lcd，一定要调用这个函数
 * @param  无
 * @retval 无
 */
void LCD_Init(void)
{
	LCD_GPIO_Config();
	LCD_FSMC_Config();
	
	LCD_Rst();
	LCD_REG_Config();
}

void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
	uint32_t i = 0;
	
	/* column address control set */
	LCD_ILI9341_CMD(0X2A);
	LCD_ILI9341_Parameter( x >> 8 );	 /* 先高8位，然后低8位 */
	LCD_ILI9341_Parameter( x & 0xff );	         /* column start   */ 
	LCD_ILI9341_Parameter( (x+width-1) >> 8 );   /* column end   */
	LCD_ILI9341_Parameter( (x+width-1) & 0xff );
	
	/* page address control set */	
  LCD_ILI9341_CMD(0X2B); 			     
	LCD_ILI9341_Parameter( y >> 8 );			/* page start   */
	LCD_ILI9341_Parameter( y & 0xff );
	LCD_ILI9341_Parameter( (y+height-1) >> 8);  /* page end     */
	LCD_ILI9341_Parameter( (y+height-1) & 0xff);
	
	/* memory write */
	LCD_ILI9341_CMD(0x2c);	
		
	for( i=0; i < width*height; i++ )
	{
		LCD_WR_Data( color );
		//Delay(0x0FFf);
	}	
}

void LCD_SetCursor(uint16_t x, uint16_t y)	
{	
	LCD_ILI9341_CMD(0X2A); 				 /* 设置X坐标 */
	LCD_ILI9341_Parameter(x>>8);	 /* 先高8位，然后低8位 */
	LCD_ILI9341_Parameter(x&0xff);	 /* 设置起始点和结束点*/
	LCD_ILI9341_Parameter(x>>8);
	LCD_ILI9341_Parameter(x&0xff);

    LCD_ILI9341_CMD(0X2B); 			     /* 设置Y坐标*/
	LCD_ILI9341_Parameter(y>>8);
	LCD_ILI9341_Parameter(y&0xff);
	LCD_ILI9341_Parameter(y>>8);
	LCD_ILI9341_Parameter(y&0xff);		     
}

//  _ _ _ _ _ _
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
// |           |
//  - - - - - -
void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{	
	LCD_ILI9341_CMD(0X2A); 				 /* 设置X坐标 */
	LCD_ILI9341_Parameter( x >> 8 );	 /* 先高8位，然后低8位 */
	LCD_ILI9341_Parameter( x & 0xff );	 /* 设置起始点和结束点*/
	LCD_ILI9341_Parameter( (x+width-1) >> 8 );
	LCD_ILI9341_Parameter( (x+width-1) & 0xff );

	LCD_ILI9341_CMD(0X2B); 			     /* 设置Y坐标*/
	LCD_ILI9341_Parameter( y >> 8 );
	LCD_ILI9341_Parameter( y & 0xff );
	LCD_ILI9341_Parameter( (y+height-1) >> 8);
	LCD_ILI9341_Parameter( (y+height-1) & 0xff);
}

void LCD_SetPoint(uint16_t x , uint16_t y , uint16_t color)	
{	
	LCD_SetCursor(x, y);
	LCD_ILI9341_CMD(0x2c);	         /* 写数据 */
	LCD_WR_Data(color);
}

uint16_t LCD_RD_data(void)	
{	
	uint16_t R=0, G=0, B=0 ;

	R = *(__IO uint16_t *)Bank1_LCD_D; 	  /*FIRST READ OUT DUMMY DATA*/
	R = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT RED DATA  */
	B = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT BLACK DATA*/
	G = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT GREEN DATA*/
	
    return (((R>>11)<<11) | ((G>>10)<<5) | (B>>11));
}

uint16_t LCD_GetPoint(uint16_t x , uint16_t y)
{ 
	uint16_t temp;

	LCD_SetCursor(x, y);
	LCD_ILI9341_CMD(0x2e);         /* 读数据 */
	temp=LCD_RD_data();
	return (temp);
}

void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color)
{
	uint16_t page, column, temp, i;
	i = ascii - ' ';
	
	LCD_OpenWindow(x, y, STR_WIDTH, STR_HEIGHT);
	LCD_ILI9341_CMD(0X2C);	
	
	for( page=0; page < STR_HEIGHT; page++ )
	{
		temp = asc2_1206[i][page];
		for( column=0; column < STR_WIDTH; column++ )
		{
			if( temp & 0x01 )
			{
				LCD_WR_Data( color );
			}
			else
			{
				LCD_WR_Data( BACKGROUND );								
			}
			temp >>= 1;		
		}/* 一行写完 */
	}/* 全部写完 */
}

void LCD_DispStr(uint16_t x, uint16_t y, uint8_t *pstr, uint16_t color)
{
	while( *pstr != '\0' )
	{
		if( x > (COLUMN-STR_WIDTH) )
		{
			x = 0;
			y += STR_HEIGHT;
		}
		if( y > (PAGE-STR_HEIGHT) )
		{
			x = 0;
			y = 0;
		}
		LCD_DispChar(x, y, *pstr, color);
		x += STR_WIDTH;
		pstr++;
	}
}

//  temp = 345   length = 0
//  34           1
//  3            2
//  0            3


//  0    6    12
//  ____ ____ ____
void LCD_DisNum(uint16_t x, uint16_t y, uint32_t num, uint16_t color)
{
	uint32_t length = 0, temp = 0;
	temp = num;
	
	if( temp == 0 )
	{
		LCD_DispChar(x, y, '0', color);
		return;
	}
	
	while( temp )
	{// 得到num的长度
		temp /= 10;
		length ++;
	}
	
	while( num )
	{
		/* 从个位开始显示 */
		LCD_DispChar((x+STR_WIDTH*(length--)-STR_WIDTH), y, (num%10)+'0', color);
		num /= 10;
	}	
}
