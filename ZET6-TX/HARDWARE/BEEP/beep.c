#include "beep.h"
#include "delay.h"

//��ʼ��PE2Ϊ�����.��ʹ������ڵ�ʱ��
//��������ʼ��
void BEEP_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);   //ʹ��GPIOE�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               //BEEP-->PE2 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�Ϊ50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);  //���ݲ�����ʼ��GPIOE2

    GPIO_SetBits(GPIOE, GPIO_Pin_2); //���1���رշ��������
}


void BEEP_Power_ON(void)
{
    u16 i;
    for (i = 0; i < 400; i++)
    {
        BEEP = 0;
        delay_us(500);
        BEEP = 1;
        delay_us(500);
    }
}

void BEEP_Normal(void)
{
    u16 i;
    for (i = 0; i < 100; i++)
    {
        BEEP = 0;
        delay_us(400);
        BEEP = 1;
        delay_us(400);
    }
}
