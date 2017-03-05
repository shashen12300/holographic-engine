#include "LCD_DXDCG8448.h"
#include "includes.h"
#include "ASCII.h"
#include "GB2312_12x12_Sraech.h"
 //sfr   P1=0x90;
// sbit  RS=   0x92;      //6
// sbit  REST= 0x90;    //5
// sbit  CLK = 0x94;
// sbit  DI  = 0x93;
// sbit  CS_S =0x91;   //4

// sbit         pp=         0xb2;
// unsigned char data dis=0x3f;
void LCD_Delay_ns(u16 ns)
{
	while(--ns);
}
void LCD_Delay_us(u32 us)
{
	us=us*50;
	while(--us);
}
void LCD_Delay_ms(u16 us)
{
	int i;
	for(i=0;i<us;i++)
	LCD_Delay_us(800);
}

void LCD_PutAscii_5x8(unsigned char x, unsigned char y, char ch)
{
  unsigned char i;
  LCD_SetRamAddr(x,y);
  for(i=0;i<5;i++)
  LCD_WriteData(ASCII_5x8[(ch-0x20)*5+i]);
}
void LCD_PutAscii_5x8_invert(unsigned char x, unsigned char y, char ch)
{
	char tmp;
  unsigned char i;
	
	/*ÉÏÏÂÍ¿ºÚ*/
	LCD_SetRamAddr(x-1,y-1);
	for(i=0;i<7;i++)
	{
		LCD_WriteData(0x80);
	}
	
//	LCD_SetRamAddr(x-1,y+1);
//	for(i=0;i<7;i++)
//	{
//		LCD_WriteData(0x01);
//	}
//	
	/*×óÓÒÍ¿ºÚ*/
	LCD_SetRamAddr(x-1,y);
	LCD_WriteData(0xFF);
	
	LCD_SetRamAddr(x+5,y);
	LCD_WriteData(0xFF);

	
  LCD_SetRamAddr(x,y);
  for(i=0;i<5;i++)
	{
		tmp=~ASCII_5x8[(ch-0x20)*5+i];
		LCD_WriteData(tmp);
	}
 
}

void LCD_PutImage(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl,int len,char* tmp)
{
	CPU_SR_ALLOC();
  int i,i2;
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
  LCD_SetRamAddr(x,y);
  for(i=0;i<len;i++)
	{
		/*»»ĞĞ*/
		if(i%xl==0 && i>0)
		{
			y++;
			LCD_SetRamAddr(x,y);
		}
		
		/*Ğ´Êı¾İ*/
		LCD_WriteData(tmp[i]);
	}
	
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}

void LCD_clear_range(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl)
{
	CPU_SR_ALLOC();
  int i,i2;
	int len=xl*yl;
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
  LCD_SetRamAddr(x,y);
  for(i=0;i<len;i++)
	{
		/*»»ĞĞ*/
		if(i%xl==0 && i>0)
		{
			y++;
			LCD_SetRamAddr(x,y);
		}
		
		/*Ğ´Êı¾İ*/
		LCD_WriteData(0x00);
	}
	
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}
void LCD_PutGB2312_12x12(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();
	
	int i,iS,l,ch_count=0;
	
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
	
	while(ch[ch_count]!='\0')
	{
		/*»ñÈ¡ºº×Ö×Ö¿â³¤¶È*/
		l=sizeof(GB2312_12x12_Sraech)/26;
		
		/*´Ó×Ö·ûÊı¾İ¿âÖĞËÑË÷ºº×Ö*/
		for(i=0;i<l;i++)
		{
			/*Èç¹ûÕÒµ½¶ÔÓ¦µÄºº×Ö*/
			if(ch[ch_count]==GB2312_12x12_Sraech[i*26] && ch[ch_count+1]==GB2312_12x12_Sraech[i*26+1])
			{
				/*Ö¸ÏòÊı×éµÄ¿ªÍ·*/
				iS=i*26+2;
				break;
			}
		}
		
		/*ÏÔÊ¾×ø±êÒÆ¶¯µ½ºº×ÖµÄÉÏ°ë²¿·Ö*/
		LCD_SetRamAddr(x,y);
		/*´òÓ¡Ò»¸öºº×Ö*/
		for(i=0;i<24;i++)
		{
			if(i%24==12)
			{
				/*y×ø±êÏòÏÂÒÆ¶¯£¬´òÓ¡ºº×ÖµÄÏÂ°ë²¿·Ö*/
				LCD_SetRamAddr(x,y+1);
			}
			LCD_WriteData(GB2312_12x12_Sraech[i+iS]);
			
		}

		/*Êı×éÖ¸Õë+2*/
		ch_count=ch_count+2;
		/*ÏÔÊ¾Î»ÖÃÓÒÒÆ12¸ñ*/
		x=x+12;
	}
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}

