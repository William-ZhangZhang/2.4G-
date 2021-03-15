#include "MP3.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

unsigned char Play_1st[11]={0x7E,0x05,0x41,0x00,0x01,0x45,0xEF};	//��һ�׸�
unsigned char Play_2st[11]={0x7E,0x05,0x41,0x00,0x02,0x46,0xEF};	//�ڶ��׸�
unsigned char Play_3st[11]={0x7E,0x05,0x41,0x00,0x03,0x47,0xEF};	//�����׸�
unsigned char Play_4st[11]={0x7E,0x05,0x41,0x00,0x04,0x40,0xEF};	//�����׸�
unsigned char Play_5st[11]={0x7E,0x05,0x41,0x00,0x05,0x41,0xEF};	//�����׸�
unsigned char Play_6st[11]={0x7E,0x05,0x41,0x00,0x06,0x42,0xEF};	//�����׸�
unsigned char Play_7st[11]={0x7E,0x05,0x41,0x00,0x07,0x43,0xEF};	//�����׸�


unsigned char Sound_15[11]={0x7E,0x04,0x31,0x15,0x3A,0xEF};	//����15

unsigned char Stop_Play[11]={0x7E,0x03,0x0E,0x0D,0xEF};	//ֹͣ����
unsigned char i = 0; 



void MP3_Sound_5(void)
{
	for (i=0; i<6; i++)
	{
		USART_SendData(USART2,Sound_15[i]);	
		delay_us(1000);	
	}
}



void MP3_1st(void)
{
  printf("��һ��\r\n");
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_1st[i]);	
		delay_us(1000);	
	}	
}

void MP3_2st(void)
{
  printf("�ڶ���\r\n");	
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_2st[i]);	
		delay_us(1000);	
	}	
}

void MP3_3st(void)
{
  printf("������\r\n");	
	for (i=0; i<7; i++)
	{	
		USART_SendData(USART2,Play_3st[i]);	
		delay_us(1000);	
	}	
}

void MP3_4st(void)
{
  printf("������\r\n");
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_4st[i]);	
		delay_us(1000);	
		
	}	
}

void MP3_5st(void)
{
  printf("������\r\n");
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_5st[i]);	
		delay_us(1000);			
	}	
}

void MP3_6st(void)
{
  printf("������\r\n");
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_6st[i]);	
		delay_us(1000);	
	}	
}

void MP3_7st(void)
{
	printf("������\r\n");
	for (i=0; i<7; i++)
	{
		USART_SendData(USART2,Play_7st[i]);	
		delay_us(1000);	
	}	
}

