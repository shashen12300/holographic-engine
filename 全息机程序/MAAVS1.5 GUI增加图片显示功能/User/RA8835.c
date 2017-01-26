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
unsigned char dataOfScreen[40*240*2]={0}; //为了提升读取屏幕RAM数据速度，定义的屏幕RAM数据存放数组

/************************************************************************************
基本驱动
************************************************************************************/
//..........延时n毫秒..........
void delay_n_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<1;j++);
}
//..........测忙..........
void chk_lcm_busy(void)
{
//	CS_0;
//	A0_0;
//	WR_1;
//	/*input*/
//	DATA_PORT_IN;
//	RD_0;
//	//delay_n_ms(1);
//	while(READ_BUSY);
//	RD_1;
//	CS_0;
//	/*output*/
//	DATA_PORT_OUT;
}
//..........写命令到LCM..........
void send_cmd_to_lcm(unsigned char lcm_cmd)
{
	chk_lcm_busy();
	CS_0;
	A0_1;
	RD_1;
	lcm_WriteByte(lcm_cmd);
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
	lcm_WriteByte(lcm_data);
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
	//delay_n_ms(1);
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
	delay_n_ms(1);
	RST_1;
	//delay_n_ms(1);
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
//	send_cmd_and_data_to_lcm(0x59,0x04);		//DISP  只开显示一区
//	send_cmd_and_data_to_lcm(0x59,0x10);		//DISP  只开显示二区
//	send_cmd_and_data_to_lcm(0x59,0x40);		//DISP  只开显示三区
//	send_cmd_and_data_to_lcm(0x59,0x54);		//DISP  开显示一二三区
	send_cmd_and_data_to_lcm(0x59,0x04);		//DISP  只开显示一区

}
/************************************************************************************
中间层封装
************************************************************************************/
//0 光标移动方向向右
//1 左
//2 上
//3 下
void changeDir(unsigned char dir)
{
	send_cmd_to_lcm(0x4c+dir);
}
void setCursor(unsigned short int address)
{
	send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
	send_two_data_to_lcm(address);
}
void writeData(unsigned char data)
{
	send_cmd_to_lcm(0x42);//显示数据写入
	send_data_to_lcm(data);
}
void writeDataOfSame(unsigned char data,unsigned short int length)
{
	unsigned short int i;
	send_cmd_to_lcm(0x42);//显示数据写入
	for(i=0;i<length;i++)
		send_data_to_lcm(data);
}
unsigned char readData(void)
{
	send_cmd_to_lcm(0x43);				//读显示RAM里的数据
	return read_data_from_lcm();
}
void readDataByAddress(unsigned short int address,unsigned short int length,unsigned char * data)
{
	unsigned short int i;
	setCursor(address);
	send_cmd_to_lcm(0x43);
	for(i=0;i<length;i++)
		*(data+i)=read_data_from_lcm();
}
void prepareWriteData(unsigned short int address)
{
	send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
	send_two_data_to_lcm(address);
	send_cmd_to_lcm(0x42);//显示数据写入
}
void writeDataByAddress(unsigned short int address,unsigned char data)
{
//	setCursor(address);
//	writeData(data);
	send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
	send_two_data_to_lcm(address);
	send_cmd_to_lcm(0x42);//显示数据写入
	send_data_to_lcm(data);
	dataOfScreen[address]=data;
}
void writeDataOfScreen(unsigned short int address,unsigned char data)
{
	dataOfScreen[address]=data;
}
unsigned char readDataOfScreen(unsigned short int address)
{
//	setCursor(address);
//	return readData();
//	send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//	send_two_data_to_lcm(address);
//	send_cmd_to_lcm(0x43);				//读显示RAM里的数据
//	return read_data_from_lcm();
	return dataOfScreen[address];
}
void writeDataOfSameByAddress(unsigned char data,unsigned short int length,unsigned short int startAddress)
{
	unsigned short int i;
	send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
	send_two_data_to_lcm(startAddress);
	send_cmd_to_lcm(0x42);//显示数据写入
	for(i=0;i<length;i++)
		send_data_to_lcm(data);
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

unsigned short int getAreaAddress(unsigned int x,unsigned int y,unsigned int area)
{
	#ifdef DIR_Horizontal //横屏 x(0~319) y(0~239) 
		return (area-1)*second_home_address+x/8+y*40;
	#endif
	#ifdef DIR_Vertical //竖屏 x(0~239) y(0~319)
		return (area-1)*second_home_address+y/8+(239-x)*40;
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
	
	#ifdef DIR_Horizontal //横屏
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		send_two_data_to_lcm(first_home_address);
		unsigned int i;
//		setCursor(first_home_address);
//		send_cmd_to_lcm(0x42);
		prepareWriteData(first_home_address);
		for(i=0;i<9600;i++){
			send_data_to_lcm(0x00);
			dataOfScreen[i]=0;
		}
	#endif
	#ifdef DIR_Vertical //竖屏
		unsigned int i,j;
		for(i=0;i<40;i++)
		{
//			send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//			send_two_data_to_lcm(first_home_address+40*(240-1)+i);
//			setCursor(first_home_address+40*(240-1)+i);
//			send_cmd_to_lcm(0x42);
			prepareWriteData(first_home_address+40*(240-1)+i);
			for(j=0;j<240;j++){
				send_data_to_lcm(0x00);
				dataOfScreen[i*40+j]=0;
			}
		}
		for(i=0;i<40;i++)
		{
//			send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//			send_two_data_to_lcm(second_home_address+40*(240-1)+i);
//			setCursor(second_home_address+40*(240-1)+i);
//			send_cmd_to_lcm(0x42);
			prepareWriteData(second_home_address+40*(240-1)+i);
			for(j=0;j<240;j++){
				send_data_to_lcm(0x00);
				dataOfScreen[second_home_address+i*40+j]=0;
			}
		}
	#endif

}
//画点
void setPoint(unsigned int x,unsigned int y,unsigned short int pixel)
{
	unsigned short int address;
	unsigned char location;
	address=getAddress(x,y);
	location=getLocationAtByte(x,y);
	if(pixel==0) //不显示
	{
		writeDataByAddress(address,readDataOfScreen(address) & ~location);
	}else{ //显示
		writeDataByAddress(address,readDataOfScreen(address) | location);
	}
	
//	unsigned short int address,newAddress;
//		unsigned short int i;
//		unsigned char temp;
//		address=getAddress(x0,y0);
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		send_two_data_to_lcm(address);
//		send_cmd_to_lcm(0x42);//显示数据写入
//		for(i=0;i<x1-x0+1;i++){
//			newAddress=address-40*i;
//			temp=readDataOfScreen(newAddress) | getLocationAtByte(x0+i,y0);
//			send_data_to_lcm(temp);
//			dataOfScreen[newAddress]=temp;
//		}
}
//读一个点
unsigned short int getPoint(unsigned int x,unsigned int y)
{
	unsigned short int address;
	unsigned char location;
	address=getAddress(x,y);
	location=getLocationAtByte(x,y);
	if(readDataOfScreen(address) & location){
		return 0x01;
	}else{
		return 0x00;
	}
}
//画线
//横屏 x(0~319) y(0~239) 竖屏 x(0~239) y(0~319)
void DrawHLine(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int color)
{
	#ifdef DIR_Horizontal //横屏
		unsigned short int address;
		unsigned short int i,temp;
		address=getAddress(x0,y0);
		if(color!=0){
			temp=x1/8-x0/8;
			if(temp>0){
				writeDataByAddress( address,(0xff>>x0%8)|readDataOfScreen(address) );//写开始的1字节RAM
				for(i=0;i<temp-1;i++){
					//writeDataOfSameByAddress(0xff,temp-1,unsigned short int startAddress)
					send_data_to_lcm(0xff);
					dataOfScreen[address+i+1]=0xff;	
				}
				writeDataByAddress( address+temp,(0xff<<(7-x1%8))|readDataOfScreen(address+temp) );//写结束的1字节RAM
			}else{
				writeDataByAddress( address,((0xff>>x0%8)&(0xff<<(7-x1%8)))|readDataOfScreen(address) );
			}
		}else{
			temp=x1/8-x0/8;
			if(temp>0){
				writeDataByAddress( address,~(0xff>>x0%8)&readDataOfScreen(address) );//写开始的1字节RAM
				for(i=0;i<temp-1;i++){
					//writeDataOfSameByAddress(0xff,temp-1,unsigned short int startAddress)
					send_data_to_lcm(0);
					dataOfScreen[address+i+1]=0;	
				}
				writeDataByAddress( address+temp,~(0xff<<(7-x1%8))&readDataOfScreen(address+temp) );//写结束的1字节RAM
			}else{
				writeDataByAddress( address,(~(0xff>>x0%8)|~(0xff<<(7-x1%8)))&readDataOfScreen(address) );
			}
		}
		/*else if(temp==1){
			send_data_to_lcm(0xff<<(7-x1%8));
		}else if(temp==0){
			
		}
		end=x1%8*/
		//writeDataOfSameByAddress(0xff,unsigned short int length,unsigned short int startAddress)
	#endif
	#ifdef DIR_Vertical //竖屏
//		for(;x0<x1;x0++){
//			setPoint(x0,y0,color);
//		}
		unsigned short int address,newAddress;
		unsigned short int i;
		unsigned char temp,temp2;
		address=getAddress(x0,y0);
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		send_two_data_to_lcm(address);
//		send_cmd_to_lcm(0x42);//显示数据写入
		prepareWriteData(address);
		if(color!=0){ //显示
			temp2=getLocationAtByte(x0,y0);//此处竖屏只关心y0的值
			for(i=0;i<x1-x0+1;i++){
				newAddress=address-40*i;
				temp=readDataOfScreen(newAddress) | temp2;
				send_data_to_lcm(temp);
				dataOfScreen[newAddress]=temp;
			}
		}else{ //不显示
			temp2=~getLocationAtByte(x0,y0);//此处竖屏只关心y0的值
			for(i=0;i<x1-x0+1;i++){
				newAddress=address-40*i;
				temp=readDataOfScreen(newAddress) & temp2;
				send_data_to_lcm(temp);
				dataOfScreen[newAddress]=temp;
			}
		}
//		writeDataByAddress(
//		address,readDataOfScreen(address) | getLocationAtByte(x,y)
//		);
	#endif
	
}
void DrawVLine(unsigned short int x0,unsigned short int y0,unsigned short int y1,unsigned short int color)
{
//	for(;y0<y1;y0++){
//		setPoint(x0,y0,color);
//	}
	#ifdef DIR_Horizontal //横屏
		unsigned short int address,newAddress;
		unsigned short int i;
		unsigned char temp,temp2;
		send_cmd_to_lcm(0x4f); //设置光标向下移动
		address=getAddress(x0,y0);
//		send_cmd_to_lcm(0x46);//设置光标在显示RAM区的位置
//		send_two_data_to_lcm(address);
//		send_cmd_to_lcm(0x42);//显示数据写入
		prepareWriteData(address);
		if(color!=0){ //显示
			temp2=getLocationAtByte(x0,y0);//此处竖屏只关心x0的值
			for(i=0;i<y1-y0+1;i++){
				newAddress=address+40*i;
				temp=readDataOfScreen(newAddress) | temp2;
				send_data_to_lcm(temp);
				dataOfScreen[newAddress]=temp;
			}
		}else{ //不显示
			temp2=~getLocationAtByte(x0,y0);//此处竖屏只关心x0的值
			for(i=0;i<y1-y0+1;i++){
				newAddress=address+40*i;
				temp=readDataOfScreen(newAddress) & temp2;
				send_data_to_lcm(temp);
				dataOfScreen[newAddress]=temp;
			}
		}
		send_cmd_to_lcm(0x4c); //恢复光标向右移动
	#endif
	#ifdef DIR_Vertical //竖屏
		unsigned short int address;
		unsigned short int i,temp;
	
		send_cmd_to_lcm(0x4c); //设置光标向右移动
		
		address=getAddress(x0,y0);
		if(color!=0){//显示 	
			temp=y1/8-y0/8;
			if(temp>0){
				writeDataByAddress( address,(0xff>>y0%8)|readDataOfScreen(address) );//写开始的1字节RAM
				for(i=0;i<temp-1;i++){
					//writeDataOfSameByAddress(0xff,temp-1,unsigned short int startAddress)
					send_data_to_lcm(0xff);
					dataOfScreen[address+i+1]=0xff;	
				}
				writeDataByAddress( address+temp,(0xff<<(7-y1%8))|readDataOfScreen(address+temp) );//写结束的1字节RAM
			}else{
				writeDataByAddress( address,((0xff>>y0%8)&(0xff<<(7-y1%8)))|readDataOfScreen(address) );
			}
		}else{//不显示 
			temp=y1/8-y0/8;
			if(temp>0){
				writeDataByAddress( address,~(0xff>>y0%8)&readDataOfScreen(address) );//写开始的1字节RAM
				for(i=0;i<temp-1;i++){
					//writeDataOfSameByAddress(0xff,temp-1,unsigned short int startAddress)
					send_data_to_lcm(0x00);
					dataOfScreen[address+i+1]=0x00;	
				}
				writeDataByAddress( address+temp,~(0xff<<(7-y1%8))&readDataOfScreen(address+temp) );//写结束的1字节RAM
			}else{
				writeDataByAddress( address,(~(0xff>>y0%8)|~(0xff<<(7-y1%8)))&readDataOfScreen(address) );
			}
		}			
		send_cmd_to_lcm(0x4e);	//恢复光标向上移动
	#endif
}
//填充矩形
void FillRect(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int y1,unsigned short int color)
{
	#ifdef DIR_Horizontal //横屏
		if(x0==0 && y0==0 && x1==319 && y1==239 && color==0){
			clr_ram();
		}	
	#endif
	#ifdef DIR_Vertical //竖屏
		if(x0==0 && y0==0 && x1==239 && y1==319 && color==0){
			clr_ram();
		}
	#endif
	else{
		for(;y0<=y1;y0++){
			DrawHLine(x0,y0,x1,color);
		}
	}
}
/*
x0,y0起始坐标
xsize,ysize横坐标和纵坐标像素点个数
pData图像数组(1字节8个像素，数据排列方向：横坐标方向)
*/
void DrawBitmap(unsigned short int x0,unsigned short int y0,
							  unsigned short int xsize,unsigned short int ysize,
								const	unsigned char *pData)
{
	#ifdef DIR_Horizontal //横屏
		unsigned short int address;
		unsigned short int i,j;
		unsigned char data,flag,temp;
		address=getAddress(x0,y0);
		flag=x0%8;
		if(flag==0){
			for(i=0;i<ysize;i++){
				prepareWriteData(address+i*40);
				for(j=0;j<xsize/8;j++){
					data=*(pData+i*((xsize-1)/8+1)+j);
					writeDataOfScreen(address+i*40+j,data);
					send_data_to_lcm(data);
				}
				if(xsize%8!=0){
					data=readDataOfScreen(address+i*40+(xsize-1)/8);//写最后不是8像素的一个字节
					data=data&(0xff>>(xsize%8)); //取屏幕最后几个像素的值
					data=data| ( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8))&(0xff<<(8-xsize%8)) );//将要显示的图片最后几个像素的值与屏幕的几个像素值融合
					writeDataOfScreen(address+i*40+(xsize-1)/8,data);
					send_data_to_lcm(data);
				}
			}
		}else{
			for(i=0;i<ysize;i++){
				prepareWriteData(address+i*40);
				
				data=readDataOfScreen(address+i*40);
				data=data & (0xff<<(8-(x0%8)));//清零屏幕第一个字节图像显示的像素点值
				data=data | ( *(pData+i*((xsize-1)/8+1))>>(x0%8) );//将要显示的图片最后几个像素的值与屏幕的几个像素值融合
				writeDataOfScreen(address+i*40,data);
				send_data_to_lcm(data);
				
				for(j=1;j<(x0%8+xsize)/8;j++){
					data= (*(pData+i*((xsize-1)/8+1)+j-1) << (8-flag));
					data=data | (*(pData+i*((xsize-1)/8+1)+j)>>flag);
					writeDataOfScreen(address+i*40+j,data);
					send_data_to_lcm(data);
				}
				if((x0+xsize)%8!=0){
					data=readDataOfScreen(address+i*40+( x0+xsize-1)/8-x0/8 );//写最后不是8像素的一个字节
					data=data&(0xff>>((x0+xsize)%8)); //取屏幕最后几个像素的值
					if((xsize/8+1)*8-(j*8-flag)>8){
						temp=(*(pData+i*((xsize-1)/8+1)+j-1)<<(8-flag)) | 
							( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8)>>flag) & (0xff<<(8-flag-xsize%8)) ) ;
					}else{
						temp=(*(pData+i*((xsize-1)/8+1)+j-1)&(0xff<<j*8-xsize)) << (8-(x0+xsize+1)%8);
					}
					data=data | temp;
//					( 
//						(
//							(*(pData+i*((xsize-1)/8+1)+j-1)<<(8-flag)) | 
//							( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8)>>flag) & (0xff<<(8-flag-xsize%8)) ) 
//						)
//						<< (8-(x0+xsize)%8) 
//					);//将要显示的图片最后几个像素的值与屏幕的几个像素值融合

					writeDataOfScreen(address+i*40+(xsize-1)/8,data);
					send_data_to_lcm(data);
				}
			}
		}
	#endif
	#ifdef DIR_Vertical //竖屏
		
	#endif
}

