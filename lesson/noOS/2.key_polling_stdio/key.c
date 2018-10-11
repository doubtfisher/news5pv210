#include "stdio.h"

// ��������Ĵ����ĺ�
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)
#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

// ��ʼ������
void key_init(void)
{
	// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	rGPH0CON &= ~(0xFF<<8);
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xFFFF<<0);
}

void delay20ms(void)
{
	// ���������������ʱ20ms
	// ��Ϊ��������������������ص㲻�����Ҫ���������ǽ�ѧ
	// �����������������ֻ�������Եģ���û��ʵ��
	// ������з����Ǿ�Ҫ��ʱ����ĵ��Գ���ʱ20ms�ĳ���
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}


void key_polling(void)
{
	// ���Σ�����ȥ����ÿ��GPIO��ֵ���ж���ֵΪ1����0.���Ϊ1�򰴼����£�Ϊ0����
	
	// ��ѯ����˼���Ƿ���ѭ���ж����ް��������ܶ�ʱ��
	while (1)
	{
		// ��Ӧ�������ϱ���LEFT���Ǹ�����
		if (rGPH0DAT & (1<<2))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// ��������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH0DAT & (1<<2)))
			{
				// Ϊ0��˵���а���
				led1();
				printf("key left.\n");
			}
		}
		
		// ��Ӧ�������ϱ���DOWN���Ǹ�����
		if (rGPH0DAT & (1<<3))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// Ϊ0��˵���а���
			led2();
			printf("key down.\n");
		}
		
		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<0))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// Ϊ0��˵���а���
			led3();
		}
	}
}
























