#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "24l01.h"
#include "pwm.h"
#include "timer.h"
#include "motor.h"
#include "capture.h"

u8 spd = 0;		//С���ٶȵ�λ��0~9
u8 auto_flag;
u8 avoid_status;
u16 distance;


int main(void)
{
    u8 tmp_rxbuf[3];

    SystemInit();
    delay_init();           //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart1_init(115200);     //����1��ӡ���
    LED_Init();             //��ʼ����LED���ӵ�Ӳ���ӿ�
    KEY_Init();             //��ʼ������
    MOTOR_Init();           //��ʼ��������ƽӿ�
    NRF24L01_Init();        //��ʼ��NRF24L01
    TIM2_PWM_Init(9, 7199); //��ʼ����ʱ��2��PWM���
	TIM4_Int_Init(9, 7199);	//��ʼ��ͨ�ö�ʱ��4��ÿ1ms�ж�1��
    CAPTURE_Init();         //��ʼ����ȡ������ʱ����ʱ��3

    while (NRF24L01_Check())
    {
        printf("NRFδ����\r\n");
        LED0 = ~LED0;
        delay_ms(100);
    }

    LED0 = 1;
    printf("NRF������\r\n");
    NRF24L01_RX_Mode();

    while (1)
    {
//������ʵʱ���
		distance = Hcsr04GetLength();//��λcm
		printf("dist = %dcm\r\n", distance);
//		delay_ms(100);

//���մ���
        if (NRF24L01_RxPacket(tmp_rxbuf) == 0)
        {
            printf("�������ݣ�");
            if (tmp_rxbuf[0] == '#')
            {
                switch (tmp_rxbuf[1])
                {
                case 'A'://UP
                    printf("ǰ��\r\n");
                    Go(spd);
                    break;
                case 'B'://DOWN
                    printf("����\r\n");
                    Back(spd);//����
                    break;
                case 'C'://LEFT
                    printf("��ת\r\n");
                    Turn_Left(spd);
                    break;
                case 'D'://RIGHT
                    printf("��ת\r\n");
                    Turn_Right(spd);
                    break;
                case 'E'://MID
                    printf("ֹͣ\r\n");
                    Stop();
                    break;
                case 'F'://SET
					printf("�Զ�\r\n");
					auto_flag = !auto_flag;
					if(auto_flag == 1)
					{
						LED0 = 0;
						delay_ms(100);
					}
					else
					{
						Stop();
						avoid_status = 0;
						LED0 = 1;
						delay_ms(100);
					}
                    break;
                case 'G'://RST
                    printf("����\r\n");
					POWER = ~POWER;
					delay_ms(100);
					if(POWER)
						Start();
					else
					{
						Stop();
						auto_flag = 0;
					}
                    break;
                case 0:
                    printf("Speed=0\r\n");
                    spd = 0;
                    break;
                case 1:
                    printf("Speed=1\r\n");
                    spd = 1;
                    break;
                case 2:
                    printf("Speed=2\r\n");
                    spd = 2;
                    break;
                case 3:
                    printf("Speed=3\r\n");
                    spd = 3;
                    break;
                case 4:
                    printf("Speed=4\r\n");
                    spd = 4;
                    break;
                case 5:
                    printf("Speed=5\r\n");
                    spd = 5;
                    break;
                case 6:
                    printf("Speed=6\r\n");
                    spd = 6;
                    break;
                case 7:
                    printf("Speed=7\r\n");
                    spd = 7;
                    break;
                case 8:
                    printf("Speed=8\r\n");
                    spd = 8;
                    break;
                case 9:
                    printf("Speed=9\r\n");
                    spd = 9;
                    break;

                default :
                    printf("Fault Data:%d\r\n", tmp_rxbuf[1]);
                }

                LED1 = 0;
                delay_ms(200);
                LED1 = 1;

                tmp_rxbuf[0] = tmp_rxbuf[1] = tmp_rxbuf[2] = 0;
            }
            else
                printf("#���ݴ���\r\n");
        }
    }
}



