#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//�������˿ڶ���
#define BEEP PEout(2)	// BEEP,�������ӿ�		   

void BEEP_Init(void);	//��ʼ��
void BEEP_Power_ON(void);	//������ʾ��
void BEEP_Normal(void);	//�ٶȸı���ʾ��
		 				    
#endif

