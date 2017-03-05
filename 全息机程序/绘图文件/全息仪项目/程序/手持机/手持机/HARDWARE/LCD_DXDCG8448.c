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
/*дһ���ַ� */
void LCD_PutAscii_5x8(unsigned char x, unsigned char y, char ch)
{
	unsigned char Ysize=8,Xsize=5;
  unsigned char j,i;
	unsigned char tmp_char=0,tmp_num;
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=ASCII_5x8[(ch-0x20)*5+i];
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>j;
			
			/*�ж������1������ʾ���������*/
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
	
	/*Ϳ������*/
	for(i=x-1;i<x+6;i++)
	{
		for(i2=y-1;i2<y+8;i2++)
		{
			LCD_Set_ram_addr(i,i2,1);
		}
	}
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=ASCII_5x8[(ch-0x20)*5+i];
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>j;
			
			/*�ж������1������ʾ���������*/
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
	

	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	/*��ȡ�����ֿⳤ��*/
	l=sizeof(GB2312_12x12_Sraech)/26;
	
	/*���ַ����ݿ�����������*/
	for(i=0;i<l;i++)
	{
		/*����ҵ���Ӧ�ĺ���*/
		if(ch[0]==GB2312_12x12_Sraech[i*26] && ch[1]==GB2312_12x12_Sraech[i*26+1])
		{
			/*ָ������Ŀ�ͷ*/
			iS=i*26+2;
			break;
		}
	}
	/*���ַ�������������*/
	for(i=0;i<26;i++)
	{
		tmp[i]=GB2312_12x12_Sraech[i+iS];
	}
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	/*��ȡ�����ֿⳤ��*/
	l=sizeof(GB2312_10x10_Sraech)/StrLen;
	
	/*���ַ����ݿ�����������*/
	for(i=0;i<l;i++)
	{
		/*����ҵ���Ӧ�ĺ���*/
		if(ch[0]==GB2312_10x10_Sraech[i*StrLen] && ch[1]==GB2312_10x10_Sraech[i*StrLen+1])
		{
			/*ָ������Ŀ�ͷ*/
			iS=i*StrLen+2;
			break;
		}
	}
	/*���ַ�������������*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=GB2312_10x10_Sraech[i+iS];
	}
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	
	//OS_CRITICAL_ENTER();	//�����ٽ���	
	
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
		i++;//����ָ���Լ�
	}
	//OS_CRITICAL_EXIT();	//�˳��ٽ���	
}
void LCD_Printf_12x12(unsigned char x, unsigned char y,char* ch)
{
//	CPU_SR_ALLOC();
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//�����ٽ���	
	
	while(ch[i]!='\0')
	{
		//���
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutASCII_7x11(x,y+1,ch[i]);
			//LCD_PutASCII_6x12(x,y,ch[i]);
			LCD_clear_range(x+6,y,1,12);
			x=x+7;
			i++;//����ָ���Լ�
		}
		//ȫ��
		else
		{
			LCD_PutGB2312_12x12(x,y,&ch[i]);
			LCD_clear_range(x+12,y,1,12);
			x=x+12;
			i=i+2;//����ָ���Լ�
		}
	}
	//OS_CRITICAL_EXIT();	//�˳��ٽ���	
}
void LCD_Printf_10x10(unsigned char x, unsigned char y,char* ch)
{
	//CPU_SR_ALLOC();
	u32 i=0;
	while(ch[i]!='\0')
	{
		//���
		if((unsigned char)ch[i]<0xA1)
		{
			LCD_PutAscii_5x8(x,y+2,ch[i]);
			//LCD_clear_range(x+6,y,1,12);
			x=x+5;
			i++;//����ָ���Լ�
		}
		//ȫ��
		else
		{
			LCD_PutGB2312_10x10(x,y,&ch[i]);
			LCD_clear_range(x+12,y,1,12);
			x=x+10;
			i=i+2;//����ָ���Լ�
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
		
		/*�ҵ���ɫλ*/
		if((i+1)==p)
		{
			LCD_PutAscii_5x8_invert(x,y,ch[i]);
		}
		
		x=x+7;
		i++;//����ָ���Լ�
	}
