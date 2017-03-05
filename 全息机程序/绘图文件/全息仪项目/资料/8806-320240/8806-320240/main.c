#include <reg52.h>
#include "ra8806reg.h"

sbit rs = P2^0;
sbit wr = P2^1;
sbit rd = P2^2;
sbit cs1 = P2^3;
sbit rst = P2^5;   
sbit busy = P2^4;

#define BUS P0

unsigned char code tab1[]={"深圳市川航电子科技有限公司专业生产液晶屏"};

unsigned char code pic1[]={
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XF3,0XCF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X93,0XC9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X93,0XC9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF3,
0XCF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X12,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X12,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X09,0X80,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XF9,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X0F,0XBF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X1F,0XFF,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X5F,
0XFF,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XF0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XF0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X07,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF3,0XC0,0X00,
0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X93,0XC0,0X00,0X00,0X00,
0X00,0X00,0X0F,0XFF,0XFF,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X93,0XC0,0X00,0X78,0X00,0X00,0X00,
0X7F,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF3,0XC0,0X07,0XFF,0XC1,0XFF,0XE0,0XFF,0XFF,
0XF8,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X0F,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XF8,0X1F,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X7F,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X0F,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC1,0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X7F,0X80,0X0F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X3F,
0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0X80,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X01,0XFF,
0XFC,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X0F,0XFF,0XFC,0X3F,
0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X1F,0XFF,0XF8,0X07,0XFF,0XFF,
0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X1F,0X8F,0XF8,0X00,0XFF,0XFF,0XFC,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X0E,0X01,0XF0,0X00,0X00,0XFE,0XFC,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X0E,0X01,0XF0,0X00,0X00,0X7C,0X3C,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X0E,0X01,0XF0,0X00,0X00,0X7C,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X0E,0X01,0XE0,0X00,0X00,0X79,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X0C,0X01,
0XE0,0X00,0X00,0X7F,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X0C,0X03,0XE0,0X00,
0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X1C,0X03,0XC0,0X00,0X00,0X78,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X1C,0X01,0XC0,0X00,0X00,0X70,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X1C,0X01,0XC0,0X00,0X00,0X70,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X78,0X00,0XC0,0X00,0X00,0X70,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X70,0X00,0XE0,0X00,0X00,0X70,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,
0X70,0X00,0X70,0X00,0X00,0X70,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X60,0X00,
0X70,0X00,0X00,0X78,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X38,0X00,
0X00,0X78,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X3C,0X00,0X00,0X38,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XCF,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF3,0XC9,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X12,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X24,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X93,0XC9,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X12,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X24,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X93,0XCF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XF3,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};


unsigned char d,h,m,s;

