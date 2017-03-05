

//�ǵøĿ�������ʱ��ͳ�����Զ��ػ���

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "includes.h"
#include "KD_CH4.h"
#include "LCD_DXDCG8448.h"
#include "BSP_PCF8563.h"
#include "BSP_TM7705.h"
#include "BSP_ds18b20.h"
#include "image.h"
#include "string.h"
#include "BSP_spi_flash.h"
#include "BSP_nrf24l01.h"

//UCOSIII���������ȼ��û�������ʹ��
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

uint8_t ls2401=0;

/*������ȫ�ֱ���*/
DEV_keyTypeDef DEV_key;
/*�豸��Ϣ��ȫ�ֱ���*/
DEV_info	CH4_info;
/*ϵͳʱ���ȫ�ֱ���*/
RTC_TimeTypeDef Time;
RF_SEND_DATA_TypeDef  RF_SEND_DATA;
FLASH_DATA_TypeDef FLASH_DATA_W,FLASH_DATA_R;

/*����ʱ�������û�а���ʱ����ֵ��һֱ����ֱ����ֵ*/
uint32_t BL_count=0,MeunRetrun_count=0;


OS_Q TaskQ_Return;
OS_Q TaskQ_task_rf;

float fMJC4_ADC,fMJC4_Voltage,fMJC4_Val,f_DS18B20;;


uint8_t RF_RxData[32];
uint8_t RF_TxData[32];
uint8_t DEV_MAC[5];

uint8_t FLASH_READ[256];

OS_ERR err;


void menu_sysconfig_admin(void);
u8	 menu_sysconfig_admin_password(void);
void menu_sysconfig(void);
void menu_sysconfig_time(void);
void menu_sysconfig_sample(void);
void menu_sysconfig_sample_callZero(void);
uint8_t menu_sysconfig_sample_callGain(float MJC4_CON);
void menu_sysconfig_dispaly(void);
void menu_sysconfig_dispaly_BLLong(void);
void menu_sysconfig_dispaly_BLLum(void);
void menu_sysconfig_alarm(void);
void menu_sysconfig_alarm_ch4_sv(void);
void menu_sysconfig_alarm_temp_sv(void);
void menu_sysconfig_storage(void);
void menu_sysconfig_storage_ViewData(void);
void menu_sysconfig_rf(void);
void menu_sysconfig_rf_ViewMAC(void);
void menu_sysconfig_rf_SetID(void);

void CH4_infoToFlash(void);
void Send_key_return_2(void);
void flash_set_DataNumber(int number);
int flash_get_DataNumber(void);
//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void task_start(void *p_arg);

//�������ȼ�
#define MENU_TASK_PRIO		5
//�����ջ��С	
#define MENU_STK_SIZE 		128
//������ƿ�
OS_TCB menu_TaskTCB;
//�����ջ	
CPU_STK MENU_TASK_STK[MENU_STK_SIZE];
void task_menu(void *p_arg);

								 
//�������ȼ�
#define FUN1_TASK_PRIO		5
//�����ջ��С	
#define FUN1_STK_SIZE 		128
//������ƿ�
OS_TCB fUN1_TaskTCB;
//�����ջ	
CPU_STK FUN1_TASK_STK[FUN1_STK_SIZE];
void task_fun(void *p_arg);


//�������ȼ�
#define KEY_TASK_PRIO		4
//�����ջ��С	
#define KEY_STK_SIZE 		128
//������ƿ�
OS_TCB key_TaskTCB;
//�����ջ	
CPU_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void task_key(void *p_arg);


//�������ȼ�
#define WATCHDOG_TASK_PRIO		7
//�����ջ��С	
#define WATCHDOG_STK_SIZE 		128
//������ƿ�
OS_TCB WATCHDOG_TaskTCB;
//�����ջ	
CPU_STK WATCHDOG_TASK_STK[WATCHDOG_STK_SIZE];
//������
void task_watchdog(void *p_arg);



//�������ȼ�
#define TIME_TASK_PRIO		5
//�����ջ��С	
#define TIME_STK_SIZE 		128
//������ƿ�
OS_TCB TIME_TaskTCB;
//�����ջ	
CPU_STK TIME_TASK_STK[TIME_STK_SIZE];
void task_time(void *p_arg);


//�������ȼ�
#define POWER_TASK_PRIO		4
//�����ջ��С	
#define POWER_STK_SIZE 		128
//������ƿ�
OS_TCB POWER_TaskTCB;
//�����ջ	
CPU_STK POWER_TASK_STK[POWER_STK_SIZE];
void task_power(void *p_arg);

//�������ȼ�
#define DATE_TASK_PRIO		5
//�����ջ��С	
#define DATE_STK_SIZE 		128
//������ƿ�
OS_TCB DATE_TaskTCB;
//�����ջ	
CPU_STK DATE_TASK_STK[DATE_STK_SIZE];
void task_date(void *p_arg);

//�������ȼ�
#define RF_TASK_PRIO		5
//�����ջ��С	
#define RF_STK_SIZE 		128
//������ƿ�
OS_TCB RF_TaskTCB;
//�����ջ	
CPU_STK RF_TASK_STK[RF_STK_SIZE];
void task_rf(void *p_arg);

//�������ȼ�
#define ALARM_TASK_PRIO		5
//�����ջ��С	
#define ALARM_STK_SIZE 		128
//������ƿ�
OS_TCB ALARM_TaskTCB;
//�����ջ	
CPU_STK ALARM_TASK_STK[ALARM_STK_SIZE];
void task_alarm(void *p_arg);

//������
int main(void)
{
	int i;
	uint8_t CPUID[15];
	CPU_SR_ALLOC();
	
	delay_init();  //ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	
	
	
	/*��ԴоƬ��ʼ��*/
	Power_Init();
	
	/*���ڳ�ʼ��*/
	uart_init(115200);
	
	Buzzer_Init();
	Motor_Init();
	Key_Init();
	
	/*�ػ�JTAG,�˴���������LCD*/
	/*���ض�������ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
#ifndef DEBUG
		if(BSP_KEY_FUN_IN==1)
		{
			GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
		}
		else
		{
			/*�ض���SWD*/
			GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
		}
#else
		/*�ض���SWD*/
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
#endif
	
	/*LED��ʼ��	*/
	LED_Init();         
	
	/*LCD��ʼ��*/
	LCD_Init();
	/*��ʾ��������*/
	LCD_Printf_GB2312_12x12((84-(6*13))/2,(48-12)/2,"��������Ƽ�");
	

	TM7705_Init();
	DS18B20_Init();
	SPI_FLASH_Init();
	nRF24L01_Init();
	nRF24L01_RxMode();
	
	SPI_FLASH_BufferRead((u8*)&CH4_info.SoftwareVersion,FLASH_ADDR_DEV_INFO,DEFAULT_DEV_INFO_LONG);
	
	/*δ�ҵ��豸��Ϣ�ļ�¼��д��Ĭ��ֵ*/
	if(CH4_info.SoftwareVersion!=SOFTWARE_VERSION)
	{
		/*��Ļ��ʾ*/
		LCD_Printf_GB2312_12x12((84-(6*13))/2,(48-12)/2,"����Ĭ������");
		
		/*д��Ĭ��ֵ*/
		CH4_info.SoftwareVersion=SOFTWARE_VERSION;
		CH4_info.Alarm_CH4=DEFAULT_CH4_ALARM;
		CH4_info.Alarm_TEMP=DEFAULT_TEMP_ALARM;
		CH4_info.DEV_ID=DEFAULT_DEV_ID;
		CH4_info.MJC4_Offset=DEFAULT_MJC4_OFFSET;
		CH4_info.MJC4_Gain=DEFAULT_MJC4_GAIN;
		CH4_info.BL_LUM=DEFAULT_BL_LUM;
		CH4_info.BL_LONG=BL_LENGTH_MS;
		CH4_info.Alarm_Long=ALARM_LONG_S;
		/*д���µ��豸��Ϣ*/
		CH4_infoToFlash();
	}
	
	/*���ñ���*/
	LCD_BL_Init(CH4_info.BL_LUM);
	
	/*��ȡMACCPUID���ֻȡ5λ��������ĵ�5λ��ʼ�������غϵļ��ʱȽϴ�*/
	BSP_Get_CPUID(CPUID);
	for(i=0;i<5;i++)
	{ 
		DEV_MAC[i] = CPUID[i+5]; 
	}
	
	
	OSInit(&err);		    //��ʼ��UCOSIII
	OS_CRITICAL_ENTER();	//�����ٽ���			 
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )task_start, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���
	OSStart(&err);      //����UCOSIII
}

