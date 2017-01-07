#ifndef LCDCONF_H
#define LCDCONF_H


#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL (1)  //LCD颜色灰度，16位

#define LCD_CONTROLLER -1     //官方对一些LCD型号做了注释，而系统并没使用这些型号，所以写-1

#define LCD_MIRROR_X      (1<<1)      
#define LCD_MIRROR_Y      (1<<1)           //XY轴镜像
#define LCD_SWAP_XY       (1<<2) 
#define LCD_INIT_CONTROLLER()     lcm_init()       //UC/GUI中LCD的初始化放在这里                                                    \


 
#endif /* LCDCONF_H */

 
