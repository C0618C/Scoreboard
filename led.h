#ifndef __LED__h_
#define __LED__h_
/**
 * 8位数码管的相关定义
*/
//数码管定义 从左往右4321
sbit P24 = P2 ^ 4; //数码管第1位
sbit P25 = P2 ^ 5; //数码管第2位
sbit P26 = P2 ^ 6; //数码管第3位
sbit P27 = P2 ^ 7; //数码管第4位
#define LED1 P24
#define LED2 P25
#define LED3 P26
#define LED4 P27
/** 
 * LED显示字典	—— 高电平不显示
	//0、1、2、3、4、5、6、7、8、9
	//A b C d E F
	//不显示、-、.
*/
unsigned char code LEDDis[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
0x88,0x83,0xC6,0xA1,0x86,0x8E
, 0xFF, 0xBF, 0x7F};


#endif