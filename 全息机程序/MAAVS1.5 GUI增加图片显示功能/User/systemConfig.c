#include "systemConfig.h"
#include "GUI.h"
//������
WM_HWIN root_hWin;
//logoͼ��
WM_HWIN mainForm_hWin;
//��Ϣ�趨
WM_HWIN dialog_hWin;
//ʱ��
WM_HWIN time_hWin;
//�������
WM_HWIN draw_hWin;
WM_HWIN drawLine_hWin;
//ϵͳ�˵�
WM_HWIN menu_hWin;
//ϵͳ˵��
WM_HWIN explain_hWin;
//ʱ���趨
WM_HWIN clock_hWin;
//���浯��
WM_HWIN warning_hWin;
//�����б�
WM_HWIN report_hWin;
//���������
 int myMessageType = MY_MESSAGE_ID_LOGO;
//�Ƿ����ø�����Ϣ
int isOrSetMessage=0;
//�Ƿ�ˢ�¸�����Ϣ
int isOrRefreshMessage=0;
//��ת��������־λ
int rotate_flag=0;
//��ת�������Ƿ��±�־λ
int rotateEnter_flag=0;
//�����û���Ϣ
 char *saveData[5] = {"��","35","δ��","����","03"};
//�Ƿ�չʾϵͳ˵��
 int isOrShowExplain = 0;
 //�Ƿ�չʾʱ���趨����
 int isOrShowSetTime = 0;
 //����ʱ��
 char *timeData[6] = {"2017","01","01","08","30","00"};
 //�Ƿ�����ʱ��
 int isOrSetClock = 0;
 //�Ƿ�����
 int isOneCheck = 0;
 //�Ƿ����¼��
 int isRestartCheck = 1;
 //�Ƿ�ʼ���
 int isBeginCheck = 0;
 //�Ƿ񻭵�
 int isOrSetPoint = 0;
 //�Ƿ�չʾ����
 int isOrShowReport = 0;

