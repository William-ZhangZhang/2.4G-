#include "timer.h"
#include "motor.h"

#define SafeDistance  50	//��С��ȫ���룬Ĭ��50cm
u16 dist_l, dist_f, dist_r;

//ͨ�ö�ʱ��4�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��4!
void TIM4_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

    //��ʱ��TIM4��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //ʹ��ָ����TIM4�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�4��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

    TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx
}



u16 ms_timer;
u16 get_dist_timer, TL_timer, TR_timer, BK_timer;

//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{	
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
    {
		if(auto_flag == 1)
		{
			if(ms_timer++ >= 100)
			{
				ms_timer = 0;
				switch(avoid_status)
				{
					case 0:
						dist_f = distance;
						if(dist_f >= SafeDistance)
							Go(spd);
						else
						{
							Stop();
							avoid_status = 1;
						}
						break;
					case 1:
						Turn_Left(1);
						if(TL_timer++ >= 3)
						{
							TL_timer = 0;
							Stop();
							dist_l = distance;
							if(dist_l > SafeDistance)
								avoid_status = 0;
							else
								avoid_status = 2;
						}
						break;
					case 2:
						Turn_Right(1);
						if(TR_timer++ >= 5)
						{
							TR_timer = 0;
							Stop();
							dist_r = distance;
							if(dist_r > SafeDistance)
								avoid_status = 0;
							else
								avoid_status = 3;
						}
						break;
					case 3:
						if(dist_r < SafeDistance && dist_l < SafeDistance)
						{
							Back(spd);
							if(BK_timer++ >= 3)
							{
								Stop();
								avoid_status = 0;
							}
						}
						break;
				}
			}
		}
		
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);    //���TIMx�����жϱ�־
    }
}












