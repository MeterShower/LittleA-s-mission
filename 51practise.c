#include<reg52.h>
#define LED P2
#define NumberLED P0
#define GPIO_KEY P1 
void DisPlayLSA(void);
typedef unsigned int u16;
typedef unsigned char u8;
void delay(u16 m);
void LakeLED(void);
void Keyboard(void);
void KeyBoard2(void);
void Timer0Init(void);
void exter0Init(void);
void exter1Init(void);
void Timer1Init(void);

u8 KeyValue;
	
	sbit beep=P1^5;
	sbit D1=P2^0;
	sbit D2=P2^1;
	sbit D3=P2^2;
	sbit D4=P2^3;
	sbit k1=P3^1;
	sbit k2=P3^0;
	sbit k3=P3^2;
	sbit k4=P3^3;
	sbit LSA=P2^2;
	sbit LSB=P2^3;
	sbit LSC=P2^4;
	char code LSAchar[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
		0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};	// 0-F共阴数码管码表

int main(void)
{
	Timer0Init();
	exter0Init();
	exter1Init(); 
//	Timer1Init();
	
	while(1);

   return 0;

}


void delay(u16 m)
{
	while(m>0){
		m--;
	}


}
void DisPlayLSA(void)//动态数码管显示
{
	int i;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0):
				LSC=0;LSB=0;LSA=0;P0=LSAchar[8];break;
			case(1):
				LSC=0;LSB=0;LSA=1;P0=LSAchar[1];break;
			case(2):
				LSC=0;LSB=1;LSA=0;P0=LSAchar[2];break;
			case(3):
				LSC=0;LSB=1;LSA=1;P0=LSAchar[0];break;
			case(4):
				LSC=1;LSB=0;LSA=0;P0=LSAchar[0];break;
			case(5):
				LSC=1;LSB=0;LSA=1;P0=LSAchar[2];break;
			case(6):
				LSC=1;LSB=1;LSA=0;P0=LSAchar[0];break;
			case(7):
				LSC=1;LSB=1;LSA=1;P0=LSAchar[2];break;
		
		
		}
		delay(100);
		NumberLED=LSAchar[16];
	
	}
}
void LakeLED(void)//流水灯显示
{
	while(1)
	{
		int k;
		LED=0x01;
		for(k=0;k<8;k++)
		{
			LED=~LED;
			delay(30000);
			LED=~LED<<1;
		}
	
	
	}




}

void Keyboard(void)//独立键盘控制
{
	if(k1==0){
	  	delay(1000);
		while(!k1){
			DisPlayLSA();
		}  
	}
	else if(k2==0){
		delay(1000);
		while(!k2){
			beep=~beep;
			delay(100);
		}

	  while(!k2);
	}
	else if(k3==0){
		delay(1000);
		if(k3==0){
			D3=~D3;
		}

	 	while(!k3);
	}
	else if(k4==0){
		delay(1000);
		if(k4==0){
			D4=~D4;
		}
	  	while(!k4);
	}

}

void KeyBoard2(void){//矩阵键盘行列控制
	u8 a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f){
		delay(1000);
		if(GPIO_KEY!=0x0f){
			switch(GPIO_KEY){
				case(0x07):KeyValue=1;break;
				case(0x0b):KeyValue=2;break;
				case(0x0d):KeyValue=3;break;
				case(0x0e):KeyValue=4;break;	

			}
			GPIO_KEY=0xf0;
			switch(GPIO_KEY){
				case(0x70):KeyValue+=0;break;
				case(0xb0):KeyValue+=4;break;
				case(0xd0):KeyValue+=8;break;
				case(0xe0):KeyValue+=12;break;	

			}
			while(a<50&&(GPIO_KEY!=0xf0)){
				delay(1000);
				a++;
			
			}	
		
		}
	
	}	




}
void Timer0Init(){
	TMOD=0x01;
	TH0=0xFC;
	TL0=0x18;
	EA=1; //打开总中断
	ET0=1;
	TR0=1;


}

void exter0Init(){
	 EA=1;
	 EX0=1;
	 IT0=0;
	 INT0=1;



}
void exter1Init(){
	EA=1;
	EX1=1;
	IT1=0;
	INT1=1;


}
void exter0()interrupt 0
{
 	   DisPlayLSA();

}
void Timer0() interrupt 1
{
	static u16 i;
	TH0=0xFC;	 //每次溢出后在中断装载初值
	TL0=0x18;
	i++;  //累计溢出次数，达1000次即1ms*1000=1s
	if(i==1000){
		i=0;
		D1=~D1;
	}


}
void Timer1()interrupt 3
{
	static u16 k;
	TH1=0xfe;
	TL1=0x0d;
	k++;
	if(k==1000){
		k=0;
		D4=~D4;	
	}

}

void exter1()interrupt 2
{ 
 	  D2=0; 

}
void Timer1Init()
{
	  EA=1;
	  TMOD=0x10;
	  ET1=1;
	  TR1=1;
	  TH1=0xfe;
	  TL1=0x0d;



}