//��ʼ����������
void task_start(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	
		//����POWER����
	OSTaskCreate((OS_TCB 	* )&POWER_TaskTCB,		
				 (CPU_CHAR	* )"POWER task", 		
                 (OS_TASK_PTR )task_power, 			
                 (void		* )0,					
                 (OS_PRIO	  )POWER_TASK_PRIO,     
                 (CPU_STK   * )&POWER_TASK_STK[0],	
                 (CPU_STK_SIZE)POWER_STK_SIZE/10,	
                 (CPU_STK_SIZE)POWER_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
								 
	//����TIME����
	OSTaskCreate((OS_TCB 	* )&TIME_TaskTCB,		
				 (CPU_CHAR	* )"TIME task", 		
                 (OS_TASK_PTR )task_time, 			
                 (void		* )0,					
                 (OS_PRIO	  )TIME_TASK_PRIO,     
                 (CPU_STK   * )&TIME_TASK_STK[0],	
                 (CPU_STK_SIZE)TIME_STK_SIZE/10,	
                 (CPU_STK_SIZE)TIME_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);			
//	
//	//����DATE����
//	OSTaskCreate((OS_TCB 	* )&DATE_TaskTCB,		
//				 (CPU_CHAR	* )"DATE task", 		
//                 (OS_TASK_PTR )task_date, 			
//                 (void		* )0,					
//                 (OS_PRIO	  )DATE_TASK_PRIO,     
//                 (CPU_STK   * )&DATE_TASK_STK[0],	
//                 (CPU_STK_SIZE)DATE_STK_SIZE/10,	
//                 (CPU_STK_SIZE)DATE_STK_SIZE,		
//                 (OS_MSG_QTY  )0,					
//                 (OS_TICK	  )0,					
//                 (void   	* )0,					
//                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
//                 (OS_ERR 	* )&err);		
								 
	//����TASK1����
	OSTaskCreate((OS_TCB 	* )&fUN1_TaskTCB,		
				 (CPU_CHAR	* )"fUN1_ task", 		
                 (OS_TASK_PTR )task_fun, 			
                 (void		* )0,					
                 (OS_PRIO	  )FUN1_TASK_PRIO,     
                 (CPU_STK   * )&FUN1_TASK_STK[0],	
                 (CPU_STK_SIZE)FUN1_STK_SIZE/10,	
                 (CPU_STK_SIZE)FUN1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
				 
	//����KEY����
	OSTaskCreate((OS_TCB 	* )&key_TaskTCB,		
				 (CPU_CHAR	* )"key task", 		
                 (OS_TASK_PTR )task_key, 			
                 (void		* )0,					
                 (OS_PRIO	  )KEY_TASK_PRIO,     	
                 (CPU_STK   * )&KEY_TASK_STK[0],	
                 (CPU_STK_SIZE)KEY_STK_SIZE/10,	
                 (CPU_STK_SIZE)KEY_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);			 
								 
	//���� ����
	OSTaskCreate((OS_TCB 	* )&WATCHDOG_TaskTCB,		
				 (CPU_CHAR	* )"WATCHDOG task", 		
                 (OS_TASK_PTR )task_watchdog, 			
                 (void		* )0,					
                 (OS_PRIO	  )WATCHDOG_TASK_PRIO,     	
                 (CPU_STK   * )&WATCHDOG_TASK_STK[0],	
                 (CPU_STK_SIZE)WATCHDOG_STK_SIZE/10,	
                 (CPU_STK_SIZE)WATCHDOG_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
	//����MENU����
	OSTaskCreate((OS_TCB 	* )&menu_TaskTCB,		
				 (CPU_CHAR	* )"Task1 task", 		
                 (OS_TASK_PTR )task_menu, 			
                 (void		* )0,					
                 (OS_PRIO	  )MENU_TASK_PRIO,     
                 (CPU_STK   * )&MENU_TASK_STK[0],	
                 (CPU_STK_SIZE)MENU_STK_SIZE/10,	
                 (CPU_STK_SIZE)MENU_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
								 
	//����RF����
	OSTaskCreate((OS_TCB 	* )&RF_TaskTCB,		
				 (CPU_CHAR	* )"RF task", 		
                 (OS_TASK_PTR )task_rf, 			
                 (void		* )0,					
                 (OS_PRIO	  )RF_TASK_PRIO,     
                 (CPU_STK   * )&RF_TASK_STK[0],	
                 (CPU_STK_SIZE)RF_STK_SIZE/10,	
                 (CPU_STK_SIZE)RF_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
	
	//����ALARM����
	OSTaskCreate((OS_TCB 	* )&ALARM_TaskTCB,		
				 (CPU_CHAR	* )"ALARM task", 		
                 (OS_TASK_PTR )task_alarm, 			
                 (void		* )0,					
                 (OS_PRIO	  )ALARM_TASK_PRIO,     
                 (CPU_STK   * )&ALARM_TASK_STK[0],	
                 (CPU_STK_SIZE)ALARM_STK_SIZE/10,	
                 (CPU_STK_SIZE)ALARM_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
								 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
								 
	 
								 
	OSTaskDel((OS_TCB*)0,&err);	//ɾ��task_start��������
}

#define flashlong			500
u8 flash_datar[flashlong];

//watchdog������
void task_watchdog(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	
	
	OS_CRITICAL_ENTER();	//�����ٽ���	
	SPI_FLASH_BufferRead(flash_datar,0,flashlong);
	OS_CRITICAL_EXIT();	//�˳��ٽ���	
	
	while(1)
	{

		BSP_LED1_OUT=1;
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
		BSP_LED1_OUT=0;
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}


//ʱ��������
void task_time(void *p_arg)
{
	char str[30];
	
	OS_ERR err;
//	CPU_SR_ALLOC();
	(void)p_arg;
	
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
	RTC_Init();
	
	/*����*/
	LCD_clear();
	
	//LCD_PutGB2312_10x10(0,20,"��");
	while(1)
	{
		
		/*��ȡʱ��*/
		Time=PCF8563_Get_Time();
		
		/*������ʾʱ��*/
		sprintf(str,"%02d-%02d %02d:%02d",Time.Month ,Time.Day,Time.Hour ,Time.Minute);
		//sprintf(str,"%02d��%02d��%02dʱ%02d��",12,22,22,22);
		LCD_Printf(0,0,str);
		
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

//����������
void task_date(void *p_arg)
{
	char str[30];
	
	OS_ERR err;
//	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 

	while(1)
	{
		/*������ʾ����*/
		sprintf(str,"%02d-%02d-%02d",Time.Year ,Time.Month ,Time.Day);
		LCD_Printf(0,8,str);
		
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
//����������
void task_alarm(void *p_arg)
{
//	char str[30];
	
	OS_ERR err;
//	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
	Motor_out();
	Buzzer_out();
	while(1)
	{
		if(f_DS18B20>CH4_info.Alarm_TEMP || fMJC4_Val>CH4_info.Alarm_CH4)
		{
			BSP_BUZZER_OUT=1;
			BSP_MOTOR_OUT=1;
		}
		else
		{
			BSP_MOTOR_OUT=0;
			BSP_BUZZER_OUT=0;
		}
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void task_rf(void *p_arg)
{
	char str[30];
	int ADDR_ID=00;
	int i;
	static uint8_t RF_Rx;
	float callGain;
	/*�������� �յ����ߺ󣬴�ֵ���0,RF_HB_SV=�Ƚ�ֵ*/
	static int RF_HB=200,RF_HB_SV=20;
	void *Msg;
	OS_MSG_SIZE size;
//	u8   Msg_Return;
	u8 	*p;
	CPU_SR_ALLOC();
			
		
	p_arg = p_arg;

	/*������Ϣ����*/
 	OSQCreate((OS_Q *)&TaskQ_task_rf, //��Ϣ����ָ��
  (CPU_CHAR *)"TaskQ_task_rf",     //��Ϣ��������
 	(OS_MSG_QTY) 5,
	(OS_ERR *)&err );
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
	
	while(1)
	{
		//��ѯ��Ϣ
		Msg=OSQPend((OS_Q*			)&TaskQ_task_rf,   
								(OS_TICK		)0,
								(OS_OPT			)OS_OPT_PEND_NON_BLOCKING,
								(OS_MSG_SIZE*	)&size,		
								(CPU_TS*		)0,
								(OS_ERR*		)&err);
		
		
		/*�յ���Ϣ��RF��������*/
		if((int)Msg==QRASK_RF_SEND_DATA)
		{
			RF_SEND_DATA.Time=Time;
			for(i=0;i<5;i++)
			{
					RF_SEND_DATA.MAC[i]=DEV_MAC[i];
			}
			RF_SEND_DATA.MJC4=fMJC4_Val;
			
			p=&RF_SEND_DATA.Time.Second;
			
			for(i=0;i<RF_SEND_DATA_LEN;i++)RF_TxData[i]=p[i];
			
			OS_CRITICAL_ENTER();	//�����ٽ���	
			nRF24L01_TxMode();
			nRF24L01_TxData(RF_TxData);
			nRF24L01_RxMode();
			OS_CRITICAL_EXIT();	//�˳��ٽ���	
			
			OSTaskSuspend(&fUN1_TaskTCB,&err);
			LCD_clear();
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѷ���");
			OSTimeDlyHMSM(0,0,1,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
			OSTaskResume(&fUN1_TaskTCB,&err);
			
		}
		
		/*��ѯ������Ϣ*/
		OS_CRITICAL_ENTER();	//�����ٽ���	
		RF_Rx=nRF24L01_RxData(RF_RxData);
		OS_CRITICAL_EXIT();	//�˳��ٽ���	

		
		/*�յ���ָ��*/
		if(RF_Rx>0 && RF_RxData[0]==(uint8_t)(RF_PACKAGE_CALIBRATION_HEAD>>8) && RF_RxData[1]==(uint8_t)RF_PACKAGE_CALIBRATION_HEAD)
		{
			/*��0���������,ʵ�ֱ���Ĵ�*/
			BL_count=0;
			
			OSTaskSuspend(&fUN1_TaskTCB,&err);
			LCD_clear_range(0,18,82,28);
			LCD_Printf_GB2312_12x12((84-(13*6))/2,20,"�յ�����ָ��");
			OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
			OSTaskResume(&fUN1_TaskTCB,&err);
			
			/*��ָ����У��*/
			if(RF_RxData[2]==0 && RF_RxData[3]==0 && RF_RxData[4]==0)
			{
				menu_sysconfig_sample_callZero();
			}
			/*��ָ����У����*/
			else
			{
				/*��Э������ȡ����*/
				callGain=(float)(RF_RxData[2]*100+RF_RxData[3]*10+RF_RxData[4])/100;
				menu_sysconfig_sample_callGain(callGain);
			}
		}
		
		/*����յ�����*/
		if(RF_Rx>0)
		{
			RF_HB=0;
			//LCD_PutImage(6*8+2+13,0,1,8,(char*)RF_RxData);
		}
		else
		{
			RF_HB++;
		}
		
		/*�ж��Ƿ��л�վ�ź�,����ʾ*/
		if(RF_HB>RF_HB_SV)
		{
			/*���ź�*/
			LCD_PutImage(DISPALY_ADDR_RF_ICO_X,DISPALY_ADDR_RF_ICO_Y,12,8,RSSI_0);
			BSP_LED2_OUT=1;
		}
		else
		{
			/*���ź�*/
			LCD_PutImage(DISPALY_ADDR_RF_ICO_X,DISPALY_ADDR_RF_ICO_Y,12,8,RSSI_4);
			BSP_LED2_OUT=0;
		}
		/*��ʾλ����Ϣ*/
		sprintf(str,"%03d",ADDR_ID);
		LCD_Printf(DISPALY_ADDR_RF_ICO_X+20,DISPALY_ADDR_RF_ICO_Y,"000");
		
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
//POWER������
void task_power(void *p_arg)
{
	uint16_t batt;
	
	static uint32_t FlashID = 0;
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	
	 /* Get SPI Flash ID */
	OS_CRITICAL_ENTER();	//�����ٽ���	
  FlashID = SPI_FLASH_ReadID()&0xFFFFFF00;
	OS_CRITICAL_EXIT();	//�˳��ٽ���	
	if( sFLASH_ID != FlashID)
	{
		while(1)
		{
			LCD_Printf(0,0,"flash error");
		}
	}
	
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
	
	
	
	while(1)
	{
		/*��ȡ��ص���*/
		batt=GetBatt();

		if(batt<=100 && batt>75)
		{
			LCD_PutImage(DISPALY_ADDR_POWER_ICO_X,DISPALY_ADDR_POWER_ICO_Y,20,8,BATT_100);
		}
		else if(batt<=75 && batt>50)
		{
			LCD_PutImage(DISPALY_ADDR_POWER_ICO_X,DISPALY_ADDR_POWER_ICO_Y,20,8,BATT_75);
		}
		else if(batt<=50 && batt>25)
		{
			LCD_PutImage(DISPALY_ADDR_POWER_ICO_X,DISPALY_ADDR_POWER_ICO_Y,20,8,BATT_50);
		}
		else if(batt<=25)
		{
			LCD_PutImage(DISPALY_ADDR_POWER_ICO_X,DISPALY_ADDR_POWER_ICO_Y,20,8,BATT_25);
		}
		
		/*��Դ�������£�ʱ��>3S�ػ�*/
		if(DEV_key.Power.down>=30)
		{
			/*�����ٽ���*/
			OS_CRITICAL_ENTER();	
			/*�Զ��ػ�*/
			Power_Off();
		}
		
		
		#ifndef DEBUG
		/*�͵�ѹ�Զ��ػ�*/
		if(batt==0)
		{
			/*�����ٽ���*/
			OS_CRITICAL_ENTER();		 
			/*�Զ��ػ�*/
			Power_Off();
		}
		
		#endif
		

		
		#ifndef DEBUG
		/*�����5V���룬�Զ��ػ�*/
		if(BSP_5V_IN==1)
		{

			/*��ʾ���ڳ��*/
			LCD_Printf(0,1,"Charging...");
			OSTimeDlyHMSM(0,0,2,800,OS_OPT_TIME_HMSM_STRICT,&err);
			
	 		/*�����ٽ���*/
			OS_CRITICAL_ENTER();	
			/*�Զ��ػ�*/
			Power_Off();
		}
		#endif

		
		
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

//fun������
void task_fun(void *p_arg)
{
	
	char str[30];
	u16 adc1;

		
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	/*��������*/
	//OSTaskSuspend(&fUN1_TaskTCB,&err); //**********************
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err);
	
	
	/*����*/
	LCD_clear();
	
	while(1)
	{

		/*��ȡ������ֵ*/
		OS_CRITICAL_ENTER();	//�����ٽ���	
		adc1 = TM7705_ReadAdc(1);
		OS_CRITICAL_EXIT();	//�˳��ٽ���	
		
		/*�����ѹ*/
		fMJC4_ADC=adc1;
		fMJC4_Voltage=DEFAULT_AD7705_REF/DEFAULT_AD7705_FULLRANGE*fMJC4_ADC/DEFAULT_AD7705_GAIN;
		//ת��Ϊmv
		fMJC4_Voltage=fMJC4_Voltage*1000;
		
		
		/*�����Ũ��ֵ +��ֹ��Ư��ƫ�ƣ�DEFAULT_CALIZERO*/
		fMJC4_Val=(fMJC4_Voltage-CH4_info.MJC4_Offset)*CH4_info.MJC4_Gain+DEFAULT_CALIZERO;
		
		/*��ֹΪ����*/
		if(fMJC4_Val<0)fMJC4_Val=0;
		
		/*��ֹ���*/
		if(fMJC4_Val>DEFAULT_CH4_MAX)fMJC4_Val=DEFAULT_CH4_MAX;
		
		sprintf(str,"%4.2f%%",fMJC4_Val);
		/*��������ֹ��Ӱ*/
		LCD_clear_range(DISPALY_ADDR_CH4_X,DISPALY_ADDR_CH4_Y,79,24);
		LCD_Printf_NUMBER_16x24(DISPALY_ADDR_CH4_X,DISPALY_ADDR_CH4_Y,str);
		
		
		/*��ȡDS18B20*/
		OS_CRITICAL_ENTER();	//�����ٽ���	
		if(LCD_BL_OUT!=0)
		{
			f_DS18B20=DS18B20_Get_Temp();
		}
		/*��������˽�Ƶģʽ*/
		else
		{
			/*ϵͳƵ�ʻָ�*/
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
			f_DS18B20=DS18B20_Get_Temp();
			/*ϵͳ��Ƶ*/
			RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
		}
		OS_CRITICAL_EXIT();	//�˳��ٽ���	
		
		
		sprintf(str,"%4.1f",f_DS18B20);
		LCD_Printf(DISPALY_ADDR_TEMP_X,DISPALY_ADDR_TEMP_Y,str);
		LCD_PutImage(DISPALY_ADDR_TEMP_X+6*4,DISPALY_ADDR_TEMP_Y,8,8,Celsius);
		
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
		
	}
}


void task_key(void *p_arg)
{
	OS_ERR err;
//	CPU_SR_ALLOC();
	
	
	static char *Msg;
	OS_MSG_SIZE size;
	
	p_arg = p_arg;
	
	/*������Ϣ����*/
 	OSQCreate((OS_Q *)&TaskQ_Return, //��Ϣ����ָ��
  (CPU_CHAR *)"TaskQ_Return",     //��Ϣ��������
 	(OS_MSG_QTY) 5,
	(OS_ERR *)&err );
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 

	while(1)
	{
		
		if(BSP_KEY_POW_IN==0)
		{
			DEV_key.Power.down++;
		}
		else if(DEV_key.Power.down>=1 && BSP_KEY_POW_IN==1)
		{
			DEV_key.Power.down=0;
			DEV_key.Power.puch=1;
		}
		
		if(BSP_KEY_FUN_IN==0)
		{
			DEV_key.Fun.down++;
		}
		else if(DEV_key.Fun.down>=1 && BSP_KEY_FUN_IN==1)
		{
			DEV_key.Fun.down=0;
			DEV_key.Fun.puch=1;
		}
		
		if(BSP_KEY_UP_IN==0)
		{
			DEV_key.Higher.down++;
		}
		else if(DEV_key.Higher.down>=1 && BSP_KEY_UP_IN==1)
		{
			DEV_key.Higher.down=0;
			DEV_key.Higher.puch=1;
		}
		
		if(BSP_KEY_LOW_IN==0)
		{
			DEV_key.Low.down++;
		}
		else if(DEV_key.Low.down>=1 && BSP_KEY_LOW_IN==1)
		{
			DEV_key.Low.down=0;
			DEV_key.Low.puch=1;
		}
		
		if(BSP_KEY_STORE_IN==0)
		{
			DEV_key.Store.down++;
		}
		else if(DEV_key.Store.down>=1 && BSP_KEY_STORE_IN==1)
		{
			DEV_key.Store.down=0;
			DEV_key.Store.puch=1;
		}
		
		if(BSP_KEY_SEND_IN==0)
		{
			DEV_key.Send.down++;
		}
		else if(DEV_key.Send.down>=1 && BSP_KEY_SEND_IN==1)
		{
			DEV_key.Send.down=0;
			DEV_key.Send.puch=1;
		}
		

		/*δ��⵽�������ۼ�ʱ��>CH4_info.BL_LONG */
		if((KEY_POLLING_MS*BL_count)>=CH4_info.BL_LONG)
		{
			/*�رձ���*/
			LCD_BL_OUT=0;
			/*ϵͳ��Ƶ*/
			RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
			
			/*�����⵽����*/
			if(DEV_key.Power.puch>0 || DEV_key.Fun.puch>0 || DEV_key.Higher.puch>0 || DEV_key.Low.puch>0)
			{
				/*�򿪱���*/
				LCD_BL_OUT=CH4_info.BL_LUM;
				/*ϵͳƵ�ʻָ�*/
				RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
				
				/*���а�����Ϊ0*/
				DEV_key.Power.puch=0;
				DEV_key.Fun.puch=0;
				DEV_key.Higher.puch=0;
				DEV_key.Low.puch=0;
				
				/*��0���������*/
				BL_count=0;
			}
		}
		/*δ��⵽�������ۼ�ʱ��<CH4_info.BL_LONG */
		else
		{
			/*�����⵽����*/
			if(DEV_key.Power.puch>0 || DEV_key.Fun.puch>0 || DEV_key.Higher.puch>0 || DEV_key.Low.puch>0)
			{
				/*��0���������*/
				BL_count=0;
				/*�˵���ʱ���޲����Զ����ؼ�����0*/
				MeunRetrun_count=0;
			}
		}
		
		
		/*��������Լ�*/
		BL_count++;
		/*�˵���ʱ���޲����Զ����ؼ����Լ�*/
		MeunRetrun_count++;
		
		//������ϢKEY_Msg
		Msg=OSQPend((OS_Q*			)&TaskQ_Return,   
								(OS_TICK		)0,
								(OS_OPT			)OS_OPT_PEND_NON_BLOCKING,
								(OS_MSG_SIZE*	)&size,		
								(CPU_TS*		)0,
								(OS_ERR*		)&err);
		
		/*����յ���Ҫreturn����Ϣ*/
		if((int)Msg==QRASK_KEY_SEND_RETURN)
		{
			DEV_key.Power.puch=1;
		}
		
//		/*��ʾ����*/
//		if(DEV_key.Power.down>=1)
//		{
//			LCD_Printf(65,0,"K1");
//		}
//		else if(DEV_key.Fun.down>=1)
//		{
//			LCD_Printf(65,0,"K2");
//		}
//		else if(DEV_key.Higher.down>=1)
//		{
//			LCD_Printf(65,0,"K3");
//		}
//		else if(DEV_key.Low.down>=1)
//		{
//			LCD_Printf(65,0,"K4");
//		}
		OSTimeDlyHMSM(0,0,0,KEY_POLLING_MS,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

//MENU������
void task_menu(void *p_arg)
{
	char str[40];
	uint16_t Batt_Voltage,adc1;
	int i;
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_HMSM_STRICT,&err); 
	

	
	while(1)
	{

		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			menu_sysconfig();
		}
		/*���ͼ�����*/
		if(DEV_key.Send.puch==1)
		{
			DEV_key.Send.puch=0;
			
			/*������Ϣ�������߲���*/
			OSQPost((OS_Q*		)&TaskQ_task_rf,		
			(void*		)(char)QRASK_RF_SEND_DATA,
			(OS_MSG_SIZE)1,
			(OS_OPT		)OS_OPT_POST_FIFO,
			(OS_ERR*	)&err);
		}
		
		/*�洢������*/
		if(DEV_key.Store.puch==1)
		{
			DEV_key.Store.puch=0;
			
			OS_CRITICAL_ENTER();	//�����ٽ���
			i=flash_get_DataNumber();
			ls2401=i;
			flash_set_DataNumber(i);
			
			FLASH_DATA_W.Time=Time;
			FLASH_DATA_W.MJC4=fMJC4_Val;
			FLASH_DATA_W.TEMP=f_DS18B20;
			FLASH_DATA_W.ADDR=0;
			
			SPI_FLASH_BufferWrite(&FLASH_DATA_W.Time.Second,FLASH_ADDR_DATA+(i*FLASH_DATA_LONG),FLASH_DATA_LONG);
			
			OS_CRITICAL_EXIT();	//�˳��ٽ���	
			
			OSTaskSuspend(&fUN1_TaskTCB,&err);
			LCD_clear();
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�Ѵ���");
			OSTimeDlyHMSM(0,0,1,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
			OSTaskResume(&fUN1_TaskTCB,&err);
			
		}
		/*�¼�������*/
		if(DEV_key.Low.down>=1)
		{
			/*��������*/
			OSTaskSuspend(&fUN1_TaskTCB,&err);
			
			/*����*/
			LCD_clear();
			
			/*����¼���һֱ�����£�һֱѭ��*/
			while(DEV_key.Low.down>=1)
			{

				/*��ʾ��������ѹ*/
				/*��ȡ������ֵ*/
				adc1 = TM7705_ReadAdc(1);
				/*�����ѹ*/
				fMJC4_ADC=adc1;
				fMJC4_Voltage=DEFAULT_AD7705_REF/DEFAULT_AD7705_FULLRANGE*fMJC4_ADC/DEFAULT_AD7705_GAIN;
				//ת��Ϊmv
				fMJC4_Voltage=fMJC4_Voltage*1000-CH4_info.MJC4_Offset;
				
				sprintf(str,"MJC4:%5.2fmV ",fMJC4_Voltage);
				LCD_Printf(0,1*8,str);
				
				/*��ʾ��ص�ѹ*/
				Batt_Voltage=GetBatt_Voltage();
				sprintf(str,"Batt:%04dmV",Batt_Voltage);
				LCD_Printf(0,2*8,str);
				
				/*��ʾ���鱨����Ũ��*/
				sprintf(str,"Alarm:%4.2f%% ",(float)CH4_info.Alarm_CH4/100);
				LCD_Printf(0,3*8,str);
				

				
	
				OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); 
			}
			
			/*����*/
			LCD_clear();
			/*�ָ�����*/
			OSTaskResume(&fUN1_TaskTCB,&err);
			

			/*���а�����Ϊ0*/
			DEV_key.Power.puch=0;
			DEV_key.Fun.puch=0;
			DEV_key.Higher.puch=0;
			DEV_key.Low.puch=0;
		}
		

		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;

		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); 
	}
}

int16_t str_L[7];

u8 menu_sysconfig_admin_password(void)
{
	char str[40];
	
	/*��ʼ���ַ���ָ���ڵ�һλ*/
	uint16_t StrP=1;
	
	/*��ʼ����Ҫ�������ʾ����*/
	u32 in_password=DEFAULT_DISPLAY_ADMIN_NUMBER;
	
	OS_ERR err;
	
	str_L[1]=(in_password/100000)%10;
	str_L[2]=(in_password/10000)%10;
	str_L[3]=(in_password/1000)%10;
	str_L[4]=(in_password/100)%10;
	str_L[5]=(in_password/10)%10;
	str_L[6]=(in_password/1)%10;

	/*����*/
	LCD_clear();
	
	LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"�����������");

	while(1)
	{

		

		/*�ҵ�ȷ���������ƶ�һλ*/
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			StrP++;
		}
		
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*��Ӧ��λ�Լ�*/
			str_L[StrP]++;
			
			/*��ֹ���*/
			if(str_L[StrP]>9)str_L[StrP]=0;
			
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			/*��Ӧ��λ�Լ�*/
			str_L[StrP]--;
			
			/*��ֹ���*/
			if(str_L[StrP]<0)str_L[StrP]=9;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return 1;
		}
		
		/*��������룬ʵ�������Աȵ�������һ����ֵ����������*/
		in_password=str_L[1]*100000+str_L[2]*10000+str_L[3]*1000+str_L[4]*100+str_L[5]*10+str_L[6];
		
		/*��ֹ��Ӱ*/
		LCD_clear_range((84-(9*6))/2-1,40-1,(9*6),9);
		sprintf(str,"%d",in_password);
		LCD_Printf_invert((84-6*6)/2,40,str,StrP);
		
		/*�����������*/
		if(StrP>6)
		{
			/*����*/
			LCD_clear();
			if(in_password==DEFAULT_ADMIN_PASSWORD)
			{
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"������ȷ");
				OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
				
				/*����*/
				return 0;
			}
			else
			{
				/*����*/
				LCD_clear();
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�������");
				
				OSTimeDlyHMSM(0,0,1,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
				
				/*����*/
				LCD_clear();
				LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"�����������");
				
				/*ָ������ָ���һλ*/
				StrP=1;
				
				/*���а�����Ϊ0*/
				DEV_key.Power.puch=0;
				DEV_key.Fun.puch=0;
				DEV_key.Higher.puch=0;
				DEV_key.Low.puch=0;
			}
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig(void)
{
	int16_t index=0;
	int16_t menu_index_MAX=MENU_SYSCONFIG_LONG;
	OS_ERR err;
	
	/*��������*/
	OSTaskSuspend(&fUN1_TaskTCB,&err);
	OSTaskSuspend(&RF_TaskTCB,&err);
	//OSTaskSuspend(&POWER_TaskTCB,&err);

	
	/*����*/
	LCD_clear();
	
	
	while(1)
	{
		
		switch (index)
		{
			
			case MENU_SYSCONFIG_ALARM:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��������");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					menu_sysconfig_alarm();
				}
				break;
			
			case MENU_SYSCONFIG_SAMPLE:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"У������");
			if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					
					menu_sysconfig_sample();
				}
				break;
			case MENU_SYSCONFIG_DISPALY:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��ʾ����");
			if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					
					menu_sysconfig_dispaly();
				}
				break;
			case MENU_SYSCONFIG_RF:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��������");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					menu_sysconfig_rf();
					
				}
				break;
			case MENU_SYSCONFIG_STORAGE:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"���ݴ洢");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					menu_sysconfig_storage();
					
				}
				break;
			case MENU_SYSCONFIG_ADMIN:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"����Ȩ��");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					
					if(menu_sysconfig_admin_password()==0)
					{
						menu_sysconfig_admin();
					}
				}
				break;
			case MENU_SYSCONFIG_TIME:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"ʱ������");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					/*����*/
					LCD_clear();
					
					menu_sysconfig_time();
				}
				break;
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*�ָ�����*/
			OSTaskResume(&fUN1_TaskTCB,&err);
			OSTaskResume(&RF_TaskTCB,&err);
			//OSTaskResume(&POWER_TaskTCB,&err);
			
			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_admin(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	
	/*���а�����Ϊ0*/
	DEV_key.Power.puch=0;
	DEV_key.Fun.puch=0;
	DEV_key.Higher.puch=0;
	DEV_key.Low.puch=0;
	
	/*����*/
	LCD_clear();

	//LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"���뱣������");
	while(1)
	{
		LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"ϵͳ��λ");
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			/*���ϵͳ����*/
			OS_CRITICAL_ENTER();	//�����ٽ���	
			SPI_FLASH_SectorErase(FLASH_ADDR_DEV_INFO);
			SPI_FLASH_SectorErase(FLASH_ADDR_DATA_NUMBER);
			SPI_FLASH_SectorErase(FLASH_ADDR_DATA);
			OS_CRITICAL_EXIT();	//�˳��ٽ���	
			
			/*�����ٽ���*/
			OS_CRITICAL_ENTER();	
			
			/*�Զ��ػ�*/
			Power_Off();
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();

			/*����*/
			return;
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

void menu_sysconfig_sample_callZero(void)
{
	u16 adc1;
	CPU_SR_ALLOC();
	/*����*/
	LCD_clear();
	
	/*��ȡ������ֵ*/
	OS_CRITICAL_ENTER();	//�����ٽ���	
	adc1 = TM7705_ReadAdc(1);
	OS_CRITICAL_EXIT();	//�˳��ٽ���	
	
	/*�����ѹ*/
	fMJC4_ADC=adc1;
	fMJC4_Voltage=DEFAULT_AD7705_REF/DEFAULT_AD7705_FULLRANGE*fMJC4_ADC/DEFAULT_AD7705_GAIN;
	//ת��Ϊmv
	fMJC4_Voltage=fMJC4_Voltage*1000;
	
	//CH4_info.MJC4_Offset=fMJC4_Voltage-(1/CH4_info.MJC4_Gain*DEFAULT_CALIZERO);
	CH4_info.MJC4_Offset=fMJC4_Voltage;
	
	/*д���µ��豸��Ϣ*/
	CH4_infoToFlash();

}


uint8_t menu_sysconfig_sample_callGain(float MJC4_CON)
{
	CPU_SR_ALLOC();
	u16 adc1;
	float fMJC4_Gain;
	/*����*/
	LCD_clear();
	
	/*��������0��������Ĭ��ֵ*/
	if(MJC4_CON==0)
	{
		MJC4_CON=DEFAULT_MJC4_CON;
	}
	MJC4_CON=MJC4_CON-DEFAULT_CALIZERO;
	/*��ȡ������ֵ*/
	OS_CRITICAL_ENTER();	//�����ٽ���	
	adc1 = TM7705_ReadAdc(1);
	OS_CRITICAL_EXIT();	//�˳��ٽ���	
	
	/*�����ѹ*/
	fMJC4_ADC=adc1;
	fMJC4_Voltage=DEFAULT_AD7705_REF/DEFAULT_AD7705_FULLRANGE*fMJC4_ADC/DEFAULT_AD7705_GAIN;
	//ת��Ϊmv
	fMJC4_Voltage=fMJC4_Voltage*1000;
	
	fMJC4_Gain=MJC4_CON/(fMJC4_Voltage-CH4_info.MJC4_Offset);
	
	if(fMJC4_Gain>1)
	{
		return 1;
	}
	/*���������*/
	CH4_info.MJC4_Gain=fMJC4_Gain;
	
	/*д���µ��豸��Ϣ*/
	CH4_infoToFlash();
	
	return 0;
}
void CH4_infoToFlash(void)
{
	CPU_SR_ALLOC();
	/*д���µ��豸��Ϣ*/
	OS_CRITICAL_ENTER();	//�����ٽ���	
	SPI_FLASH_SectorErase(FLASH_ADDR_DEV_INFO);
	SPI_FLASH_BufferWrite((u8*)&CH4_info.SoftwareVersion,FLASH_ADDR_DEV_INFO,DEFAULT_DEV_INFO_LONG);
	SPI_FLASH_BufferRead((u8*)&CH4_info.SoftwareVersion,FLASH_ADDR_DEV_INFO,DEFAULT_DEV_INFO_LONG);
	OS_CRITICAL_EXIT();	//�˳��ٽ���	
}
void menu_sysconfig_sample(void)
{
	OS_ERR err;
//	u8 Msg;
	char str[20];
	
	int index=0,menu_index_MAX=MENU_SYSCONFIG_SAMPLE_LONG;
	
	while(1)
	{
		
		switch (index)
		{
			case MENU_SYSCONFIG_SAMPLE_CALIZERO:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"���У��");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_sample_callZero();
					LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��У��");
					OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
					LCD_clear();
				
					/*�����¼�,��Key���̲�������return*/
					Send_key_return_2();
				}
				break;
				
			case MENU_SYSCONFIG_SAMPLE_CALIGAIN:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"����У��");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					if(menu_sysconfig_sample_callGain(DEFAULT_MJC4_CON)==0)
					{
						LCD_Printf_GB2312_12x12((84-(13*3))/2,16,"��У��");
					}
					else
					{
						LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"У��ʧ��");
					}
					LCD_Printf_GB2312_12x12(0,30,"����");
					sprintf(str,":%4.2f%%",DEFAULT_MJC4_CON);
					LCD_Printf(13*2,34,str);
				
					OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
					LCD_clear();
				
					/*�����¼�,��Key���̲�������return*/
					Send_key_return_2();
				}
				break;
				
				
//			case MENU_SYSCONFIG_SAMPLE_CALIZERO_D:
//				LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"��ʱУ�����");
//				if(DEV_key.Fun.puch==1)
//				{
//					DEV_key.Fun.puch=0;
//					
//					LCD_Printf_GB2312_12x12(10,30,"�ȴ�");
//					LCD_Printf(10+(13*2),34,"20");
//					LCD_Printf_GB2312_12x12(10+(13*2)+12,30,"��");
//					OSTimeDlyHMSM(0,0,20,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
//					
//					menu_sysconfig_sample_callZero();
//					LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��У��");
//					OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
//					LCD_clear();
//				
//					/*�����¼�,��Key���̲�������return*/
//					Send_key_return_2();
//				}
//				break;
//				
//			case MENU_SYSCONFIG_SAMPLE_CALIGAIN_D:
//				LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"��ʱУ������");
//				if(DEV_key.Fun.puch==1)
//				{
//					DEV_key.Fun.puch=0;
//					
//					LCD_Printf_GB2312_12x12(10,30,"�ȴ�");
//					LCD_Printf(10+(13*2),34,"20");
//					LCD_Printf_GB2312_12x12(10+(13*2)+12,30,"��");
//					OSTimeDlyHMSM(0,0,20,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
//					
//					menu_sysconfig_sample_callGain(DEFAULT_MJC4_CON);
//					LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��У����");
//				
//					LCD_Printf_GB2312_12x12(0,30,"����");
//					sprintf(str,":%4.2f%%",DEFAULT_MJC4_CON);
//					LCD_Printf(13*2,34,str);
//				
//					OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
//					LCD_clear();
//				
//					/*�����¼�,��Key���̲�������return*/
//					Send_key_return_2();
//				}
//				break;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_time(void)
{
	OS_ERR err;
//	CPU_SR_ALLOC();
	
	char str[40];
	RTC_TimeTypeDef su_Time=Time;
	int16_t index=12;
	
	while(1)
	{
		
		
		sprintf(str,"%02d-%02d-%02d",su_Time.Year+2000 ,su_Time.Month ,su_Time.Day );
		LCD_Printf(0+10,0+20,str);
		
		sprintf(str,"%02d:%02d:%02d",su_Time.Hour ,su_Time.Minute ,su_Time.Second );
		LCD_Printf(6+10,8+20,str);
		
		switch (index)
		{
			case 1:
				sprintf(str,"%02d",su_Time.Second);
				LCD_Printf_invert(6+10+(6*6),8+20,str,2);
				break;
			case 2:
				sprintf(str,"%02d",su_Time.Second);
				LCD_Printf_invert(6+10+(6*6),8+20,str,1);
				break;
			case 3:
				sprintf(str,"%02d",su_Time.Minute);
				LCD_Printf_invert(6+10+(6*3),8+20,str,2);
				break;
			case 4:
				sprintf(str,"%02d",su_Time.Minute);
				LCD_Printf_invert(6+10+(6*3),8+20,str,1);
				break;
			case 5:
				sprintf(str,"%02d",su_Time.Hour);
				LCD_Printf_invert(6+10+(6*0),8+20,str,2);
				break;
			case 6:
				sprintf(str,"%02d",su_Time.Hour);
				LCD_Printf_invert(6+10+(6*0),8+20,str,1);
				break;
			case 7:
				sprintf(str,"%02d",su_Time.Day);
				LCD_Printf_invert(0+10+(6*8),0+20,str,2);
				break;
			case 8:
				sprintf(str,"%02d",su_Time.Day);
				LCD_Printf_invert(0+10+(6*8),0+20,str,1);
				break;
			case 9:
				sprintf(str,"%02d",su_Time.Month);
				LCD_Printf_invert(0+10+(6*5),0+20,str,2);
				break;
			case 10:
				sprintf(str,"%02d",su_Time.Month);
				LCD_Printf_invert(0+10+(6*5),0+20,str,1);
				break;
			case 11:
				sprintf(str,"%02d",su_Time.Year);
				LCD_Printf_invert(0+10+(6*2),0+20,str,2);
				break;
			case 12:
				sprintf(str,"%02d",su_Time.Year);
				LCD_Printf_invert(0+10+(6*2),0+20,str,1);
				break;
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			switch (index)
			{
				case 1:
					if(su_Time.Second%10<9)su_Time.Second++;
					break;
				case 2:
					if(su_Time.Second<50)su_Time.Second=su_Time.Second+10;
					break;
				case 3:
					if(su_Time.Minute%10<9)su_Time.Minute++;
					break;
				case 4:
					if(su_Time.Minute<50)su_Time.Minute=su_Time.Minute+10;
					break;
				case 5:
					if(su_Time.Hour%10<9)su_Time.Hour++;
					break;
				case 6:
					if(su_Time.Hour<=10)su_Time.Hour=su_Time.Hour+10;
					break;
				case 7:
					if(su_Time.Day%10<9)su_Time.Day++;
					break;
				case 8:
					if(su_Time.Day<=20)su_Time.Day=su_Time.Day+10;
					break;
				case 9:
					if(su_Time.Month%10<9)su_Time.Month++;
					break;
				case 10:
					if(su_Time.Month<2)su_Time.Month=su_Time.Month+10;
					break;
				case 11:
					if(su_Time.Year%10<9)su_Time.Year++;
					break;
				case 12:
					if(su_Time.Year<=80)su_Time.Year=su_Time.Year+10;
					break;
			}
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			switch (index)
			{
				case 1:
					if(su_Time.Second%10>0)su_Time.Second--;
					break;
				case 2:
					if(su_Time.Second>10)su_Time.Second=su_Time.Second-10;
					break;
				case 3:
					if(su_Time.Minute%10>0)su_Time.Minute--;
					break;
				case 4:
					if(su_Time.Minute>10)su_Time.Minute=su_Time.Minute-10;
					break;
				case 5:
					if(su_Time.Hour%10>0)su_Time.Hour--;
					break;
				case 6:
					if(su_Time.Hour>10)su_Time.Hour=su_Time.Hour-10;
					break;
				case 7:
					if(su_Time.Day%10>0)su_Time.Day--;
					break;
				case 8:
					if(su_Time.Day>10)su_Time.Day=su_Time.Day-10;
					break;
				case 9:
					if(su_Time.Month%10>0)su_Time.Month--;
					break;
				case 10:
					if(su_Time.Month>10)su_Time.Month=su_Time.Month-10;
					break;
				case 11:
					if(su_Time.Year%10>0)su_Time.Year--;
					break;
				case 12:
					if(su_Time.Year>10)su_Time.Year=su_Time.Year-10;
					break;
			}
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			index--;
			
			/*����*/
			LCD_clear();
			
			if(index<=0)
			{
				/*д��ϵͳʱ��*/
				PCF8563_Set_Time(su_Time);
				
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
				OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
				LCD_clear();
					
				/*�����¼�,��Key���̲�������return*/
				Send_key_return_2();
				
				/*����*/
				return;
			}
			
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();

			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}

}
void menu_sysconfig_dispaly_BLLum(void)
{
	int  menu_index_MAX=10;
	int  index=CH4_info.BL_LUM;
	char str[20];
	
	while(1)
	{
		TIM3->CCR3=index;
		CH4_info.BL_LUM=index;
		
		sprintf(str,"0-9:%d",index);
		LCD_Printf((84-(6*5))/2,40,str);
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			
			/*д���µ��豸��Ϣ*/
			CH4_infoToFlash();
			/*����*/
			LCD_clear();
			
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
			OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
				
			/*�����¼�,��Key���̲�������return*/
			Send_key_return_2();
			
			/*����*/
			return;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_dispaly_BLLong(void)
{
	int  menu_index_MAX=100;
	int  index=CH4_info.BL_LONG/1000;
	char str[20];
	
	while(1)
	{
		CH4_info.BL_LONG=index*1000;
		
		sprintf(str,"0-99:%d",index);
		LCD_Printf((84-(6*5))/2,40,str);
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			
			/*д���µ��豸��Ϣ*/
			CH4_infoToFlash();
			/*����*/
			LCD_clear();
			
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
			OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
				
			/*�����¼�,��Key���̲�������return*/
			Send_key_return_2();
			
			/*����*/
			return;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_dispaly(void)
{
	OS_ERR err;

	
	int index=0,menu_index_MAX=MENU_SYSCONFIG_DISPALY_LONG;
	
	while(1)
	{
		
		switch (index)
		{
			case MENU_SYSCONFIG_DISPALY_BLLum:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"��������");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_dispaly_BLLum();
				}
				break;
			case MENU_SYSCONFIG_DISPALY_BLLong:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"����ʱ��");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_dispaly_BLLong();
				}
				break;
		}
		
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

void menu_sysconfig_alarm_ch4_sv(void)
{
	/*��ʼ���ַ���ָ���ڵ�һλ*/
	int StrP=0,StrP_MAX=3;
	char str[30];
	float val=CH4_info.Alarm_CH4;
	float dif;


	while(1)
	{

		sprintf(str,"0-9:%4.2f%%",val);
		//sprintf(str,"%4.2f%%",val);
		/*��ֹ��Ӱ*/
		LCD_clear_range((84-(9*6))/2-1,40-1,(9*6),9);
		
		if(StrP<1)
		{
			LCD_Printf_invert((84-(9*6))/2,40,str,StrP+5);
		}
		/*ʹ��ɫ������С����*/
		else
		{
			LCD_Printf_invert((84-(9*6))/2,40,str,StrP+6);
		}
		
		/*�ҵ�ȷ���������ƶ�һλ*/
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			StrP++;
			/*�������*/
			if(StrP>=StrP_MAX)
			{
				CH4_info.Alarm_CH4=val;
				/*д���µ��豸��Ϣ*/
				CH4_infoToFlash();
				
				LCD_clear();
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
				OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
				
				/*�����¼�,��Key���̲�������return*/
				Send_key_return_2();
				
				/*����*/
				LCD_clear();
				return;
			}
		}
		
		dif=0.01*pow(10,2-StrP);
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			if((val+dif)<10)
			{
					val=val+dif;
			}
			
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			if((val-dif)>0)
			{
					val=val-dif;
			}
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			StrP--;
			if(StrP<0)
			{
				/*����*/
				LCD_clear();
				
				/*����*/
				return;
			}
		}
		
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_alarm_temp_sv(void)
{
	int  menu_index_MAX=80;
	int  index=CH4_info.Alarm_TEMP;
	char str[20];
	
	while(1)
	{
		
		//sprintf(str,"0-80:%d",index);
		sprintf(str,"%d",index);
		LCD_Printf((84-(6*5))/2,40,str);
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			CH4_info.Alarm_TEMP=index;
			
			/*д���µ��豸��Ϣ*/
			CH4_infoToFlash();
			/*����*/
			LCD_clear();
			
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
			OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
				
			/*�����¼�,��Key���̲�������return*/
			Send_key_return_2();
			
			/*����*/
			return;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_alarm_duration(void)
{
	int  menu_index_MAX=10;
	int  index=CH4_info.Alarm_Long;
	char str[20];
	
	while(1)
	{
		
		sprintf(str,"0-9:%d",index);
		LCD_Printf((84-(6*5))/2,40,str);
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			CH4_info.Alarm_Long=index;
			/*д���µ��豸��Ϣ*/
			CH4_infoToFlash();
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_alarm(void)//�����޸Ĵ˴�
{
	OS_ERR err;

	
	int index=0,menu_index_MAX=MENU_SYSCONFIG_ALARM_LONG;
	
	while(1)
	{
		
		switch (index)
		{
			case MENU_SYSCONFIG_ALARM_SV_1:
				LCD_Printf_GB2312_12x12((84-(13*5))/2,16,"���鱨����");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_alarm_ch4_sv();
				}
				break;
			case MENU_SYSCONFIG_ALARM_SV_2:
				LCD_Printf_GB2312_12x12((84-(13*5))/2,16,"�¶ȱ�����");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_alarm_temp_sv();
				}
				break;
		}
		
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_rf(void)//�����޸Ĵ˴�
{
	OS_ERR err;

	
	int index=0,menu_index_MAX=MENU_SYSCONFIG_RF_LONG;
	
	while(1)
	{
		
		switch (index)
		{
			case MENU_SYSCONFIG_RF_DEVICE_ID:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�豸���");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_rf_SetID();
				}
				break;
			case MENU_SYSCONFIG_RF_VIEW_MAC:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"���ߵ�ַ");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_rf_ViewMAC();
				}
				break;
		}
		
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_storage(void)
{
	CPU_SR_ALLOC();
	
	
	int index=0,menu_index_MAX=MENU_SYSCONFIG_STORAGE_LONG;
	
	while(1)
	{
		
		switch (index)
		{
			case MENU_SYSCONFIG_STORAGE_VIEW_DATA:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�鿴����");//�����޸Ĵ˴�
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					menu_sysconfig_storage_ViewData();
				}
				break;
			case MENU_SYSCONFIG_STORAGE_CLEAR_DATA:
				LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�������");
				if(DEV_key.Fun.puch==1)
				{
					DEV_key.Fun.puch=0;
					
					LCD_clear();
					LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�����");
					OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
					
					OS_CRITICAL_ENTER();	//�����ٽ���	
					SPI_FLASH_SectorErase(FLASH_ADDR_DATA_NUMBER);
					SPI_FLASH_SectorErase(FLASH_ADDR_DATA);
					OS_CRITICAL_EXIT();	//�˳��ٽ���	
					
					/*�����¼�,��Key���̲�������return*/
					Send_key_return_2();
					
					
				}
				break;

		}
		
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_storage_ViewData(void)
{
	int  menu_index_MAX;
	int  index=0;
	char str[40];
	CPU_SR_ALLOC();
	
	/*����*/
	LCD_clear();
	
	menu_index_MAX=flash_get_DataNumber();
	while(1)
	{
		OS_CRITICAL_ENTER();	//�����ٽ���	
		SPI_FLASH_BufferRead(&FLASH_DATA_R.Time.Second,FLASH_ADDR_DATA+(index*FLASH_DATA_LONG),FLASH_DATA_LONG);
		OS_CRITICAL_EXIT();	//�˳��ٽ���	
		
		if(menu_index_MAX>0)
		{
			/*������ʾ����*/
			sprintf(str,"%04d-%02d-%02d",FLASH_DATA_R.Time.Year+2000,FLASH_DATA_R.Time.Month ,FLASH_DATA_R.Time.Day );
			LCD_Printf(0,8,str);
			
			/*������ʾʱ��*/
			sprintf(str,"%02d:%02d:%02d",FLASH_DATA_R.Time.Hour ,FLASH_DATA_R.Time.Minute ,FLASH_DATA_R.Time.Second );
			LCD_Printf(0,16,str);
			
			/*��ʾ����Ũ��ֵ*/
			sprintf(str,"CH4=%4.2f%% ",FLASH_DATA_R.MJC4);
			LCD_Printf(0,24,str);
			
			/*��ʾ�¶�ֵ*/
//			sprintf(str,"temp=%4.2f",);
//			LCD_Printf(10,32,str);
			
			sprintf(str,"Temp=%4.1f",FLASH_DATA_R.TEMP);
			LCD_Printf(0,32,str);
			LCD_PutImage(9*6,32,8,8,Celsius);
			
			/*��ʾλ��*/
			sprintf(str,"Addr=%06d",FLASH_DATA_R.ADDR);
			LCD_Printf(0,40,str);
		}
		else
		{
			/*�����Ļ*/
			LCD_clear();
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"������");
			OSTimeDlyHMSM(0,0,0,600,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			
			/*�����¼�,��Key���̲�������return*/
			Send_key_return_2();
		}
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*�˵�ָ���Լ�*/
			index++;
			if(index>=menu_index_MAX)index=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
			/*�˵�ָ���Լ�*/
			index--;
			if(index<0)index=menu_index_MAX-1;
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			
			/*����*/
			LCD_clear();
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}
void menu_sysconfig_rf_ViewMAC(void)
{
//	int  menu_index_MAX;
//	int  index=0;
	char str[40];
//	CPU_SR_ALLOC();
	
	/*����*/
	LCD_clear();
	
	while(1)
	{	
		sprintf(str,"MAC=");
		LCD_Printf(0,28,str);
		sprintf(str,"%02X %02X %02X %02X %02X",DEV_MAC[0],DEV_MAC[1],DEV_MAC[2],DEV_MAC[3],DEV_MAC[4]);
		LCD_Printf(0,36,str);
		
		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			
		}
		
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;

		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

void menu_sysconfig_rf_SetID(void)
{
	char str[40];
	
	/*��ʼ���ַ���ָ���ڵ�һλ*/
	uint16_t StrP=1;
	
	/*��ʼ����Ҫ�������ʾ����*/
	u32 index=CH4_info.DEV_ID;
	
	
	str_L[1]=(index/100000)%10;
	str_L[2]=(index/10000)%10;
	str_L[3]=(index/1000)%10;
	str_L[4]=(index/100)%10;
	str_L[5]=(index/10)%10;
	str_L[6]=(index/1)%10;

	/*����*/
	LCD_clear();
	
	LCD_Printf_GB2312_12x12((84-(13*6))/2,16,"������");

	while(1)
	{

		if(DEV_key.Higher.puch==1)
		{
			DEV_key.Higher.puch=0;
			
			/*��Ӧ��λ�Լ�*/
			str_L[StrP]++;
			
			/*��ֹ���*/
			if(str_L[StrP]>9)str_L[StrP]=0;
		}
		
		if(DEV_key.Low.puch==1)
		{
			DEV_key.Low.puch=0;
			/*��Ӧ��λ�Լ�*/
			str_L[StrP]--;
			
			/*��ֹ���*/
			if(str_L[StrP]<0)str_L[StrP]=9;
		}
		
		/*�ҵ�ȷ���������ƶ�һλ*/
		if(DEV_key.Fun.puch==1)
		{
			DEV_key.Fun.puch=0;
			StrP++;
		}
		
		if(DEV_key.Power.puch==1 || (KEY_POLLING_MS*MeunRetrun_count)>=BL_MENU_RETURN_MS)
		{
			DEV_key.Power.puch=0;
			
			/*����*/
			LCD_clear();
			
			/*����*/
			return;
			
		}
		
		/*�����������*/
		if(StrP>6)
		{
			/*����*/
			LCD_clear();
			
			CH4_info.DEV_ID=index;
			
			/*д���µ��豸��Ϣ*/
			CH4_infoToFlash();
			
			LCD_Printf_GB2312_12x12((84-(13*4))/2,16,"�ѱ���");
			OSTimeDlyHMSM(0,0,1,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
			LCD_clear();
				
			/*�����¼�,��Key���̲�������return*/
			Send_key_return_2();
			
			/*����*/
			return;
		}
		
		/*�������ֵ����������*/
		index=str_L[1]*100000+str_L[2]*10000+str_L[3]*1000+str_L[4]*100+str_L[5]*10+str_L[6];
		sprintf(str,"%06d",index);
		
		/*��ֹ��Ӱ*/
		LCD_clear_range((84-(9*6))/2-1,40-1,(9*6),9);
		LCD_Printf_invert((84-6*6)/2,40,str,StrP);
		

		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
	}
}

void Send_key_return_2(void)
{
	/*�����¼�,��Key���̲�������return*/
	OSQPost((OS_Q*		)&TaskQ_Return,		
	(void*		)(char)QRASK_KEY_SEND_RETURN,
	(OS_MSG_SIZE)1,
	(OS_OPT		)OS_OPT_POST_FIFO,
	(OS_ERR*	)&err);
	
	OSQPost((OS_Q*		)&TaskQ_Return,		
	(void*		)(char)QRASK_KEY_SEND_RETURN,
	(OS_MSG_SIZE)1,
	(OS_OPT		)OS_OPT_POST_FIFO,
	(OS_ERR*	)&err);
}

int flash_get_DataNumber(void)
{
	int i;
	
	SPI_FLASH_BufferRead(FLASH_READ,FLASH_ADDR_DATA_NUMBER,FLASH_ADDR_DATA_NUMBER_MAX);
	i=0;
	while(FLASH_READ[i]==0)
	{
		i++;
	}
	
	return i;
}
void flash_set_DataNumber(int number)
{
	int str[2];
	
	str[0]=0;
	SPI_FLASH_BufferWrite((uint8_t*)str,FLASH_ADDR_DATA_NUMBER+number,1);
}
//

