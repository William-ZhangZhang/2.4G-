#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 



#define KEY_FW  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//ǰ
#define KEY_TL  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��
#define KEY_TR  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��
#define KEY_BW  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//��
#define KEY_WH  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��
#define KEY_ST  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��
#define KEY_SP  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//ͣ

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����
#define KEY3_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
//u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