void LCD_PutNUMBER_16x24(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();

	/*ÉèÖÃ×Ö·û´óĞ¡*/
	int xl=16;
	int yl=3;
	int len=xl*yl;
	
	int ch_count=0;
	
	static unsigned int i,iS;
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
	
	while(ch[ch_count]!='\0')
	{
		
		/*Èç¹ûĞ¡ÓÚ·¶Î§£¬ĞŞ¸ÄÎª0*/
		if(ch[ch_count]<46)ch[ch_count]=46+2;
			
		/*Èç¹û´óÓÚ·¶Î§£¬ĞŞ¸ÄÎª9*/
		if(ch[ch_count]>46+11)ch[ch_count]=46+11;
		
		/*Ö¸ÏòÄÚÈİµÄ¿ªÍ·*/
		iS=(ch[ch_count]-46)*len;
		
	
		/*ÏÔÊ¾×ø±êÒÆ¶¯µ½ÏÔÊ¾ÇøÓòµÄ¿ªÍ·*/
		LCD_SetRamAddr(x,y);
		
			
		/*´òÓ¡Ò»¸öÊı×Ö*/
		for(i=0;i<len;i++)
		{
			if(i%xl==0 && i>0)
			{
				/*y×ø±êÏòÏÂÒÆ¶¯*/
				y++;
				LCD_SetRamAddr(x,y);
			}
			/*·¢ËÍÊı¾İ*/
			LCD_WriteData(NUMBER_15x24[i+iS]);
		}
		/*YÖá»Ø¹é*/
		y=y-yl+1;
		
		/*Êı×éÖ¸Õë+2*/
		ch_count++;
		/*ÏÔÊ¾Î»ÖÃÓÒÒÆ16¸ñ*/
		x=x+xl+1;
		
		/*Ğ¡ÊıµãÌØÊâ´¦Àí*/
		if(iS==0)x=x-13;
	}
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}

