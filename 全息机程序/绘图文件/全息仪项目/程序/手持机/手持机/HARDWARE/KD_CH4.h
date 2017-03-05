#ifndef __KD_CH4_H
#define __KD_CH4_H
#include "sys.h"
#include "BSP_PCF8563.h"

#pragma pack(1)

/*Ͷ����رմ�ע��*/
#define DEBUG		1

/*����汾*/
#define SOFTWARE_VERSION	355

/*����ʱ�� ����*/
#define BL_LENGTH_MS										10000
/*�˵��Զ�����ʱ��*/
#define BL_MENU_RETURN_MS								20000
/*Ĭ�ϱ���ʱ��*/
#define ALARM_LONG_S										1

#define	DEFAULT_CH4_MAX									4.0

/*Ĭ�ϱ�������*/
#define	DEFAULT_BL_LUM									9
/*����Ա����*/
#define DEFAULT_ADMIN_PASSWORD					545555

#define DEFAULT_DEV_ID									000001

/*Ĭ�ϼ��鱨����Ũ�� */
#define DEFAULT_CH4_ALARM					    	1.0
#define DEFAULT_TEMP_ALARM					   	36

/*У��ֵ*/
#define DEFAULT_CALIZERO								0.01
#define DEFAULT_AD7705_REF							2.8
#define DEFAULT_AD7705_FULLRANGE				65536
#define DEFAULT_AD7705_GAIN							4

/*Ĭ��У��������Ũ��*/
#define DEFAULT_MJC4_CON								2.4


/*�������� ��ѯʱ�䣬����*/
#define KEY_POLLING_MS								5

/*����Ա�����������Ĭ������*/
#define DEFAULT_DISPLAY_ADMIN_NUMBER		555555

/*�豸��Ϣ��flash��ַ*/
#define FLASH_ADDR_DEV_INFO						0
#define FLASH_ADDR_DATA_NUMBER				4096
/*��ֵ�ĵ�ʱ����Ҫע�⣬�����д�߼�*/
#define FLASH_ADDR_DATA_NUMBER_MAX		256  
#define FLASH_ADDR_DATA								(4096*2)
#define FLASH_DATA_LONG								16

#define DEFAULT_MJC4_OFFSET										50
#define DEFAULT_MJC4_GAIN											0.04

#define OFFSET_FLASH_ADDR							0
#define OFFSET_FLASH_LONG							4

#define MENU_SYSCONFIG_SAMPLE					0
#define MENU_SYSCONFIG_ALARM					1
#define MENU_SYSCONFIG_DISPALY				2
#define MENU_SYSCONFIG_RF							3
#define MENU_SYSCONFIG_STORAGE				4
#define MENU_SYSCONFIG_ADMIN					5
#define MENU_SYSCONFIG_TIME						6
#define MENU_SYSCONFIG_LONG						7


#define MENU_SYSCONFIG_SAMPLE_CALIZERO		0
#define MENU_SYSCONFIG_SAMPLE_CALIGAIN		1
#define MENU_SYSCONFIG_SAMPLE_CALIZERO_D	2
#define MENU_SYSCONFIG_SAMPLE_CALIGAIN_D	3
#define MENU_SYSCONFIG_SAMPLE_LONG				2

#define MENU_SYSCONFIG_ALARM_SV_1						0
#define MENU_SYSCONFIG_ALARM_SV_2						1
#define MENU_SYSCONFIG_ALARM_LONG						2

#define MENU_SYSCONFIG_DISPALY_BLLum		0
#define MENU_SYSCONFIG_DISPALY_BLLong		1
#define MENU_SYSCONFIG_DISPALY_LONG			2

#define MENU_SYSCONFIG_STORAGE_VIEW_DATA		0
#define MENU_SYSCONFIG_STORAGE_CLEAR_DATA		1
#define MENU_SYSCONFIG_STORAGE_LONG					2

#define MENU_SYSCONFIG_RF_DEVICE_ID					0
#define MENU_SYSCONFIG_RF_VIEW_MAC					1
#define MENU_SYSCONFIG_RF_LONG					2

/*У��*/
#define RF_PACKAGE_CALIBRATION_HEAD				0xEE01

