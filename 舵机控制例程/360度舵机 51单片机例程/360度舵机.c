/*********************************************************************************************
*  程序功能：基于51单片机的舵机控制参考程序
*  主要硬件：STC89C52RC单片机最小系统+360度舵机
*  店铺名称：欣薇电子
*  店铺网址：https://xwdzqyd.taobao.com/      
*  编辑日期：2022-7-11
**********************************************************************************************/
	
#include "reg52.h"			//	   头文件

sbit Sevro_moto_pwm=P2^0;	   	// 舵机信号线（橙色）

unsigned char pwm_val  = 0;//变量定义
unsigned char push_val = 14;//舵机归中，产生约，1.5MS 信号
				

void delay1ms(unsigned int k)   //延时1ms函数，k等于多少就延时多少ms
{
    unsigned int a,b,c,d;
	for(d=0;d<k;d++)
        for(c=1;c>0;c--)
            for(b=50;b>0;b--)
                for(a=2;a>0;a--);
}								   


/**********************************************************************************************
**                              TIMER1中断服务子函数产生PWM信号
**********************************************************************************************/

 	void time1()interrupt 3   using 2
{	
     TH1=(65536-100)/256;	  //100US定时
	 TL1=(65536-100)%256;
	 pwm_val++;
	 if(pwm_val<=push_val)	  
	       Sevro_moto_pwm=1;   //PWM信号高电平时间
	else 
	       Sevro_moto_pwm=0;   //PWM信号高电平时间
	if(pwm_val>=100)
	pwm_val=0;
 }



/**********************************************************************************************
**                                       主函数
**********************************************************************************************/
void main(void)
{
	TMOD=0X10;
	TH1=(65536-100)/256;	  //100US定时
	TL1=(65536-100)%256;
	TR1= 1;
	ET1= 1;
	EA = 1;

	while(1)		       /*无限循环*/
	{ 
		  push_val=9;	  //舵机慢速正转
		  delay1ms(2000); //延时2秒
		  push_val=13;	  //舵机停止
		  delay1ms(500);  //延时500MS

		  push_val=4;	  //舵机快速正转
		  delay1ms(2000); //延时2秒
		  push_val=13;	  //舵机停止
		  delay1ms(500);  //延时500MS

		  push_val=17;	  //舵机慢速反转
		  delay1ms(2000); //延时2秒
		  push_val=13;	  //舵机停止
		  delay1ms(500);  //延时500MS

		  push_val=22;	  //舵机快速反转
		  delay1ms(2000); //延时2秒
		  push_val=13;	  //舵机停止
		  delay1ms(500);  //延时500MS


	   }

	}   
/**********************************************************************************************
**                                        END FILE
**********************************************************************************************/
	