////////////////////////////////
void delay_nms(unsigned int n)
{
        unsigned int i,j;
		for(i=n;i>0;i--)
		{
		        for(j=125;j>0;j--)
				{
				}
		}
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void softrst()
{
     delay_nms(2);
	 rst=0;
	 delay_nms(5);
	 rst=1;
	 delay_nms(5);
  
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 
unsigned char LCD_CmdRead(unsigned char Addr)
{  
unsigned char Data;  

cs1=0;
rs=1;
rd=1;
BUS=Addr;
wr=0;
wr=1;

BUS=0XFF;
rs=0;
wr=1;
rd=1;
rd=0;
Data=BUS;

return Data;
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void LCD_CmdWrite(unsigned char cmdaddr)//8080
{		cs1=0;
		rd=1;
		rs=1;
		BUS=cmdaddr;
		wr=0;
        wr=1;
		cs1=1;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void LCD_DataWrite(unsigned char wrdata)
{       while(busy==0);
		cs1=0;
 		rd=1;
		rs=0;
		BUS=wrdata;
		wr=0;
		wr=1;
		cs1=1;
}
//******************消除雪花模式******************
void clearsnow(void)       //在文本方式下，无法使用消除雪花模式，在图形模式下可以用
 {  unsigned char temp;
    temp=LCD_CmdRead(0x01);
	temp |=0x80;
    LCD_CmdWrite(0x01);
    LCD_DataWrite(temp); 
	}
//******************不消除雪花模式--正常模式******************
void noclearsnow(void)
 {  unsigned char temp;     //在文本方式下，无法使用消除雪花模式
    temp=LCD_CmdRead(0x01);
	temp &=0x7f;
    LCD_CmdWrite(0x01);
    LCD_DataWrite(temp); 
	}
//******************X,Y坐标定位******************
void LCD_GotoXY(unsigned char xx,unsigned char yy)
{   LCD_CmdWrite(0x60); 
	LCD_DataWrite(xx);
    LCD_CmdWrite(0x70);  
	LCD_DataWrite(yy);
}
//*************绘图模式**************************
void LCD_Graphic(void)
{   unsigned char temp;
    temp=LCD_CmdRead(0x00);
	temp &=0xf7;
    LCD_CmdWrite(0x00);
    LCD_DataWrite(temp); 
	clearsnow();      //开启消除雪花功能
 }
//*************文字模式**************************
void LCD_Text(void)
{   unsigned char temp;
    temp=LCD_CmdRead(0x00);
	temp |=0x08;
    LCD_CmdWrite(0x00);
    LCD_DataWrite(temp); 
	noclearsnow();      //关闭消除雪花功能
 }

//***********DDRAM1 显示**************************
void Only_Show_Page1(void)
{
	unsigned char temp;
    temp=LCD_CmdRead(0x12);
    temp &=0x9f;
	temp |=0x10;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}

//***********DDRAM2 显示**************************
void Only_Show_Page2(void)
{
	unsigned char temp;
    temp=LCD_CmdRead(0x12);
    temp &=0xaf;
	temp |=0x20;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}
//***********DDRAM1和DDRAM2 双图层显示***************
void Show_Two_Layer(void)
{
	unsigned char temp;	
	temp=LCD_CmdRead(0x12);
    temp &=0xbf;
	temp |=0x30;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}
//***********DDRAM1和DDRAM2 OR方式显示***************
void OR_Two_Layer(void)
{
	unsigned char temp;	
	temp=LCD_CmdRead(0x12);
    temp &=0xf3;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}
//***********存取DDRAM1*******************************
void Access_Page1(void)
{
	unsigned char temp;	
	temp=LCD_CmdRead(0x12);
    temp &=0xfd;
	temp |=0x01;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}
//***********存取DDRAM2*******************************
void Access_Page2(void)
{
	unsigned char temp;	
	temp=LCD_CmdRead(0x12);
    temp &=0xfe;
	temp |=0x02;
    LCD_CmdWrite(0x12);
    LCD_DataWrite(temp); 
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void displays(unsigned char x,unsigned char y,unsigned char *m)
{
    unsigned int iiii=0,pppp=0,c=0;
    LCD_Graphic();    //选择绘图模式
    LCD_GotoXY(x,y);   //指定坐标为00，00
    LCD_CmdWrite(0xb0); 
	   for(iiii=0;iiii<80;iiii++)
	   {
	        for(pppp=0;pppp<40;pppp++)
            {
                  LCD_DataWrite(m[c++]); 
            }   
	    } 

} 
///////////////////////////////////////////
void lcd_inital()
{ 
	LCD_CmdWrite(WLCR);		//[00H] , Default --> 0x00
	LCD_DataWrite(0x04);    //屏幕显示开启  disp_off输出high	

	LCD_CmdWrite(MISC);		//[01H] , Default --> 0x00
	LCD_DataWrite(0x04);

	LCD_CmdWrite(ADSR);		//[03H] , Default --> 0x00 
	LCD_DataWrite(0x00);

	LCD_CmdWrite(INTR);		//[0FH] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CHWI);		//[11H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(MAMR);		//[12H] , Default --> 0x11 
	LCD_DataWrite(0x11);

	LCD_CmdWrite(AWRR);		//[20H] , Default --> 0x27
	LCD_DataWrite(39);

	LCD_CmdWrite(DWWR);		//[21H] , Default --> 0x27
	LCD_DataWrite(39);

	LCD_CmdWrite(AWBR);		//[30H] , Default --> 0xEF	
	LCD_DataWrite(239);

	LCD_CmdWrite(DWHR);		//[31H] , Default --> 0xEF
	LCD_DataWrite(239);

	LCD_CmdWrite(AWLR);		//[40H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(AWTR);		//[50H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CURX);		//[60H] , Default --> 0x00 
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BGSG);		//[61H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(EDSG);		//[62H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CURY);		//[70H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BGCM);		//[71H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(EDCM);		//[72H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BTMR);		//[80H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(ITCR);		//[90H] , Default --> 0x00    对比度不好可以改此参数
	LCD_DataWrite(0x00);

	LCD_CmdWrite(PNTR);		//[E0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FNCR);		//[F0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FVHT);		//[F1H] , Default --> 0x00
	LCD_DataWrite(0x00);
}
    

/////////////////清屏子程序//////////////////////////
void clear(void)
{ 
  LCD_Graphic();     //选择绘图模式     
  noclearsnow();      //关闭消除雪花功能
  LCD_CmdWrite(0xe0);
  LCD_DataWrite(0x00);
  LCD_CmdWrite(0xf0);
  LCD_DataWrite(0xa8);
  delay_nms(3);
}
//////////////全部显示子程序///////////////////////
void display_all()
{
    LCD_Graphic();    //选择绘图模式
    noclearsnow();      //关闭消除雪花功能
    LCD_CmdWrite(0xe0);
    LCD_DataWrite(0xff);     //全部填0xff
    LCD_CmdWrite(0xf0);
    LCD_DataWrite(0xa8);
    delay_nms(3);
}
//////////////装配测试用///////////////////////////
void display_snows(unsigned char dat1,unsigned char dat2)
{

    unsigned int iiii=0,pppp=0;
    LCD_Graphic();   //选择绘图模式
    LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置
	LCD_CmdWrite(0xb0); 
	   for(iiii=0;iiii<120;iiii++)
	   {
	        for(pppp=0;pppp<40;pppp++)
            {
                  LCD_DataWrite(dat1);  
            }   
			for(pppp=0;pppp<40;pppp++)
            {
                  LCD_DataWrite(dat2);  
            }  
	   } 
}
/////////////显示一行边框//////////////////////////////////

void display_kuang(void)
{

	unsigned int n0,n1;
	Only_Show_Page1(); //只显示DDRAM1
    Access_Page1();   //只存取DDRAM1
    LCD_Graphic();   //选择绘图模式
    LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置
	LCD_CmdWrite(0xb0);
	for(n0=0;n0<40;n0++)
			LCD_DataWrite(0xff);

	for(n0=0;n0<238;n0++)		
    {
		for(n1=0;n1<40;n1++)
		{
		    if (n1==0)          LCD_DataWrite(0x80);
		 	else if (n1==39) LCD_DataWrite(0x01);
		   	else                LCD_DataWrite(0x00);
        }
	}

	for(n0=0;n0<40;n0++)
	LCD_DataWrite(0xff);
}
/////////////画一个表格//////////////////////////////////

void display_biao(void)
{

	unsigned int n0,n1;
    LCD_Graphic();   //选择绘图模式
    LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置
	LCD_CmdWrite(0xb0);
	for(n0=0;n0<40;n0++)
			LCD_DataWrite(0xff);

	for(n0=0;n0<31;n0++)		
    {
		for(n1=0;n1<40;n1++)
		{
		    if (n1==0)          LCD_DataWrite(0x80);
		 	else if (n1==39) LCD_DataWrite(0x01);
		   	else                LCD_DataWrite(0x00);
        }
	}

	for(n0=0;n0<40;n0++)
	LCD_DataWrite(0xff);
	for(n0=0;n0<(125);n0++)		
    {
		for(n1=0;n1<40;n1++)
		{
		    if (n1==0)          LCD_DataWrite(0x80);
		 	else if (n1==39) LCD_DataWrite(0x01);
		   	else                LCD_DataWrite(0x00);
        }
	}
	for(n0=0;n0<40;n0++)
	LCD_DataWrite(0xff);
}
//--------------调出ASCII表1----------------------
void display_ziku()
{
	unsigned int i=0;
    Access_Page2() ; //存取DDRAM2
    clear();       //清DDRAM2
    LCD_Text();   //选择文本模式
	LCD_CmdWrite(0xb0); 
	   for(i=0;i<140;i++)
	   {
	       LCD_DataWrite(0x00+i);  
				delay_nms(1);
            }   
}

/////////////显示中文字库和字符////////////////////
void display_word(unsigned char code *cha, int count )
{
	unsigned int iiii=0;
    LCD_Text();   //选择文本模式
	//LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置  放在外面了
	LCD_CmdWrite(0xb0); 
	   for(iiii=0;iiii<count;iiii++)
	   {
	       LCD_DataWrite(*cha++);  
               //++cha;
				delay_nms(1);
            }   
}

/////////////在指定的坐标处显示字符串////////////////////
void LCD_ShowStr(unsigned char *text)
{ 
    LCD_Text();   //选择文本模式
	//LCD_GotoXY(xxx,yyy);   //设定X,Y坐标位置 
    LCD_CmdWrite(0xB0);
    while(*text != '\0')          
	{
    	LCD_DataWrite(*text++);
	    delay_nms(1);
    }
}
/////////////////////全屏反白显示///////////////////////////////////
void reverse_data(void)
{  unsigned char temp;
   temp=LCD_CmdRead(0x00);  //读WLCR寄存器数据
   temp |=0x01;
   LCD_CmdWrite(0x00);
   LCD_DataWrite(temp);     
 }
/////////////////////全屏正常显示///////////////////////////////////
void normal_data(void)
{  unsigned char temp;
   temp=LCD_CmdRead(0x00);  //读WLCR寄存器数据
   temp &=0xfe;
   LCD_CmdWrite(0x00);
   LCD_DataWrite(temp);     
 }
///***************数据反白输入*****************************
void LCD_Inv(void)
{
	unsigned char temp;	
    temp=LCD_CmdRead(0x10);
    temp |=0x20;
    LCD_CmdWrite(0x10);
    LCD_DataWrite(temp); 
}
///***************数据正常输入*****************************
void LCD_NoInv(void)
{
	unsigned char temp;	
    temp=LCD_CmdRead(0x10);
    temp &=0xdf;
    LCD_CmdWrite(0x10);
    LCD_DataWrite(temp); 
}

 /////////////////////汉字粗体显示///////////////////////////////////
void bold_word(void)
{  unsigned char temp;
   temp=LCD_CmdRead(0x10);  //读wccr寄存器数据
   temp |=0x10;
   LCD_CmdWrite(0x10);
   LCD_DataWrite(temp);     
 }
  /////////////////////汉字非粗体显示///////////////////////////////////
void no_bold_word(void)
{  unsigned char temp;
   temp=LCD_CmdRead(0x10);  //读wccr寄存器数据
   temp &=0xef;
   LCD_CmdWrite(0x10);
   LCD_DataWrite(temp);     
 }
/////////////////////字符放大i倍///////////////////////////////////
void enlarge(unsigned char i)
{  
   switch(i)
  { case 0x01:
   LCD_CmdWrite(0xf1);
   LCD_DataWrite(0x00);  
   break;
    case 0x02:
   LCD_CmdWrite(0xf1);
   LCD_DataWrite(0x50);  
   break;
   case 0x03:
   LCD_CmdWrite(0xf1);
   LCD_DataWrite(0xa0); 
   break;
   case 0x04:
   LCD_CmdWrite(0xf1);
   LCD_DataWrite(0xf0); 
   break;
    }
 }
 //-----------------------------组装测试------------------------------------------------
void display_test(unsigned char com1,unsigned char com2)
{
  unsigned char i,j,k;
  LCD_Graphic();   //选择绘图模式
  LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置
  LCD_CmdWrite(0xb0);
  for(i=0;i<240;i++)
  {
     if(i%2==1)
      k=com1;
	else  k=com2;
    for(j=0;j<40;j++)
     {LCD_DataWrite(k);
	 }
  }
}

void lcd_test()
{
  unsigned char i;
  unsigned char code tdata[][2]=
  {
  	{0xff,0xff},	// All
	{0x00,0x00},	// None	
	{0x00,0xFF},	// Virtical 
//	{0xff,0x00},	// Virtical
	{0xAA,0xAA},	// Horizontal 
//	{0x55,0x55},	// Horizontal 
	{0xAA,0x55},	// Stars 
	{0x55,0xaa},	// Stars 
  };
  for(i=0;i<6;i++)
  {
   display_test(tdata[i][0],tdata[i][1]); 
   delay_nms(800);
   clear();
  }
}

//------------------以240128图片显示-----------
void disp_Graphic2()    //boxing
{
    unsigned char i, j;
    LCD_Graphic();    //绘图模式打开
 	Only_Show_Page2();
	Access_Page2() ; //存取DDRAM2
    //clear();       //清DDRAM2
	LCD_GotoXY(0,0);
    LCD_CmdWrite(0Xb0);   
   for(i=0;i<128;i++)
    {
      for(j=0;j<30;j++)
     {
      LCD_DataWrite(pic1[i*30+j]);
     }
   }
}

//*************转HEX***********************
void Print_Hex(unsigned char buf)
{
	unsigned char temp;
	temp=buf;
	temp = (temp >>4) & 0x0F;
	if(temp < 0x0A)
	{
		temp |= 0x30;
	}
	else temp = temp + 0x37;
	LCD_DataWrite(temp);
	delay_nms(1);

	temp=buf;
	temp = temp & 0x0F;
	if(temp < 0x0A)
	{
		temp |= 0x30;
	}
	else temp = temp + 0x37;
	LCD_DataWrite(temp);
	delay_nms(1);
 }
 //**************测试触摸屏*********************
 void tp_test_auto()
{
 unsigned char k,temp,X1[3],X2[3],Y1[3],Y2[3];
 unsigned int X,Y;
	delay_nms(10);
	temp=LCD_CmdRead(0x0f);
	LCD_CmdWrite(0xff);
	while((temp&0x01)==0x01)
	{
		for(k=0;k<3;k++)
		{
		temp=LCD_CmdRead(0x0f);
		LCD_CmdWrite(0xff);
		if((temp&0x01)==0x01)
		{
 			LCD_CmdWrite(0x0f);
			LCD_DataWrite(0x00);
			X1[k]=LCD_CmdRead(0xc1);
			X2[k]=LCD_CmdRead(0xc3)&0x03;							
	    	LCD_CmdWrite(0x0f);
			LCD_DataWrite(0x10);
			delay_nms(5);
	 	}
	    temp=LCD_CmdRead(0x0f);
		LCD_CmdWrite(0xff);
		if((temp&0x01)==0x01)
		{
 			LCD_CmdWrite(0x0f);
			LCD_DataWrite(0x00);
			Y1[k]=LCD_CmdRead(0xc2);
			Y2[k]=LCD_CmdRead(0xc3)&0x0c;			
	    	LCD_CmdWrite(0x0f);
			LCD_DataWrite(0x10);
			delay_nms(5);
	 	}

	}
if((X1[0]==X1[1])&&(X1[0]==X1[2]))
{
X = (((unsigned int)X1[0]&0x00ff)<<2) | ((unsigned int)X2[0]&0x0003);
Y = (((unsigned int)Y1[0]&0x00ff)<<2) | (((unsigned int)Y2[0]&0x000C) >> 2);
    LCD_Text();   //选择文本模式
    LCD_GotoXY(0x17,0x47);   //设定X,Y坐标位置 
	LCD_CmdWrite(0xb0);
Print_Hex(X>>8);
Print_Hex(X);
LCD_GotoXY(0x17,0x64);   //设定X,Y坐标位置 
LCD_CmdWrite(0xb0);
Print_Hex(Y>>8);
Print_Hex(Y);
}
	}
}
//===========================================//
 void rut(void) interrupt 0 //using 1
{
delay_nms(20);   
tp_test_auto();
}
//===========================================//
void main (void)  
{ 
  delay_nms(10);   
  softrst();
  lcd_inital();  
  clear();
  while(1)
  {

  display_kuang();    //显示框
  LCD_GotoXY(0x00,0x02);
  display_ziku();     //ASCII表1
  OR_Two_Layer();//DDRAM1 OR DDRAM2
  Show_Two_Layer();//DDRAM1与DDRAM2同时显示
  delay_nms(1000);
  clear();


  Only_Show_Page1(); //只显示DDRAM1
  Access_Page1();   //只存取DDRAM1
  display_test(0xaa,0x55);	 //显示星
  delay_nms(1500);
  clear();

  lcd_test(); //组装测试
  
  LCD_GotoXY(0x00,0x00);   //设定X,Y坐标位置 
  display_word(tab1,40);   //显示正常汉字
  LCD_GotoXY(0x00,0x13);   //
  bold_word();             //字体变粗
  display_word(tab1,40);   //显示正常汉字
  no_bold_word();          //字体变粗功能关闭
  enlarge(1);    //字体不放大，为16X16点阵大小
  LCD_GotoXY(0x00,0x2c);   
  LCD_ShowStr("川航");
  enlarge(2);    //字体放大2倍，为32X32点阵大小
  LCD_GotoXY(0x04,0x3c);   //
  LCD_ShowStr("川航");
  enlarge(3);    //字体放大3倍
  LCD_GotoXY(0x0c,0x4c);   //
  LCD_ShowStr("川航");
  enlarge(4);    //字体放大4倍
  LCD_GotoXY(0x18,0x5c);   //
  LCD_ShowStr("川航");
  enlarge(2);
  LCD_Inv();     //数据反白
  LCD_GotoXY(0x00,0xa6);   //设定X,Y坐标位置
  LCD_ShowStr("努力做事只是把事做对");
   LCD_GotoXY(0x00,0xd0);   //设定X,Y坐标位置
  LCD_ShowStr("用心做事才能把事做好");
  enlarge(1);
  LCD_NoInv();  //取消反白
  delay_nms(1500);
  clear();

   // LCD_NoInv();  //取消反白
//  disp_Graphic2();    //显示240128的一张图片
//  Access_Page1();   //存取DDRAM1
//  Only_Show_Page1(); //显示DDRAM1
//  LCD_GotoXY(0x02,0x03);   //设定X,Y坐标位置 
//  LCD_ShowStr("深圳市川航电子科技有限公司");   //显示正常汉字
//  enlarge(2);           //字体放大2倍
//  LCD_GotoXY(0x05,0x1a);   //设定X,Y坐标位置 
//  LCD_ShowStr("请点测试区");   //显示正常汉字
//  enlarge(1);	  //字体还原，就是一倍
//  LCD_GotoXY(0x10,0x47);   //设定X,Y坐标位置 
//  LCD_ShowStr("X坐标=");   //显示正常汉字
//  LCD_GotoXY(0x10,0x64);   //设定X,Y坐标位置 
//  LCD_ShowStr("Y坐标=");   //显示正常汉字
//  OR_Two_Layer();//DDRAM1 OR DDRAM2
//  Show_Two_Layer();//DDRAM1与DDRAM2同时显示
////  LCD_CmdWrite(0xc0);     //至能触摸屏扫描
////  LCD_DataWrite(0x80);
////  LCD_CmdWrite(0xc4);
////  LCD_DataWrite(0x00);   //自動模式
////  LCD_CmdWrite(0x0f);
////  LCD_DataWrite(0x10); 
////  EX0=1;
////  EA=1;
////  IT0=1;  
//  delay_nms(1500);
//  clear();
  }        
}