#include "LCD_DXDCG8448.h"
#include "includes.h"
#include "ASCII.h"
#include "GB2312_12x12_Sraech.h"
#include "GB2312_Sraech.h"
#include "KD_CH4.h"
 //sfr   P1=0x90;
// sbit  RS=   0x92;      //6
// sbit  REST= 0x90;    //5
// sbit  CLK = 0x94;
// sbit  DI  = 0x93;
// sbit  CS_S =0x91;   //4

// sbit         pp=         0xb2;
// unsigned char data dis=0x3f;

char LCD_buff[LCD_BUFF_LEN];

char *LCD_buffp=LCD_buff;



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
/*写一个字符 */
void LCD_PutAscii_5x8(unsigned char x, unsigned char y, char ch)
{
	unsigned char Ysize=8,Xsize=5;
  unsigned char j,i;
	unsigned char tmp_char=0,tmp_num;
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=ASCII_5x8[(ch-0x20)*5+i];
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>j;
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
//  LCD_WriteData(ASCII_5x8[(ch-0x20)*5+i]);
}
void LCD_PutAscii_5x8_invert(unsigned char x, unsigned char y, char ch)
{
//	char tmp;
  unsigned char j,i,i2;
	unsigned char Ysize=8,Xsize=5;
	unsigned char tmp_char=0,tmp_num;
	
	/*涂黑四周*/
	for(i=x-1;i<x+6;i++)
	{
		for(i2=y-1;i2<y+8;i2++)
		{
			LCD_Set_ram_addr(i,i2,1);
		}
	}
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=ASCII_5x8[(ch-0x20)*5+i];
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>j;
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
    }
		x++;
	}
}

void LCD_PutImage(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl,char* tmp)
{
	unsigned char Ysize=yl,Xsize=xl;
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	

	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
}


void LCD_clear(void)
{
	u32 i=0;
	for(i=0;i<LCD_BUFF_LEN;i++)LCD_buff[i]=0;
	//LCD_clear_range(20,20,10,10);
}
void LCD_clear_range(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl)
{
  u16 i,i2;
	
  for(i=x;i<(x+xl);i++)
	{
			for(i2=y;i2<(y+yl);i2++)
			{
				LCD_Set_ram_addr(i,i2,0);
			}
	}
	
}
void LCD_PutGB2312_12x12(unsigned char x, unsigned char y,char* ch)
{
	unsigned char Ysize=12,Xsize=12;
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	int iS,l;
	char tmp[26];
	/*获取汉字字库长度*/
	l=sizeof(GB2312_12x12_Sraech)/26;
	
	/*从字符数据库中搜索汉字*/
	for(i=0;i<l;i++)
	{
		/*如果找到对应的汉字*/
		if(ch[0]==GB2312_12x12_Sraech[i*26] && ch[1]==GB2312_12x12_Sraech[i*26+1])
		{
			/*指向数组的开头*/
			iS=i*26+2;
			break;
		}
	}
	/*将字符串拷贝到缓存*/
	for(i=0;i<26;i++)
	{
		tmp[i]=GB2312_12x12_Sraech[i+iS];
	}
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}

}