void LCD_Printf(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();
	u32 i=0;
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
	
	while(ch[i]!='\0')
	{
		//ASCII
		if(ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
		
		/*²åÈë¿Õ°×*/
		LCD_WriteData(0x00);
		
		x=x+6;
		i++;//Êı×éÖ¸Õë×Ô¼Ó
	}
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}

void LCD_Printf_invert(unsigned char x, unsigned char y,char* ch,char p)
{
	CPU_SR_ALLOC();
	u32 i=0;
	
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇø	
	
	while(ch[i]!='\0')
	{
		
		/*Çå¿Õ¸½½üÇøÓò*/
		LCD_clear_range(x-1,y-1,7,3);

		//·¢ËÍ×Ö·û
		if(ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
//		/*²åÈë¿Õ°×*/
//		LCD_WriteData(0x00);
		
		/*ÕÒµ½·´É«Î»*/
		if((i+1)==p)
		{
			LCD_PutAscii_5x8_invert(x,y,ch[i]);
		}
		
		
		
		x=x+7;
		i++;//Êı×éÖ¸Õë×Ô¼Ó
	}
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}

void LCD_WriteData(unsigned char u)
 {
 	unsigned char i,j;
	j=u;
	
	LCD_RS_OUT=1;
	LCD_CS_OUT=0;
	
	LCD_Delay_us(1);
	
	LCD_CLK_OUT=1;
	
	LCD_Delay_us(1);
	
	for(i=0;i<8;i++)
	{
		LCD_CLK_OUT=0;
		
		LCD_Delay_us(1);
		
		if((j&0x80)==0x80)
			LCD_DI_OUT=1;
		else
			LCD_DI_OUT=0;
		
		LCD_Delay_us(1);
		LCD_CLK_OUT=1;
		LCD_Delay_us(1);
		
		j<<=1;
	}
	
	LCD_Delay_us(1);
	LCD_CS_OUT=1;
	LCD_Delay_us(1);
 }
 void LCD_WriteCommand(unsigned char u)
{
	unsigned char i,j;
	j=u;
	
	LCD_RS_OUT=0;
	LCD_CS_OUT=0;
	
	LCD_Delay_us(1);
	
	LCD_CLK_OUT=1;
	
	LCD_Delay_us(1);
	
	for(i=0;i<8;i++)
	{
		LCD_CLK_OUT=0;
		
		LCD_Delay_us(1);
		
		if((j&0x80)==0x80)
			LCD_DI_OUT=1;
		else
			LCD_DI_OUT=0;
		
		LCD_Delay_us(1);
		LCD_CLK_OUT=1;
		LCD_Delay_us(1);
		
		j<<=1;
	}
	
	LCD_Delay_us(1);
	LCD_CS_OUT=1;
	LCD_Delay_us(1);
}
void LCD_write_dot(unsigned char x,unsigned char y,char data)
{ 
	
	LCD_SetRamAddr(x,y);
	
	LCD_WriteData(data);
	
}
void LCD_SetRamAddr(unsigned char x,unsigned char y)
{
	/*set x*/
	LCD_WriteCommand(0x80+18+x);
	/*set y*/
	LCD_WriteCommand(0x40+2+y);
}
void LCD_clear(void)
{
	CPU_SR_ALLOC();
	int x;
	OS_CRITICAL_ENTER();	//½øÈëÁÙ½çÇ
	
	LCD_SetRamAddr(0,0);
	
	for(x=0;x<(8*102);x++)LCD_WriteData(0);
	OS_CRITICAL_EXIT();	//ÍË³öÁÙ½çÇø	
}


void LCD_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	RCC_APB2PeriphClockCmd(LCD_RS_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_RS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure);		
	
	RCC_APB2PeriphClockCmd(LCD_REST_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_REST_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_REST_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_CLK_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_CLK_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CLK_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_DI_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_DI_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_DI_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_CS_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_BL_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = LCD_BL_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_BL_GPIO_PORT, &GPIO_InitStructure);	
	
	LCD_BL_OUT=1;
	LCD_REST_OUT=1;
	LCD_CS_OUT=1;

	LCD_Delay_ms(100);
	LCD_REST_OUT=0;

	LCD_Delay_ms(100);
	LCD_REST_OUT=1;

	LCD_Delay_ms(100);

	LCD_WriteCommand(0x21);
	LCD_WriteCommand(0x12);  //System bias set
	LCD_WriteCommand(0xd5);	//Set EVR

	LCD_Delay_ms(100);
	LCD_WriteCommand(0x20);
	LCD_WriteCommand(0x0c);	//Display Control
	LCD_WriteCommand(0x40);	//Set Y addr of RAM
	LCD_WriteCommand(0x80);	//Set X addr of RAM

	LCD_Delay_ms(10);

	LCD_WriteCommand(0x21);
	LCD_WriteCommand(0x12);  //System bias set
	LCD_WriteCommand(0x80+0x75);	//Set EVR

	LCD_Delay_ms(100);
	LCD_WriteCommand(0x20);
	LCD_WriteCommand(0x0C);	//Display Control
	LCD_WriteCommand(0x40);	//Set Y addr of RAM
	LCD_WriteCommand(0x80);	//Set X addr of RAM



	LCD_Delay_ms(10);

	/*×¢Òâ£¬´Ë´¦ÊÇÎªÁËÆ¥ÅäÒº¾§ÆÁµÄÏÔÊ¾·½Ïò*/
	LCD_WriteCommand(0x38);

	LCD_clear();
		
	LCD_write_dot(0,0,0x01);

	
	
}
