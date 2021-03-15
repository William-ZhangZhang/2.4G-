#include "motor.h"

//IO��ʼ��
void MOTOR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //ʹ�ܶ˿ڸ���ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //ʧ��JTAG

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF, ENABLE); //ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14;//PE �˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        		//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       		//IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE, GPIO_Pin_10); //�����
	GPIO_SetBits(GPIOE, GPIO_Pin_12 | GPIO_Pin_14); 	//�����
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;	//PF �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure);                  //�����趨������ʼ��GPIO
    GPIO_SetBits(GPIOF, GPIO_Pin_0 | GPIO_Pin_2);         	//�����

}


void Start(void)
{
    TIM_SetCompare3(TIM2, 0);
    TIM_SetCompare4(TIM2, 0);
    BK_LEFT = 0;
	BK_RIGHT = 0;
}
void Stop(void)
{
//  TIM_SetCompare3(TIM2,0);
//  TIM_SetCompare4(TIM2,0);
    BK_LEFT = 1;
	BK_RIGHT = 1;
}
void Go(u8 spd)
{
    TIM_SetCompare3(TIM2, spd);
    TIM_SetCompare4(TIM2, spd);
	BK_LEFT = 0;
	BK_RIGHT = 0;
    FB_LEFT = 1;
    FB_RIGHT = 0;
}
void Back(u8 spd)
{
    TIM_SetCompare3(TIM2, spd);
    TIM_SetCompare4(TIM2, spd);
	BK_LEFT = 0;
	BK_RIGHT = 0;
    FB_LEFT = 0;
    FB_RIGHT = 1;
}
void Turn_Left(u8 spd)
{
    TIM_SetCompare3(TIM2, spd);
    TIM_SetCompare4(TIM2, spd);
	BK_LEFT = 0;
	BK_RIGHT = 0;
    FB_LEFT = 0;
    FB_RIGHT = 0;
}
void Turn_Right(u8 spd)
{
    TIM_SetCompare3(TIM2, spd);
    TIM_SetCompare4(TIM2, spd);
	BK_LEFT = 0;
	BK_RIGHT = 0;
    FB_LEFT = 1;
    FB_RIGHT = 1;
}