/*λ��*/
#define DISPALY_ADDR_RF_ICO_X							40
#define DISPALY_ADDR_RF_ICO_Y							40

#define DISPALY_ADDR_POWER_ICO_X					65
#define DISPALY_ADDR_POWER_ICO_Y					0

#define DISPALY_ADDR_CH4_X								5
#define DISPALY_ADDR_CH4_Y								14

#define DISPALY_ADDR_TEMP_X								0
#define DISPALY_ADDR_TEMP_Y								40

/*�����ϴ�*/
#define RF_PACKAGE_DATA_HEAD					0xEE02
#define QRASK_RF_SEND_DATA						0x53
#define QRASK_KEY_SEND_RETURN					0x12
#define RF_SEND_DATA_LEN							17

#define BSP_LED1_OUT 									PBout(6)
#define	BSP_LED1_GPIO_CLK							RCC_APB2Periph_GPIOB
#define	BSP_LED1_GPIO_PIN							GPIO_Pin_6
#define	BSP_LED1_GPIO_PORT						GPIOB


#define BSP_LED2_OUT 									PAout(12)
#define	BSP_LED2_GPIO_CLK							RCC_APB2Periph_GPIOA 
#define	BSP_LED2_GPIO_PIN							GPIO_Pin_12
#define	BSP_LED2_GPIO_PORT						GPIOA

#define BSP_BUZZER_OUT 									PCout(14)
#define	BSP_BUZZER_GPIO_CLK							RCC_APB2Periph_GPIOC 
#define	BSP_BUZZER_GPIO_PIN							GPIO_Pin_14
#define	BSP_BUZZER_GPIO_PORT						GPIOC

#define BSP_MOTOR_OUT 									PCout(15)
#define	BSP_MOTOR_GPIO_CLK							RCC_APB2Periph_GPIOC 
#define	BSP_MOTOR_GPIO_PIN							GPIO_Pin_15
#define	BSP_MOTOR_GPIO_PORT							GPIOC

#define	BSP_KEY_POW_GPIO_CLK							RCC_APB2Periph_GPIOA
#define	BSP_KEY_POW_GPIO_PIN							GPIO_Pin_11
#define	BSP_KEY_POW_GPIO_PORT							GPIOA

#define	BSP_KEY_FUN_GPIO_CLK							RCC_APB2Periph_GPIOA
#define	BSP_KEY_FUN_GPIO_PIN							GPIO_Pin_5
#define	BSP_KEY_FUN_GPIO_PORT							GPIOA

#define	BSP_KEY_UP_GPIO_CLK								RCC_APB2Periph_GPIOA
#define	BSP_KEY_UP_GPIO_PIN								GPIO_Pin_1
#define	BSP_KEY_UP_GPIO_PORT							GPIOA

#define	BSP_KEY_LOW_GPIO_CLK							RCC_APB2Periph_GPIOA
#define	BSP_KEY_LOW_GPIO_PIN							GPIO_Pin_2
#define	BSP_KEY_LOW_GPIO_PORT							GPIOA

#define	BSP_KEY_SEND_GPIO_CLK								RCC_APB2Periph_GPIOA
#define	BSP_KEY_SEND_GPIO_PIN								GPIO_Pin_4
#define	BSP_KEY_SEND_GPIO_PORT							GPIOA

#define	BSP_KEY_STORE_GPIO_CLK							RCC_APB2Periph_GPIOA
#define	BSP_KEY_STORE_GPIO_PIN							GPIO_Pin_3
#define	BSP_KEY_STORE_GPIO_PORT							GPIOA


#define BSP_KEY_FUN_IN  GPIO_ReadInputDataBit(BSP_KEY_FUN_GPIO_PORT,BSP_KEY_FUN_GPIO_PIN)
#define BSP_KEY_UP_IN  GPIO_ReadInputDataBit(BSP_KEY_UP_GPIO_PORT,BSP_KEY_UP_GPIO_PIN)
#define BSP_KEY_LOW_IN  GPIO_ReadInputDataBit(BSP_KEY_LOW_GPIO_PORT,BSP_KEY_LOW_GPIO_PIN)
#define BSP_KEY_POW_IN  GPIO_ReadInputDataBit(BSP_KEY_POW_GPIO_PORT,BSP_KEY_POW_GPIO_PIN)
#define BSP_KEY_SEND_IN  GPIO_ReadInputDataBit(BSP_KEY_SEND_GPIO_PORT,BSP_KEY_SEND_GPIO_PIN)
#define BSP_KEY_STORE_IN  GPIO_ReadInputDataBit(BSP_KEY_STORE_GPIO_PORT,BSP_KEY_STORE_GPIO_PIN)

