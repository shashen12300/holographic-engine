#include "RA8835.h"
//320240图形点阵液晶模块参考程序
//控制IC:RA8835
//点阵数:320*240

#define first_home_address	0x0000	//第一显示区首地址
#define second_home_address	0x2580	//第二显示区首地址


unsigned char systemset_tab[]={0x33,0x87,0x07,0x27,0x3a,0xef,0x28,0x00};
unsigned char scroll_tab[]={0x00,0x00,0xf0,0x80,0x25,0xf0,0x00,0x4b,0xb0,0x4f};
char datalcd[150];
static unsigned char Dis_Screen_Flag=1; //现在显示区标志 1 第一显示区 2 第二显示区

/************************************************************************************
基本驱动
************************************************************************************/
//..........延时n毫秒..........
void delay_n_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<123;j++);
}
//..........测忙..........
void chk_lcm_busy(void)
{
	CS_0;
	A0_0;
	WR_1;
	/*input*/
	DATA_PORT_IN;
	RD_0;
	delay_n_ms(1);
	while(READ_BUSY);
	RD_1;
	CS_0;
	/*output*/
	DATA_PORT_OUT;
}
//..........写命令到LCM..........
void send_cmd_to_lcm(unsigned char lcm_cmd)
{
	chk_lcm_busy();
	CS_0;
	A0_1;
	RD_1;
	lcm_WriteByte=lcm_cmd;
	WR_0;
	delay_n_ms(1);
	WR_1;
	delay_n_ms(1);
	CS_1;
}
//..........写数据到LCM..........
void send_data_to_lcm(unsigned char lcm_data)
{
	chk_lcm_busy();
	CS_0;
	A0_0;
	RD_1;
	lcm_WriteByte=lcm_data;
	WR_0;
	delay_n_ms(1);
	WR_1;
	delay_n_ms(1);
	CS_1;
}
//..........写1个命令和1个数据到LCM..........
void send_cmd_and_data_to_lcm(unsigned char lcm_cmd,unsigned char lcm_data)
{
	send_cmd_to_lcm(lcm_cmd);
	send_data_to_lcm(lcm_data);
}
//..........写1个16进制数据到LCM..........
void send_two_data_to_lcm(unsigned short int lcm_data)
{
	send_data_to_lcm(lcm_data);
	send_data_to_lcm(lcm_data>>8);
}
//..........从LCM读数据..........
unsigned char read_data_from_lcm(void)
{
	unsigned char lcm_data;
	chk_lcm_busy();
	CS_0;
	A0_1;
	WR_1;
	/*input*/
	DATA_PORT_IN; 
	RD_0;
	delay_n_ms(1);
	lcm_data=DATA_PORT->IDR;
	RD_1;
	delay_n_ms(1);
	CS_0;
	/*output*/
	DATA_PORT_OUT;
	return lcm_data;
}