//	CPU_SR_ALLOC();
//	u32 i=0;
//	
//	//OS_CRITICAL_ENTER();	//�����ٽ���	
//	
//	while(ch[i]!='\0')
//	{
//		
//		/*��ո�������*/
//		LCD_clear_range(x-1,y-1,7,3);

//		//�����ַ�
//		if(ch[i]<0xA1)
//		{
//			LCD_PutAscii_5x8(x,y,ch[i]);
//		}
////		/*����հ�*/
////		LCD_WriteData(0x00);
//		
//		/*�ҵ���ɫλ*/
//		if((i+1)==p)
//		{
//			LCD_PutAscii_5x8_invert(x,y,ch[i]);
//		}
//		
//		
//		
//		x=x+7;
//		i++;//����ָ���Լ�
//	}
//	//OS_CRITICAL_EXIT();	//�˳��ٽ���	
}
void LCD_Printf_GB2312_12x12(unsigned char x, unsigned char y,char* ch)
{
//	CPU_SR_ALLOC();
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//�����ٽ���	
	
	while(ch[i]!='\0')
	{

		LCD_PutGB2312_12x12(x,y,&ch[i]);
			
		LCD_clear_range(x+12,y,1,12);
		x=x+13;
		i=i+2;//����ָ���Լ�
	}
	//OS_CRITICAL_EXIT();	//�˳��ٽ���	
}

