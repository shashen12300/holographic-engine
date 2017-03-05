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
	
	/*上下涂黑*/
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
	/*左右涂黑*/
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
	
	OS_CRITICAL_ENTER();	//进入临界区	
  LCD_SetRamAddr(x,y);
  for(i=0;i<len;i++)
	{
		/*换行*/
		if(i%xl==0 && i>0)
		{
			y++;
			LCD_SetRamAddr(x,y);
		}
		
		/*写数据*/
		LCD_WriteData(tmp[i]);
	}
	
	OS_CRITICAL_EXIT();	//退出临界区	
}

void LCD_clear_range(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl)
{
	CPU_SR_ALLOC();
  int i,i2;
	int len=xl*yl;
	
	OS_CRITICAL_ENTER();	//进入临界区	
  LCD_SetRamAddr(x,y);
  for(i=0;i<len;i++)
	{
		/*换行*/
		if(i%xl==0 && i>0)
		{
			y++;
			LCD_SetRamAddr(x,y);
		}
		
		/*写数据*/
		LCD_WriteData(0x00);
	}
	
	OS_CRITICAL_EXIT();	//退出临界区	
}
void LCD_PutGB2312_12x12(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();
	
	int i,iS,l,ch_count=0;
	
	
	OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[ch_count]!='\0')
	{
		/*获取汉字字库长度*/
		l=sizeof(GB2312_12x12_Sraech)/26;
		
		/*从字符数据库中搜索汉字*/
		for(i=0;i<l;i++)
		{
			/*如果找到对应的汉字*/
			if(ch[ch_count]==GB2312_12x12_Sraech[i*26] && ch[ch_count+1]==GB2312_12x12_Sraech[i*26+1])
			{
				/*指向数组的开头*/
				iS=i*26+2;
				break;
			}
		}
		
		/*显示坐标移动到汉字的上半部分*/
		LCD_SetRamAddr(x,y);
		/*打印一个汉字*/
		for(i=0;i<24;i++)
		{
			if(i%24==12)
			{
				/*y坐标向下移动，打印汉字的下半部分*/
				LCD_SetRamAddr(x,y+1);
			}
			LCD_WriteData(GB2312_12x12_Sraech[i+iS]);
			
		}

		/*数组指针+2*/
		ch_count=ch_count+2;
		/*显示位置右移12格*/
		x=x+12;
	}
	OS_CRITICAL_EXIT();	//退出临界区	
}

void LCD_PutNUMBER_16x24(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();

	/*设置字符大小*/
	int xl=16;
	int yl=3;
	int len=xl*yl;
	
	int ch_count=0;
	
	static unsigned int i,iS;
	
	OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[ch_count]!='\0')
	{
		
		/*如果小于范围，修改为0*/
		if(ch[ch_count]<46)ch[ch_count]=46+2;
			
		/*如果大于范围，修改为9*/
		if(ch[ch_count]>46+11)ch[ch_count]=46+11;
		
		/*指向内容的开头*/
		iS=(ch[ch_count]-46)*len;
		
	
		/*显示坐标移动到显示区域的开头*/
		LCD_SetRamAddr(x,y);
		
			
		/*打印一个数字*/
		for(i=0;i<len;i++)
		{
			if(i%xl==0 && i>0)
			{
				/*y坐标向下移动*/
				y++;
				LCD_SetRamAddr(x,y);
			}
			/*发送数据*/
			LCD_WriteData(NUMBER_15x24[i+iS]);
		}
		/*Y轴回归*/
		y=y-yl+1;
		
		/*数组指针+2*/
		ch_count++;
		/*显示位置右移16格*/
		x=x+xl+1;
		
		/*小数点特殊处理*/
		if(iS==0)x=x-13;
	}
	OS_CRITICAL_EXIT();	//退出临界区	
}

void LCD_Printf(unsigned char x, unsigned char y,char* ch)
{
	CPU_SR_ALLOC();
	u32 i=0;
	
	OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{
		//ASCII
		if(ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
		
		/*插入空白*/
		LCD_WriteData(0x00);
		
		x=x+6;
		i++;//数组指针自加
	}
	OS_CRITICAL_EXIT();	//退出临界区	
}

void LCD_Printf_invert(unsigned char x, unsigned char y,char* ch,char p)
{
	CPU_SR_ALLOC();
	u32 i=0;
	
	OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{
		
		/*清空附近区域*/
		LCD_clear_range(x-1,y-1,7,3);

		//发送字符
		if(ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
//		/*插入空白*/
//		LCD_WriteData(0x00);
		
		/*找到反色位*/
		if((i+1)==p)
		{
			LCD_PutAscii_5x8_invert(x,y,ch[i]);
		}
		
		
		
		x=x+7;
		i++;//数组指针自加
	}
	OS_CRITICAL_EXIT();	//退出临界区	
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
	OS_CRITICAL_ENTER();	//进入临界�
	
	LCD_SetRamAddr(0,0);
	
	for(x=0;x<(8*102);x++)LCD_WriteData(0);
	OS_CRITICAL_EXIT();	//退出临界区	
}


void LCD_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	RCC_APB2PeriphClockCmd(LCD_RS_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_RS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure);		
	
	RCC_APB2PeriphClockCmd(LCD_REST_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_REST_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_REST_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_CLK_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_CLK_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CLK_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_DI_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_DI_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_DI_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_CS_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_BL_GPIO_CLK, ENABLE);	 //使能端口时钟
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

	/*注意，此处是为了匹配液晶屏的显示方向*/
	LCD_WriteCommand(0x38);

	LCD_clear();
		
	LCD_write_dot(0,0,0x01);

	
	
}