#define BSP_AVDD_OUT 										PBout(7)
#define	BSP_AVDD_GPIO_CLK								RCC_APB2Periph_GPIOB
#define	BSP_AVDD_GPIO_PIN								GPIO_Pin_7
#define	BSP_AVDD_GPIO_PORT							GPIOB

#define BSP_DVDD_OUT 										PCout(13)
#define	BSP_DVDD_GPIO_CLK								RCC_APB2Periph_GPIOC
#define	BSP_DVDD_GPIO_PIN								GPIO_Pin_13
#define	BSP_DVDD_GPIO_PORT							GPIOC


#define BSP_EN_POWER_OUT 										PCout(12)
#define	BSP_EN_POWER_GPIO_CLK								RCC_APB2Periph_GPIOC
#define	BSP_EN_POWER_GPIO_PIN								GPIO_Pin_12
#define	BSP_EN_POWER_GPIO_PORT							GPIOC

#define	BSP_ADC_BATT_GPIO_CLK								RCC_APB2Periph_GPIOC
#define	BSP_ADC_BATT_GPIO_PIN								GPIO_Pin_0
#define	BSP_ADC_BATT_GPIO_PORT							GPIOC

#define	BSP_5V_IN_GPIO_CLK								RCC_APB2Periph_GPIOA
#define	BSP_5V_IN_GPIO_PIN								GPIO_Pin_0
#define	BSP_5V_IN_GPIO_PORT								GPIOA



#define BSP_5V_IN  		GPIO_ReadInputDataBit(BSP_5V_IN_GPIO_PORT,BSP_5V_IN_GPIO_PIN)


#define ADC1_DR_Address    ((u32)0x40012400+0x4c)
#define SPI1_DR							SPI1_BASE+0x0C

#define ADC_ConBuffLen		10

typedef struct 
{
	uint8_t down;
	uint8_t up;
	uint8_t puch;
}	KEY_TypeDef;

typedef struct 
{
	KEY_TypeDef Power;
	KEY_TypeDef Fun;
	KEY_TypeDef Higher;
	KEY_TypeDef Low;
	KEY_TypeDef Send;
	KEY_TypeDef Store;
}	DEV_keyTypeDef;

/*ÿ���޸�DEV_info�ṹ��ʱ����Ҫ�޸��������*/
#define DEFAULT_DEV_INFO_LONG				(4*9)
typedef struct 
{
	/*ϵͳ�汾*/
	int SoftwareVersion;
	
	int 	DEV_ID;
	
	float Alarm_CH4;
	
	float Alarm_TEMP; //����
	
	/*У��ƫֵ*/
	float MJC4_Offset;
	/*У����ֵ*/
	float MJC4_Gain;
	
	int 	BL_LUM;
	int 	BL_LONG;
	int   Alarm_Long; //����
}	DEV_info;

/*���߷��ͽṹ��*/
typedef struct 
{
	/*ʱ��*/
	RTC_TimeTypeDef Time;
	
	/*MAC*/
	uint8_t MAC[5];
	
	/*������ֵ*/
	float MJC4;
	
}	RF_SEND_DATA_TypeDef;

/*flash�洢�ṹ��*/
typedef struct 
{
	/*ʱ��*/
	RTC_TimeTypeDef Time;
	/*������ֵ*/
	float MJC4;
	
	float TEMP;
	
	uint32_t ADDR;
	
}	FLASH_DATA_TypeDef;

void LED_Init(void);
void Buzzer_Init(void);
void Motor_Init(void);
void HW_Delay_ms(u32 us);
void HW_Delay_us(u32 us);
void Buzzer_out(void);
void Motor_out(void);
void Key_Init(void);
void Power_Init(void);
uint16_t GetBatt(void);
void Power_Off(void);
uint16_t GetBatt_Voltage(void);
void BSP_Get_CPUID(uint8_t *data);

#endif
