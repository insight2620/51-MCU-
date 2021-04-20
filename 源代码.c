/**
@author curiosity2620
@date 2019 / 3 / 12 - 20:43
*/
#include <reg52.h>
#define uint unsigned int   
unsigned char data;
sbit M=P3^5;//�����ŽӶ���ź���
sbit N=P2^0;//������ŽӶ���ź���
sbit led=P3^6;
void delayms(uint);//��ʱ����

void UsartInit()//���ڳ�ʼ��
{
  TMOD=0X20;//������ʽ���ƼĴ���
  TH1=0xF4;//Timer�Ĵ����ĸ߰�λ
  TL1=0xF4;//�Ͱ�λ
  PCON=0x80;//PCON ��Դ����Ĵ���
  TR1=1;//T1����������λ
  SCON=0x50;//���пڿ��ƼĴ���
  ES=1;//�����жϿ���
  EA=1;//�ж��ܿ���
}

void main()
{
  UsartInit();//���ô��ڳ�ʼ��
  while(1);//�ȴ������ж�
}

void Usart() interrupt 4 //�жϴ��������жϺ�Ϊ4
{  
   data=SBUF;//���ͽ������ݻ���ռ�
   RI=0;//�����жϱ�־λ
   SBUF=data;//ԭ�����ؽ��յ���
   while(!TI);//�������������������������
   TI=0;//�����жϱ�־λ
   
   if(data=='D')//(door)������յ�����D���ö��ת��
  { 
            int b=0;//���ڿ��Ʋ�����pwm�źŶγ��ȣ�ÿ����ͬ��pwm�ζ�Ӧһ������Ƕȣ���˿����˶����ĳ�Ƕ�ͣ����ʱ��
            while(b<30)//����pwm�źţ����ƶ��ת������ʼ�Ƕ�
            {
				 M=1,N=1;
	             delayms(1);
	             M=0,N=0;
	             delayms(19);
	             b++;
            }
			 	 b=0;
            while(b<200)//����pwm�źţ����ƶ��ת�����м�ǶȲ�����2s
            {
				 M=1,N=1;
	             delayms(2);
	             M=0,N=0;
	             delayms(18);
	             b++;
            }
				 b=0;
			 while(b<30)//����pwm�źţ����ƶ���ص���ʼλ��
            {
				 M=1,N=1;
	             delayms(1);
	             M=0,N=0;
	             delayms(19);
	             b++;
            }
   }
  	
   if(data=='L')//(led)������յ�������L����LED��ת
   {
     led=~led;
   }
}  

void delayms(uint xms)//��ʱ����������ΪX����
{
uint i,j;
for(i=xms;i>0;i--)
   for(j=110;j>0;j--);

}
