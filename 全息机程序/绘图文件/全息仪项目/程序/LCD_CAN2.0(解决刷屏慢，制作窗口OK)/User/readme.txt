1.ͷ�ļ�˵��
	stm32f10x_conf.h  ��Χ�̼������ͷ�ļ�
	stdint.h          ��չ�������ͺͺ��׼C��ͷ�ļ�
	stm32f10x.h  -->  core_cm3.h and systm_stm32f10x.h and stdint.h
	
	stm32f10x.h       stdint.h
	u8                uint8_t(unsigned char)
	u16               uint16_t
	uint32            uint32_t
2.�û�����˵��
	����飺User
	ͷ�ļ����ù���***.c  -->    ***.h (+stm32f10x_conf.h    .c��.h�粻ʹ�ùؼ��ּ򵥱����ɲ��ٰ���stdint.h)
3.��Χ�̼���˵��
	***.c        -->  ***.h (+rcc.h)
	***.h        -->  stm32f10x.h(-->core_cm3.h and systm_stm32f10x.h and stdint.h)�е�û�а���