void LCD_PutGB2312_10x10(unsigned char x, unsigned char y,char* ch)
{
	unsigned char Ysize=10,Xsize=10;
	unsigned char StrLen=22;
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	int iS,l;
	char tmp[26];
	/*获取汉字字库长度*/
	l=sizeof(GB2312_10x10_Sraech)/StrLen;
	
	/*从字符数据库中搜索汉字*/
	for(i=0;i<l;i++)
	{
		/*如果找到对应的汉字*/
		if(ch[0]==GB2312_10x10_Sraech[i*StrLen] && ch[1]==GB2312_10x10_Sraech[i*StrLen+1])
		{
			/*指向数组的开头*/
			iS=i*StrLen+2;
			break;
		}
	}
	/*将字符串拷贝到缓存*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=GB2312_10x10_Sraech[i+iS];
	}
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}

}


void LCD_Printf(unsigned char x, unsigned char y,char* ch)
{
//	CPU_SR_ALLOC();
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{
		//ASCII
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
		LCD_clear_range(x+5,y,1,8);
		x=x+6;
//		if(ch[i]=='-')
//		{
//			x=x-3;
//		}
		i++;//数组指针自加
	}
	//OS_CRITICAL_EXIT();	//退出临界区	
}
void LCD_Printf_12x12(unsigned char x, unsigned char y,char* ch)
{
//	CPU_SR_ALLOC();
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{
		//半角
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutASCII_7x11(x,y+1,ch[i]);
			//LCD_PutASCII_6x12(x,y,ch[i]);
			LCD_clear_range(x+6,y,1,12);
			x=x+7;
			i++;//数组指针自加
		}
		//全角
		else
		{
			LCD_PutGB2312_12x12(x,y,&ch[i]);
			LCD_clear_range(x+12,y,1,12);
			x=x+12;
			i=i+2;//数组指针自加
		}
	}
	//OS_CRITICAL_EXIT();	//退出临界区	
}
void LCD_Printf_10x10(unsigned char x, unsigned char y,char* ch)
{
	//CPU_SR_ALLOC();
	u32 i=0;
	while(ch[i]!='\0')
	{
		//半角
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y+2,ch[i]);
			//LCD_clear_range(x+6,y,1,12);
			x=x+5;
			i++;//数组指针自加
		}
		//全角
		else
		{
			LCD_PutGB2312_10x10(x,y,&ch[i]);
			LCD_clear_range(x+12,y,1,12);
			x=x+10;
			i=i+2;//数组指针自加
		}
	}
}
void LCD_Printf_invert(unsigned char x, unsigned char y,char* ch,char p)
{
	u32 i=0;
	
	while(ch[i]!='\0')
	{
		//ASCII
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y,ch[i]);
		}
		LCD_clear_range(x+5,y,1,8);
		
		/*找到反色位*/
		if((i+1)==p)
		{
			LCD_PutAscii_5x8_invert(x,y,ch[i]);
		}
		
		x=x+7;
		i++;//数组指针自加
	}
//	CPU_SR_ALLOC();
//	u32 i=0;
//	
//	//OS_CRITICAL_ENTER();	//进入临界区	
//	
//	while(ch[i]!='\0')
//	{
//		
//		/*清空附近区域*/
//		LCD_clear_range(x-1,y-1,7,3);

//		//发送字符
//		if(ch[i]<0xA1)
//		{
//			LCD_PutAscii_5x8(x,y,ch[i]);
//		}
////		/*插入空白*/
////		LCD_WriteData(0x00);
//		
//		/*找到反色位*/
//		if((i+1)==p)
//		{
//			LCD_PutAscii_5x8_invert(x,y,ch[i]);
//		}
//		
//		
//		
//		x=x+7;
//		i++;//数组指针自加
//	}
//	//OS_CRITICAL_EXIT();	//退出临界区	
}
void LCD_Printf_GB2312_12x12(unsigned char x, unsigned char y,char* ch)
{
//	CPU_SR_ALLOC();
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{

		LCD_PutGB2312_12x12(x,y,&ch[i]);
			
		LCD_clear_range(x+12,y,1,12);
		x=x+13;
		i=i+2;//数组指针自加
	}
	//OS_CRITICAL_EXIT();	//退出临界区	
}

