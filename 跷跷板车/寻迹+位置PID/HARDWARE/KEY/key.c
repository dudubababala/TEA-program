#include "key.h"
#include "delay.h"

/******************************************************************
*函数名称:	KEY_Init
*函数功能:	初始化按键
*函数参数:	无
*返 回 值:	无
*******************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	//使能IO端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//根据设定参数初始化GPIO 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			//下拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO
}


/******************************************************************
*函数名称:	KEY_Scan
*函数功能:	按键处理函数
*函数参数:	mode:0,不支持连续按;1,支持连续按;
*返 回 值:	返回按键值
			0，没有任何按键按下
			KEY0_PRES，KEY0按下
			KEY1_PRES，KEY1按下
			WKUP_PRES，WK_UP按下
*注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
*******************************************************************/
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;		//按键按松开标志
	
	if(mode)key_up=1;		//支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(1);		//去抖动 
		key_up=0;
		if(KEY0==0)	return KEY0_PRES;
		else if(KEY1==0) return KEY1_PRES;
		else if(WK_UP==1) return WKUP_PRES; 
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0) key_up=1; 	     
	return 0;// 无按键按下
}

