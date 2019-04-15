#include <reg52.h>

sbit k1 = P3^4;
sbit w1 = P2^4;
sbit w2 = P2^5;
sbit w3 = P2^6;
sbit w4 = P2^7;
sbit fm = P2^3;

void delay(int a) {
	int i, j;
	for (i = 0; i < a; ++i)
		for (j = 0; j < 112; ++j) ;
}

void main() {
	int j, cnt = 0;
	int a[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	int b[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xf , 0xf0};
	w1 = w2 = w3 = 0;
	w4 = 1;
	while (1) {
		unsigned int t = 0x0;
		for (j = 0; j < 10; ++j) {
			P1 = b[j];
			P0 = a[j%10];
			delay(50);
			if (!k1) {
				delay(10);
				if (!k1) {
					while (!k1);
					if (!j || 60%j) {
		 				fm = 1;
						delay(100);
						fm = 0;
					} else {
						w2 = w3 = w4 = 1;
						w1 = 0;
						P0 = a[6];
					}
					delay(1000000);
				}
			}
		}
	}
}