void LCD_Printf_NUMBER_16x24(unsigned char x, unsigned char y,char* ch)
{
	int Xsize=16;
	int Ysize=24;
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{

		LCD_PutNUMBER_16x24(x,y,ch[i]);
			
		LCD_clear_range(x+Xsize,y,1,Ysize);
		
		x=x+Xsize+1;
		
		/*小数点特殊处理*/
		if(ch[i]==46)x=x-11;
		
		i++;//数组指针自加

	}
}
void LCD_Printf_NUMBER_10x15(unsigned char x, unsigned char y,char* ch)
{
	int Xsize=10;
	int Ysize=15;
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	while(ch[i]!='\0')
	{

		LCD_PutNUMBER_10x15(x,y,ch[i]);
			
		LCD_clear_range(x+Xsize,y,1,Ysize);
		
		x=x+Xsize+1;
		
		/*小数点特殊处理*/
		if(ch[i]==46)x=x-6;
		
		i++;//数组指针自加

	}
}
void LCD_PutNUMBER_10x15(unsigned char x, unsigned char y,char ch)
{
	unsigned char Xsize=10,Ysize=15;
	unsigned char StrLen=20;
		
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	static unsigned int iS;
	char tmp[48];
	
	/*如果小于数据库包含的范围，修改为0*/
	if(ch<46)ch=46+2;
		
	/*如果大于数据库包含的范围，修改为9*/
	if(ch>46+11)ch=46+11;
	
	/*指向内容的开头*/
	iS=(ch-46)*StrLen;
	
	/*将字符串拷贝到缓存*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=NUMBER_10x15[i+iS];
	}
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
}

void LCD_PutASCII_6x12(unsigned char x, unsigned char y,char ch)
{
	unsigned char Xsize=6,Ysize=12;
	unsigned char StrLen=12;
	unsigned char a_star=32,a_end=126;
	
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	static unsigned int iS;
	char tmp[48];
	
	/*如果小于数据库包含的范围，修改为0*/
	if(ch<a_star)ch=a_star;
		
	/*如果大于数据库包含的范围，修改为9*/
	if(ch>a_end)ch=a_star;
	
	/*指向内容的开头*/
	iS=(ch-a_star)*Xsize*(Ysize/8+1);
	
	/*将字符串拷贝到缓存*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=ASCII_6x12[i+iS];
	}
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
}

void LCD_PutASCII_7x11(unsigned char x, unsigned char y,char ch)
{
	unsigned char Xsize=7,Ysize=11;
	unsigned char StrLen=14;
	unsigned char a_star=47,a_end=57;
	
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	static unsigned int iS;
	char tmp[48];
	
	/*如果小于数据库包含的范围，修改为0*/
	if(ch<a_star)ch=a_star;
		
	/*如果大于数据库包含的范围，修改为9*/
	if(ch>a_end)ch=a_star;
	
	/*指向内容的开头*/
	iS=(ch-a_star)*StrLen;
	
	/*将字符串拷贝到缓存*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=ASCII_7x11[i+iS]; /*需要修改*/
	}
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
}
void LCD_PutNUMBER_16x24(unsigned char x, unsigned char y,char ch)
{
	unsigned char Xsize=16,Ysize=24;
	unsigned char a_star=37,a_end=57;
  unsigned char j,i,p=0;
	unsigned char tmp_char=0,tmp_num;
	static unsigned int iS;
	char tmp[48];
	
	/*如果小于数据库包含的范围，修改为0*/
	if(ch<a_star)ch=a_star+11;
		
	/*如果大于数据库包含的范围，修改为9*/
	if(ch>a_end)ch=a_end;
	
	/*指向内容的开头*/
	iS=(ch-a_star)*Xsize*(Ysize/8);
	
	/*将字符串拷贝到缓存*/
	for(i=0;i<Xsize*(Ysize/8);i++)
	{
		tmp[i]=NUMBER_16x24[i+iS];
	}
	
	/*X循环*/
	for (i=0;i<Xsize;i++)
  {
		/*将库中的数据提取出来*/
		tmp_char=tmp[p];
		p++;
		
		/*Y循环*/
    for (j=0;j<Ysize;j++)
    {
			
			/*计算是否需要切换下一行*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*将显示数据右移相应的位数*/
			tmp_num=tmp_char>>(j%8);
			
			/*判断如果是1，则显示，否则清空*/
      if ((tmp_num&0x01) == 0x01)
			{
				LCD_Set_ram_addr(x,y+j,1);
			}
			else
			{
				LCD_Set_ram_addr(x,y+j,0);
			}
    }
		x++;
	}
}


