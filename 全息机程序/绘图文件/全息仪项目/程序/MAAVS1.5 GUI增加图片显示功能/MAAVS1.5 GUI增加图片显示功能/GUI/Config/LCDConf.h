#ifndef LCDCONF_H
#define LCDCONF_H


#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL (1)  //LCD��ɫ�Ҷȣ�16λ

#define LCD_CONTROLLER -1     //�ٷ���һЩLCD�ͺ�����ע�ͣ���ϵͳ��ûʹ����Щ�ͺţ�����д-1

#define LCD_MIRROR_X      (1<<1)      
#define LCD_MIRROR_Y      (1<<1)           //XY�᾵��
#define LCD_SWAP_XY       (1<<2) 
#define LCD_INIT_CONTROLLER()     lcm_init()       //UC/GUI��LCD�ĳ�ʼ����������                                                    \


 
#endif /* LCDCONF_H */

 
