#include <reg51.h>
#include "led.h"
#include "key.h"
#include "game.h"
#include "pingpong.h"

sbit Player_01 = P1 ^ 1;
sbit Player_02 = P1 ^ 2;

sbit beep = P2 ^ 3; //蜂鸣器

/**
 * 赛场状态
*/

struct Game curGame;

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
	P0 = LEDDis[curGame.gameStatus.Player1Score / 10];
	LED4 = 0;
	Delay500(5);
	LED4 = 1;
	P0 = LEDDis[curGame.gameStatus.Player1Score % 10];
	LED3 = 0;
	Delay500(5);
	LED3 = 1;

	P0 = LEDDis[curGame.gameStatus.Player2Score / 10];
	LED2 = 0;
	Delay500(5);
	LED2 = 1;
	P0 = LEDDis[curGame.gameStatus.Player2Score % 10];
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

//处理按键逻辑
void HandleKey()
{
	if (k1 == KEY_PRESS)
	{
		curGame.Player1GetScore(&curGame.gameStatus, 1);
		k1 = KEY_PRESS_HANDLE;
	}
	if (k4 == KEY_PRESS)
	{
		curGame.Player2GetScore(&curGame.gameStatus, 1);
		k4 = KEY_PRESS_HANDLE;
	}
}

//当前比赛状态检查
void GameStatusCheck()
{
	unsigned int winner = 0;

	if (IsWin(&curGame,&winner))
	{
		Player_01 = winner;
		Player_02 = !winner;
	}
}

/**
 * 单片机相关的设置
*/
void main()
{
	//单片机状态设置
	EA = 1;		//允许CPU中断
	ET0 = 1;	//定时器0中断打开
	TMOD = 0x1; //设定时器0为模式1，16位模式
	TH0 = 0xB1;
	TL0 = 0xDF; //设定时值为20000us（20ms）
	TR0 = 1;

	//初始化状态变量
	PingPongFactory(&curGame);

	curGame.GameStart(&curGame);

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
	GameStatusCheck();
	RenderLED();
}