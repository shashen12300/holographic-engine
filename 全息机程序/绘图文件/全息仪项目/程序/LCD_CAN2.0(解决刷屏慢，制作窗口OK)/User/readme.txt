1.头文件说明
	stm32f10x_conf.h  外围固件库调用头文件
	stdint.h          扩展整数类型和宏标准C库头文件
	stm32f10x.h  -->  core_cm3.h and systm_stm32f10x.h and stdint.h
	
	stm32f10x.h       stdint.h
	u8                uint8_t(unsigned char)
	u16               uint16_t
	uint32            uint32_t
2.用户函数说明
	存放组：User
	头文件调用规则：***.c  -->    ***.h (+stm32f10x_conf.h    .c和.h如不使用关键字简单别名可不再包含stdint.h)
3.外围固件库说明
	***.c        -->  ***.h (+rcc.h)
	***.h        -->  stm32f10x.h(-->core_cm3.h and systm_stm32f10x.h and stdint.h)有的没有包含