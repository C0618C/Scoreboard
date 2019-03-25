#include <reg51.h>
//数码管定义 从左往右4321
sbit P24 = P2 ^ 4; //数码管第1位
sbit P25 = P2 ^ 5; //数码管第2位
sbit P26 = P2 ^ 6; //数码管第3位
sbit P27 = P2 ^ 7; //数码管第4位
#define LED1 P24
#define LED2 P25
#define LED3 P26
#define LED4 P27

sbit beep = P2 ^ 3; //蜂鸣器

//按钮定义
sbit KEY_k1 = P3 ^ 2;
sbit KEY_k2 = P3 ^ 3;
sbit KEY_k3 = P3 ^ 4;
sbit KEY_k4 = P3 ^ 5;

//按钮的状态：抬起、按下、按下中、按下并已处理
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_PRESS 2
#define KEY_PRESS_HANDLE 3
//按键自动触发延时
#define KEY_AUTOHIT_DELAY 30

unsigned int k1 = KEY_UP;
unsigned int k2 = KEY_UP;
unsigned int k3 = KEY_UP;
unsigned int k4 = KEY_UP;
int key_delay_k1 = 0;
int key_delay_k2 = 0;
int key_delay_k3 = 0;
int key_delay_k4 = 0;

#define SCANKEY(k)                               \
	if (k == KEY_PRESS_HANDLE || k == KEY_PRESS) \
	{                                            \
		key_delay_##k--;                         \
		if (key_delay_##k <= 0)                  \
		{                                        \
			k = KEY_PRESS;                       \
			key_delay_##k = KEY_AUTOHIT_DELAY;   \
		}                                        \
		if (KEY_##k)                             \
			k = KEY_UP;                          \
	}                                            \
	else if (k == KEY_UP && !KEY_##k)            \
		k = KEY_DOWN;

#define SCANKEY_CHECK(k)                   \
	if (k == KEY_DOWN && !KEY_##k)         \
	{                                      \
		k = KEY_PRESS;                     \
		key_delay_##k = KEY_AUTOHIT_DELAY; \
	}
//unsigned int i = 0;

//比分记录
unsigned int ScoreRed;  //红方分数
unsigned int ScoreBlue; //蓝方分数

//赛场设定
//

// unsigned int js;
// unsigned int ds; //倒计时初始时间
// unsigned char jsflag;
// static unsigned int i;
unsigned char code LEDDis[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF, 0xBF, 0x7F};

//延时1ms
void Delay(unsigned int ii)
{
	unsigned int jj;
	for (; ii > 0; ii--)
		for (jj = 0; jj < 125; jj++)
			;
}
void Delay500(unsigned int iii)
{
	unsigned int jjj;
	for (; iii > 0; iii--)
		for (jjj = 0; jjj < 60; jjj++)
			;
}

/** 
 * 渲染数码管
*/
void RenderLED()
{
	P0 = LEDDis[ScoreRed / 10];
	LED4 = 0;
	Delay500(5);
	LED4 = 1;
	P0 = LEDDis[ScoreRed % 10];
	LED3 = 0;
	Delay500(5);
	LED3 = 1;

	P0 = LEDDis[ScoreBlue / 10];
	LED2 = 0;
	Delay500(5);
	LED2 = 1;
	P0 = LEDDis[ScoreBlue % 10];
	LED1 = 0;
	Delay500(5);
	LED1 = 1;

	//测试用——用红点显示是否按下按键
	P0 = LEDDis[12];
	if (k1)
	{
		LED4 = 0;
		Delay500(4);
		LED4 = 1;
	}
	if (k2)
	{
		LED3 = 0;
		Delay500(4);
		LED3 = 1;
	}
	if (k3)
	{
		LED2 = 0;
		Delay500(4);
		LED2 = 1;
	}
	if (k4)
	{
		LED1 = 0;
		Delay500(4);
		LED1 = 1;
	}
}

/**
 * 扫描键盘
*/
void ScanKey()
{
	// if (KEY_1 && KEY_2 && KEY_3 && KEY_4)
	// return 0;

	// k1 = !KEY_1;
	// k2 = !KEY_2;
	// k3 = !KEY_3;
	// k4 = !KEY_4;

	// Delay(10); //抖动检测

	// k1 &= !KEY_1;
	// k2 &= !KEY_2;
	// k3 &= !KEY_3;
	// k4 &= !KEY_4;

	SCANKEY(k1);
	SCANKEY(k2);
	SCANKEY(k3);
	SCANKEY(k4);
	Delay(10); //抖动检测
	SCANKEY_CHECK(k1);
	SCANKEY_CHECK(k2);
	SCANKEY_CHECK(k3);
	SCANKEY_CHECK(k4);
}

void HandleKey()
{
	if (k1 == KEY_PRESS)
	{
		ScoreRed++;
		k1 = KEY_PRESS_HANDLE;
	}
	if (k4 == KEY_PRESS)
	{
		ScoreBlue++;
		k4 = KEY_PRESS_HANDLE;
	}
}

void main()
{
	//单片机状态设置
	EA = 1;		//允许CPU中断
	ET0 = 1;	//定时器0中断打开
	TMOD = 0x1; //设定时器0为模式1，16位模式
	TH0 = 0xB1;
	TL0 = 0xDF; //设定时值为20000us（20ms）
	TR0 = 1;
	// ds = 999;
	// KeyV = 0;
	// TempKeyV = 0;
	// jsflag = 0;

	//初始化状态变量
	ScoreRed = 0;
	ScoreBlue = 0;

	while (1)
		;
}

//定时器0中断外理中键扫描和显示
void KeyAndDis_Time0(void) interrupt 1 using 2
{
	TH0 = 0xB1;
	TL0 = 0xDF; //设定时值为20000us（20ms)

	ScanKey();

	HandleKey();

	RenderLED();
}