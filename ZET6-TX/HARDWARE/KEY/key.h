#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"  	 


#define KEY_UP  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)	//UP:ǰ��
#define KEY_DOWN  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)	//DOWN:����
#define KEY_LEFT  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)	//LEFT:��ת
#define KEY_RIGHT  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)	//RIGHT����ת
#define KEY_MID  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)//MID
#define KEY_SET  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//SET
#define KEY_RST  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//RST

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����
#define KEY3_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
//u8 KEY_Scan(u8);  	//����ɨ�躯��


#endif
