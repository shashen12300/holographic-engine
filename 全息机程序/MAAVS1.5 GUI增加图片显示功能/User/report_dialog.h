#ifndef _REPORT_DIALOG_H_
#define _REPORT_DIALOG_H_

extern int reportType;
//报告内容
extern char *healthData[25];
//报告数据
extern double healthValue[25];

void report_dialogTask(void);

#endif