void LCD_WriteData(unsigned char dat)
 {
	LCD_RS_OUT=1;
	LCD_CS_OUT=0;
	//LCD_Delay_us(1);
	SPIx_ReadWriteByte(dat);
	//LCD_Delay_us(1);
	LCD_CS_OUT=1;
	//LCD_Delay_us(1);
 }
 void LCD_WriteCommand(unsigned char dat)
{
//	unsigned char i,j;
	
	LCD_RS_OUT=0;
	LCD_CS_OUT=0;
	//LCD_Delay_us(1);
	SPIx_ReadWriteByte(dat);
	//LCD_Delay_us(1);
	LCD_CS_OUT=1;
	//LCD_Delay_us(1);
}
void LCD_write_dot(unsigned char x,unsigned char y,char data)
{ 
	
	LCD_Set_disp_Addr(x,y);
	
	LCD_WriteData(data);
	
}
void LCD_Set_disp_Addr(unsigned char x,unsigned char y)
{
	/*set x*/
	LCD_WriteCommand(0x80+18+x);
	/*set y*/
	LCD_WriteCommand(0x40+2+y);
}
void LCD_Set_ram_addr(unsigned char x,unsigned char y,unsigned char tmp)
{
	u32 LCD_H,LCD_V,LCD_B;
	
	x=x+18;
	y=y+16;
	
	//计算屏幕上的行
	LCD_H=(y/8);
	
	//计算屏幕上的列
	LCD_V=x;
	
	//计算屏幕上字节中的位
	LCD_B=(y%8);
	
	*(LCD_buffp+(LCD_H*(102*8)+LCD_V*8+LCD_B)*4)=tmp;
}

void LCD_BL_Init(int BLLum)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	
	RCC_APB2PeriphClockCmd(LCD_BL_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_BL_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_BL_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* Time base configuration */
	 TIM_TimeBaseStructure.TIM_Period = 10; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值 
	 TIM_TimeBaseStructure.TIM_Prescaler = 719; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	 TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	 
	 /* Output Compare Active Mode configuration: Channel1 */
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM脉冲宽度调制模式
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	 TIM_OCInitStructure.TIM_Pulse = BLLum;                   //设置待装入捕获比较寄存器的脉冲值，初始的占空比
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	 TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	 TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);  //使能TIMx在CCR1上的预装载寄存器
	 
	 TIM_ARRPreloadConfig(TIM3,ENABLE); //使能TIMx在ARR上的预装载寄存器 	 	
	 TIM_Cmd(TIM3,ENABLE);  //使能TIMx外设
	 
}

void LCD_Init(void)
{
//	u16 i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	

	
	
	
	/*重定义SPI1*/
	GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPIx_ReadWriteByte(0xff);//启动传输		 
	
	RCC_APB2PeriphClockCmd(LCD_CLK_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_CLK_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CLK_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_DI_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_DI_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_DI_GPIO_PORT, &GPIO_InitStructure);	
	
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
	
	RCC_APB2PeriphClockCmd(LCD_CS_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);	
	

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
		
	
	//LCD_write_dot(0,0,0x01);
	
	/*设置起始坐标点=0*/
	/*set x*/
	LCD_WriteCommand(0x80+0);
	/*set y*/
	LCD_WriteCommand(0x40+0);
	
	/*将SPI的CS拉低*/
	LCD_CS_OUT=0;
	LCD_RS_OUT=1;
	
	//while(1)SPIx_ReadWriteByte(1);
	
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel3);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI1_DR;	 			//ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&LCD_buff;					//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;							//外设作为目的传输地址
	DMA_InitStructure.DMA_BufferSize = LCD_BUFF_LEN;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  										//内存地址增量
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;			//byte
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;															//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel3, ENABLE);
	
	LCD_buffp=(char*)((u32)(LCD_buffp-0x20000000)<<5)+0x22000000;
}

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}

