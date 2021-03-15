#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "24l01.h"
#include "beep.h"

int main(void)
{
    u8 tmp_txbuf[3];
    u8 key = '0';
    u8 flag = 0;
	u16 adc_value = 0;
	u8 speed_value_0 = 0, speed_value_1 = 0;
	
    SystemInit();
    delay_init();           //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);      //���ڳ�ʼ��1
    LED_Init();             //��ʼ����LED���ӵ�Ӳ���ӿ�
    KEY_Init();             //��ʼ������
	BEEP_Init();			//��ʼ��������
	Adc_Init();				//��ʼ��ADC
    NRF24L01_Init();        //��ʼ��NRF24L01
	BEEP_Power_ON();
	
    while (NRF24L01_Check())
    {
        printf("NRFδ����\r\n");
        LED0 = ~LED0;
        delay_ms(100);
    }
	
    LED0 = 1;
    printf("NRF������\r\n");
    NRF24L01_TX_Mode();
	
    while (1)
    {
//��ȡADC	
		adc_value = Get_Adc_Average(3, 10);
		speed_value_0 = adc_value/400;
		if(speed_value_1 != speed_value_0)
		{
			speed_value_1 = speed_value_0;
			key = speed_value_1;
			BEEP_Normal();
			printf("Speed = %d\r\n", key);
		}
		
//ɨ�谴��
        if (KEY_UP == 0)		//ǰ��
        {
            key = 'A';
            printf("A\r\n");
        }
        else if (KEY_DOWN == 0)	//����
        {
            key = 'B';
            printf("B\r\n");
        }
        else if (KEY_LEFT == 0)	//��ת
        {
            key = 'C';
            printf("C\r\n");
        }
        else if (KEY_RIGHT == 0)//��ת
        {
            key = 'D';
            printf("D\r\n");
        }
        else if (KEY_MID == 0)	//�м�
        {
            key = 'E';
            printf("E\r\n");
        }
        else if (KEY_SET == 0)	//SET��
        {
            key = 'F';
            printf("F\r\n");
        }
        else if (KEY_RST == 0) //RST��
        {
            key = 'G';
            printf("G\r\n");
        }

        if (key != '0')
        {
            tmp_txbuf[0] = '#';
            tmp_txbuf[1] = key;
            printf("%s", tmp_txbuf);
//����
            flag = NRF24L01_TxPacket(tmp_txbuf);
            if (flag == TX_OK)
            {
                LED1 = 0;
                delay_ms(200);
                LED1 = 1;
                printf("�ѷ���\r\n");
                key = '0';
            }
            else
            {
                printf("δ����\r\n");
                key = '0';
            }
        }
    }
}


