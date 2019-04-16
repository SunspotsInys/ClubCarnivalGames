#include<reg51.h>

#define uint unsigned int
#define uchar unsigned char

sbit k2 = P3^4;
sbit k3 = P3^5;
sbit k4 = P3^6;
sbit k5 = P3^7;

sbit wei1 = P2^4;//定义第一位数码管
sbit wei2 = P2^5;//定义第二位数码管
sbit wei3 = P2^6;//定义第三位数码管
sbit wei4 = P2^7;//定义第四位数码管

sbit dian=P0^7;

void delay(uint x) {
	uint i,j;
	for(i=x;i>0;i--)
		for(j=112;j>0;j--);
}

int tt=0;
uchar a=0,b=0,c=0,d=0;
uchar code num[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void start_timer() {
   	ET0=1;
	EA=1;
	TR0=1;
}

void stop_timer() {
   	ET0=0;
	EA=0;
	TR0=0;
}
void main() {
    TMOD = 0x01;
    TL0 = (65536-10000)%256;
    TH0 = (65536-10000)/256;
	
	start_timer();
    while (1) {
		if(!k2 || !k3 || !k4 || !k5) {
			delay(10);
			if(!k2 || !k3 || !k4 || !k5) {
				while(!k2 || !k3 || !k4 || !k5);
				/** TODO 固定数码管显示数字 */
				stop_timer();
			}
		}

		if(a==10) {
			b++;
			a=0;
		}
		if(b==10) {
			c++;
			b=0;
		}		
		if(c==10) {
			d++;
			c=0;
		}
		if(d==10) {
			d=0;
		}

		wei1=0;wei2=0;wei3=0;wei4=1;P0=num[a];delay(1);P0=0x00;
		wei1=0;wei2=0;wei3=1;wei4=0;P0=num[b];delay(1);P0=0x00; 
		wei1=0;wei2=1;wei3=0;wei4=0;P0=num[c];dian=1;delay(1);P0=0x00;
		wei1=1;wei2=0;wei3=0;wei4=0;P0=num[d];delay(1);P0=0x00;
	}
}
void timer0() interrupt 1 {
	TL0 = (65536-10000)%256;
    TH0 = (65536-10000)/256;
	a++; 
}