#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "ADC7606.h"


extern int16_t s_adc_now[8], s_volt[8],s_dat[8];

/*********************************************************************************************************
*	函 数 名: LCD_BasisDisplay
*	功能说明: LCD基础显示
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/
void LCD_BasisDisplay()		//LCD基础显示
{
	BACK_COLOR=BLACK;		//设置背景颜色黑色
	POINT_COLOR=WHITE;		//设置画笔颜色白色
	
	LCD_ShowString(30,40,200,24,24,"Mini STM32");	
	LCD_ShowString(30,70,200,16,16,"ADC7606 TEST");
	LCD_ShowString(30,90,200,16,16,"@T E A"); 
	LCD_ShowString(30,110,200,16,16,"@fu you");
	LCD_ShowString(30,150,200,16,16,"Voltage:0.000V");
	LCD_ShowString(30,180,200,16,16,"AD_CH1:");   
}



/*********************************************************************************************************
*	函 数 名: LED_Flicker
*	功能说明: LED闪烁提示
*	形    参：t：闪烁间隔时间
*	返 回 值: 无
*********************************************************************************************************/
void LED_Flicker(u16 t)		//LED闪烁提示
{
	static u16 i=0;
	
	i++;
	if(i>=t)
	{
		LED1=!LED1;
		i = 0;
	}
	delay_ms(1);
}



/*********************************************************************************************************
*	函 数 名: LCD_Result
*	功能说明: 显示处理数据
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/
void LCD_Result()
{	
	LCD_ShowxNum(86,180,s_adc_now[0],8,16,0x00);		//显示AD值
	LCD_ShowxNum(94,150,s_volt[0]/1000,1,16,0x80);
	LCD_ShowxNum(110,150,s_volt[0]%1000,3,16,0X80);	//显示电压值	
}



/*********************************************************************************************************
*	函 数 名: main
*	功能说明: AD7606测试
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/

int main(void)
{	
	u8 i;
	delay_init();	    	//延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();
	AD7606_Init();			//初始化AD7606
	
	LCD_BasisDisplay();		//LCD基础显示
	while(1) 
	{
		LED_Flicker(100);	//LED闪烁提示
		if(i>=30)
		{
			AD7606_Scan();		//读取AD转换器数据
			AD7606_Count();		//处理采样后的数据
			LCD_Result();		//显示处理数据
			i=0;
		}
		i++;
		delay_ms(10);
	} 
}


