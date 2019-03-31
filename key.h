#ifndef __KEY_h_
#define __KEY_h_

/**
 * 按键相关的定义
*/
//按钮定义
sbit KEY_k1 = P3 ^ 2;		//玩家1加分
sbit KEY_k2 = P3 ^ 3;
sbit KEY_k3 = P3 ^ 4;
sbit KEY_k4 = P3 ^ 5;		//玩家2加分

//
#define K_SCORE_UP KEY_k1

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

#define K_NEXT_GAME k2 

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


#endif