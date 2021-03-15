#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"

#define POWER 		PEout(10)	//�����Դ���ƣ�1-�պϣ�0-�Ͽ�
#define BK_LEFT  	PEout(12)	//��ɲ�������0-5v����ɲ������0-100%
#define BK_RIGHT 	PFout(0)	//��ɲ�������0-5v����ɲ������0-100%
#define FB_LEFT  	PEout(14)	//���ֻ���
#define FB_RIGHT 	PFout(2)	//���ֻ���


void MOTOR_Init(void);	//IO��ʼ��
void Start(void);	//����
void Stop(void);	//ֹͣ
void Go(u8 spd);	//ǰ��
void Back(u8 spd);	//����
void Turn_Left(u8 spd);	//��ת
void Turn_Right(u8 spd);	//��ת



#endif