//..........初始化..........
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启相应时钟 */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE); 
	
	/*控制信号*/
	GPIO_InitStructure.GPIO_Pin = RD_PIN;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RD_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(RD_PORT,RD_PIN);
	
	GPIO_InitStructure.GPIO_Pin = WR_PIN;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(WR_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(WR_PORT,WR_PIN);
	
	GPIO_InitStructure.GPIO_Pin = CS_PIN;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CS_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(CS_PORT,CS_PIN);
	
	GPIO_InitStructure.GPIO_Pin = A0_PIN;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(A0_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(A0_PORT,A0_PIN);
	
	GPIO_InitStructure.GPIO_Pin = RST_PIN;	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RST_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(RST_PORT,RST_PIN);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DATA_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(DATA_PORT,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}
void lcm_init(void)
{
	unsigned char i;
	LCD_GPIO_Init();
	RST_0;
	delay_n_ms(5);
	RST_1;
	delay_n_ms(50);
	CS_0;
	send_cmd_to_lcm(0x40);				//WRITE SYSTEMSET 指令和参数
	for(i=0;i<8;i++)
		send_data_to_lcm(systemset_tab[i]);
		
	send_cmd_to_lcm(0x40);				//WRITE SYSTEMSET 指令和参数
	for(i=0;i<8;i++)
		datalcd[i]=read_data_from_lcm();
		
	send_cmd_to_lcm(0x44);				//WRITE SCROLL 指令和参数
	for(i=0;i<10;i++)
		send_data_to_lcm(scroll_tab[i]);
	send_cmd_and_data_to_lcm(0x5a,0x00);		//显示画面水平移动量
	send_cmd_and_data_to_lcm(0x5b,0x0c);		//显示属性 //0xc0显示一区三区图像方式//0x00 文本方式
	send_cmd_to_lcm(0x5d);				//光标设置
	send_two_data_to_lcm(0x8f07);
	#ifdef DIR_Horizontal //横屏显示
		send_cmd_to_lcm(0x4c);				//光标自动移动方向--0x4c向右 0x4e向上 0x4f向下
	#endif
	#ifdef DIR_Vertical //竖屏显示
		send_cmd_to_lcm(0x4e);	
	#endif
	send_cmd_and_data_to_lcm(0x59,0x04);		//DISP  只开显示一区
}
/************************************************************************************
中间层封装
************************************************************************************/
void writeData(unsigned char data)
{
	send_cmd_to_lcm(0x42);//显示数据写入
	send_data_to_lcm(data);
}
unsigned char readData(void)
{
	send_cmd_to_lcm(0x43);				//读显示RAM里的数据
	return read_data_from_lcm();
}
void setCursor(unsigned short int address)
{
	//#ifdef DIR_Horizontal //横屏 x(0~319) y(0~239)
		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
		send_two_data_to_lcm(address);
	//#endif
	//#ifdef DIR_Vertical //竖屏 x(0~239) y(0~319)
		
	//#endif
}
void writeDataByAddress(unsigned short int address,unsigned char data)
{
	setCursor(address);
	writeData(data);
}

unsigned char readDataByAddress(unsigned short int address)
{
	setCursor(address);
	return readData();
}
unsigned short int getAddress(unsigned int x,unsigned int y)
{
	#ifdef DIR_Horizontal //横屏 x(0~319) y(0~239)
		return (Dis_Screen_Flag-1)*second_home_address+x/8+y*40;
	#endif
	#ifdef DIR_Vertical //竖屏 x(0~239) y(0~319)
		return (Dis_Screen_Flag-1)*second_home_address+y/8+(239-x)*40;
	#endif
}
unsigned char getLocationAtByte(unsigned int x,unsigned int y)
{
	#ifdef DIR_Horizontal //横屏
		return 0x80>>(x%8);
	#endif
	#ifdef DIR_Vertical //竖屏
		return 0x80>>(y%8);
	#endif
}	
//unsigned char setCursorByAddress(unsigned int x,unsigned int y)
//{
//	unsigned short int address;
//	#ifdef DIR_Horizontal //横屏 x(0~319) y(0~239)
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		//send_two_data_to_lcm(second_home_address+40*(240-1)+i);
//		address=getAddress(x,y);
//		send_two_data_to_lcm(address);
//		return (0x80>>(x%8));
//	#endif
//	#ifdef DIR_Vertical //竖屏 x(0~239) y(0~319)
//		
//	#endif
//}
/************************************************************************************
顶层封装
************************************************************************************/
//..........清显示RAM..........
void clr_ram(void)
{
	unsigned int i,j;
	#ifdef DIR_Horizontal //横屏
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		send_two_data_to_lcm(first_home_address);
		setCursor(first_home_address);
		send_cmd_to_lcm(0x42);
		for(i=0;i<9600*2;i++)
			send_data_to_lcm(0x00);
	#endif
	#ifdef DIR_Vertical //竖屏
		for(i=0;i<40;i++)
		{
//			send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//			send_two_data_to_lcm(first_home_address+40*(240-1)+i);
			setCursor(first_home_address+40*(240-1)+i);
			send_cmd_to_lcm(0x42);
			for(j=0;j<240;j++)
				send_data_to_lcm(0x00);
		}
		for(i=0;i<40;i++)
		{
//			send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//			send_two_data_to_lcm(second_home_address+40*(240-1)+i);
			setCursor(second_home_address+40*(240-1)+i);
			send_cmd_to_lcm(0x42);
			for(j=0;j<240;j++)
				send_data_to_lcm(0x00);
		}
	#endif
//	send_cmd_and_data_to_lcm(0x59,0x04);		//DISP  只开显示一区
//	send_cmd_and_data_to_lcm(0x59,0x10);		//DISP  只开显示二区
}
//画点
void setPoint(unsigned int x,unsigned int y,unsigned char pixel)
{
	unsigned short int address;
	unsigned char location;
	address=getAddress(x,y);
	location=getLocationAtByte(x,y);
	if(pixel==0) //不显示
	{
		writeDataByAddress(
		address,readDataByAddress(address) & ~location
		);
	}else{ //显示
		writeDataByAddress(
		address,readDataByAddress(address) | location
		);
	}
}
//读一个点
unsigned char getPoint(unsigned int x,unsigned int y)
{
	unsigned short int address;
	unsigned char location;
	address=getAddress(x,y);
	location=getLocationAtByte(x,y);
	if(readDataByAddress(address) & location){
		return 0x01;
	}else{
		return 0x00;
	}
}
//画线
void DrawHLine(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int color)
{
	for(;x0<x1;x0++){
		setPoint(x0,y0,color);
	}
}
void DrawVLine(unsigned short int x0,unsigned short int y0,unsigned short int y1,unsigned short int color)
{
	for(;y0<y1;y0++){
		setPoint(x0,y0,color);
	}
}
//填充矩形
void FillRect(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int y1,unsigned short int color)
{
	for(;y0<y1;y0++){
		DrawHLine(x0,y0,x1,color);
	}
}

