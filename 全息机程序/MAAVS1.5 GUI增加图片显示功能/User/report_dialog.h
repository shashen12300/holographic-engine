#ifndef _REPORT_DIALOG_H_
#define _REPORT_DIALOG_H_

extern int reportType;
//��������
extern char *healthData[25];
//��������
extern double healthValue[25];
//��ʼ����������
void healthInitData(int reportType);

void report_dialogTask(void);

#endif