void LCD_Printf_NUMBER_16x24(unsigned char x, unsigned char y,char* ch)
{
	int Xsize=16;
	int Ysize=24;
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//�����ٽ���	
	
	while(ch[i]!='\0')
	{

		LCD_PutNUMBER_16x24(x,y,ch[i]);
			
		LCD_clear_range(x+Xsize,y,1,Ysize);
		
		x=x+Xsize+1;
		
		/*С�������⴦��*/
		if(ch[i]==46)x=x-11;
		
		i++;//����ָ���Լ�

	}
}
void LCD_Printf_NUMBER_10x15(unsigned char x, unsigned char y,char* ch)
{
	int Xsize=10;
	int Ysize=15;
	u32 i=0;
	
	//OS_CRITICAL_ENTER();	//�����ٽ���	
	
	while(ch[i]!='\0')
	{

		LCD_PutNUMBER_10x15(x,y,ch[i]);
			
		LCD_clear_range(x+Xsize,y,1,Ysize);
		
		x=x+Xsize+1;
		
		/*С�������⴦��*/
		if(ch[i]==46)x=x-6;
		
		i++;//����ָ���Լ�

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
	
	/*���С�����ݿ�����ķ�Χ���޸�Ϊ0*/
	if(ch<46)ch=46+2;
		
	/*����������ݿ�����ķ�Χ���޸�Ϊ9*/
	if(ch>46+11)ch=46+11;
	
	/*ָ�����ݵĿ�ͷ*/
	iS=(ch-46)*StrLen;
	
	/*���ַ�������������*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=NUMBER_10x15[i+iS];
	}
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	
	/*���С�����ݿ�����ķ�Χ���޸�Ϊ0*/
	if(ch<a_star)ch=a_star;
		
	/*����������ݿ�����ķ�Χ���޸�Ϊ9*/
	if(ch>a_end)ch=a_star;
	
	/*ָ�����ݵĿ�ͷ*/
	iS=(ch-a_star)*Xsize*(Ysize/8+1);
	
	/*���ַ�������������*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=ASCII_6x12[i+iS];
	}
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	
	/*���С�����ݿ�����ķ�Χ���޸�Ϊ0*/
	if(ch<a_star)ch=a_star;
		
	/*����������ݿ�����ķ�Χ���޸�Ϊ9*/
	if(ch>a_end)ch=a_star;
	
	/*ָ�����ݵĿ�ͷ*/
	iS=(ch-a_star)*StrLen;
	
	/*���ַ�������������*/
	for(i=0;i<StrLen;i++)
	{
		tmp[i]=ASCII_7x11[i+iS]; /*��Ҫ�޸�*/
	}
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	
	/*���С�����ݿ�����ķ�Χ���޸�Ϊ0*/
	if(ch<a_star)ch=a_star+11;
		
	/*����������ݿ�����ķ�Χ���޸�Ϊ9*/
	if(ch>a_end)ch=a_end;
	
	/*ָ�����ݵĿ�ͷ*/
	iS=(ch-a_star)*Xsize*(Ysize/8);
	
	/*���ַ�������������*/
	for(i=0;i<Xsize*(Ysize/8);i++)
	{
		tmp[i]=NUMBER_16x24[i+iS];
	}
	
	/*Xѭ��*/
	for (i=0;i<Xsize;i++)
  {
		/*�����е�������ȡ����*/
		tmp_char=tmp[p];
		p++;
		
		/*Yѭ��*/
    for (j=0;j<Ysize;j++)
    {
			
			/*�����Ƿ���Ҫ�л���һ��*/
			tmp_char=tmp[i+(Xsize*(j/8))];
			
			/*����ʾ����������Ӧ��λ��*/
			tmp_num=tmp_char>>(j%8);
			
			/*�ж������1������ʾ���������*/
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
	
	//������Ļ�ϵ���
	LCD_H=(y/8);
	
	//������Ļ�ϵ���
	LCD_V=x;
	
	//������Ļ���ֽ��е�λ
	LCD_B=(y%8);
	
	*(LCD_buffp+(LCD_H*(102*8)+LCD_V*8+LCD_B)*4)=tmp;
}

void LCD_BL_Init(int BLLum)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	
	RCC_APB2PeriphClockCmd(LCD_BL_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LCD_BL_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_BL_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* Time base configuration */
	 TIM_TimeBaseStructure.TIM_Period = 10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 
	 TIM_TimeBaseStructure.TIM_Prescaler = 719; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	 TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	 
	 /* Output Compare Active Mode configuration: Channel1 */
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM�����ȵ���ģʽ
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	 TIM_OCInitStructure.TIM_Pulse = BLLum;                   //���ô�װ�벶��ȽϼĴ���������ֵ����ʼ��ռ�ձ�
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	 TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	 TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);  //ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	 
	 TIM_ARRPreloadConfig(TIM3,ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ��� 	 	
	 TIM_Cmd(TIM3,ENABLE);  //ʹ��TIMx����
	 
}

void LCD_Init(void)
{
//	u16 i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	

	
	
	
	/*�ض���SPI1*/
	GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
	
	SPIx_ReadWriteByte(0xff);//��������		 
	
	RCC_APB2PeriphClockCmd(LCD_CLK_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LCD_CLK_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_CLK_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_DI_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LCD_DI_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_DI_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_RS_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LCD_RS_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure);		
	
	RCC_APB2PeriphClockCmd(LCD_REST_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = LCD_REST_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(LCD_REST_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(LCD_CS_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��
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

	/*ע�⣬�˴���Ϊ��ƥ��Һ��������ʾ����*/
	LCD_WriteCommand(0x38);

	LCD_clear();
		
	
	//LCD_write_dot(0,0,0x01);
	
	/*������ʼ�����=0*/
	/*set x*/
	LCD_WriteCommand(0x80+0);
	/*set y*/
	LCD_WriteCommand(0x40+0);
	
	/*��SPI��CS����*/
	LCD_CS_OUT=0;
	LCD_RS_OUT=1;
	
	//while(1)SPIx_ReadWriteByte(1);
	
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel3);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI1_DR;	 			//ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&LCD_buff;					//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;							//������ΪĿ�Ĵ����ַ
	DMA_InitStructure.DMA_BufferSize = LCD_BUFF_LEN;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						//�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  										//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;			//byte
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;															//ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel3, ENABLE);
	
	LCD_buffp=(char*)((u32)(LCD_buffp-0x20000000)<<5)+0x22000000;
}

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}