/*
x0,y0起始坐标 
xsize,ysize横坐标和纵坐标像素点个数
pData图像数组(1字节8个像素，数据排列方向：横坐标方向)
area设置显示区
*/
void DrawAreaBitmap(unsigned short int x0,unsigned short int y0,
							  unsigned short int xsize,unsigned short int ysize,
								const	unsigned char *pData,unsigned short int area)
{
	#ifdef DIR_Horizontal //横屏
		unsigned short int address;
		unsigned short int i,j;
		unsigned char data,flag,temp;
	address=getAreaAddress(x0,y0,area);
		flag=x0%8;
		if(flag==0){
			for(i=0;i<ysize;i++){
				prepareWriteData(address+i*40);
				for(j=0;j<xsize/8;j++){
					data=*(pData+i*((xsize-1)/8+1)+j);
					writeDataOfScreen(address+i*40+j,data);
					send_data_to_lcm(data);
				}
				if(xsize%8!=0){
					data=readDataOfScreen(address+i*40+(xsize-1)/8);//写最后不是8像素的一个字节
					data=data&(0xff>>(xsize%8)); //取屏幕最后几个像素的值
					data=data| ( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8))&(0xff<<(8-xsize%8)) );//将要显示的图片最后几个像素的值与屏幕的几个像素值融合
					writeDataOfScreen(address+i*40+(xsize-1)/8,data);
					send_data_to_lcm(data);
				}
			}
		}else{
			for(i=0;i<ysize;i++){
				prepareWriteData(address+i*40);
				
				data=readDataOfScreen(address+i*40);
				data=data & (0xff<<(8-(x0%8)));//清零屏幕第一个字节图像显示的像素点值
				data=data | ( *(pData+i*((xsize-1)/8+1))>>(x0%8) );//将要显示的图片最后几个像素的值与屏幕的几个像素值融合
				writeDataOfScreen(address+i*40,data);
				send_data_to_lcm(data);
				
				for(j=1;j<(x0%8+xsize)/8;j++){
					data= (*(pData+i*((xsize-1)/8+1)+j-1) << (8-flag));
					data=data | (*(pData+i*((xsize-1)/8+1)+j)>>flag);
					writeDataOfScreen(address+i*40+j,data);
					send_data_to_lcm(data);
				}
				if((x0+xsize)%8!=0){
					data=readDataOfScreen(address+i*40+( x0+xsize-1)/8-x0/8 );//写最后不是8像素的一个字节
					data=data&(0xff>>((x0+xsize)%8)); //取屏幕最后几个像素的值
					if((xsize/8+1)*8-(j*8-flag)>8){
						temp=(*(pData+i*((xsize-1)/8+1)+j-1)<<(8-flag)) | 
							( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8)>>flag) & (0xff<<(8-flag-xsize%8)) ) ;
					}else{
						temp=(*(pData+i*((xsize-1)/8+1)+j-1)&(0xff<<j*8-xsize)) << (8-(x0+xsize+1)%8);
					}
					data=data | temp;
//					( 
//						(
//							(*(pData+i*((xsize-1)/8+1)+j-1)<<(8-flag)) | 
//							( (*(pData+i*((xsize-1)/8+1)+(xsize-1)/8)>>flag) & (0xff<<(8-flag-xsize%8)) ) 
//						)
//						<< (8-(x0+xsize)%8) 
//					);//将要显示的图片最后几个像素的值与屏幕的几个像素值融合

					writeDataOfScreen(address+i*40+(xsize-1)/8,data);
					send_data_to_lcm(data);
				}
			}
		}
	#endif
	#ifdef DIR_Vertical //竖屏
		
	#endif
}
