#include "capture.h"
#include "delay.h"


//����������
u16 msHcCount = 0;

//��ʼ��
void CAPTURE_Init(void)
{
    GPIO_InitTypeDef GPIO_IniStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_IniStructure.GPIO_Pin = GPIO_Pin_0;//PB0(ECHO)�����ź������
    GPIO_IniStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_IniStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);

    GPIO_IniStructure.GPIO_Pin = GPIO_Pin_1;//PB1(Trig)���봥���źŽţ�������10us���ϸߵ�ƽ
    GPIO_IniStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_IniStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_IniStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);


    TIM_TimeBaseInitStructure.TIM_Period = 999;//�Զ���װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//Ԥ��Ƶֵ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);//���жϣ������жϴ�������

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, DISABLE);
}

//�򿪶�ʱ��3
static void OpenTimerForHc()
{
    TIM_SetCounter(TIM3, 0);
    msHcCount = 0;
    TIM_Cmd(TIM3, ENABLE);
}

//�رն�ʱ��3
static void CloseTimerForHc()
{
    TIM_Cmd(TIM3, DISABLE);
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        msHcCount++;
    }
}

//��ȡ��ʱ��3������ֵ
u32 GetEchoTimer(void)
{
    u32 t = 0;

    t = msHcCount * 1000;
    t += TIM_GetCounter(TIM3);
    TIM3->CNT = 0;
    delay_ms(50);

    return t;
}

//ͨ����ʱ��3������ֵ�������
float Hcsr04GetLength(void)
{
    u32 t = 0;
    int i = 0;
    float lengthTemp = 0;
    float sum = 0;

    while (i != 5)
    {
        TRIG_OUT = 1;
        delay_us(20);
        TRIG_OUT = 0;
		
        while (ECHO_IN == 0);
        OpenTimerForHc();
        i = i + 1;
        while (ECHO_IN == 1);
        CloseTimerForHc();
        t = GetEchoTimer();
        lengthTemp = ((float)t / 58.0); //cm
        sum = lengthTemp + sum ;
    }
    lengthTemp = sum / 5.0;

    return lengthTemp;
}



