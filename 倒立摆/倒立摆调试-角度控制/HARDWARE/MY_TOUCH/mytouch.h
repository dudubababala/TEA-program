#ifndef _mytouch_h_
#define _mytouch_h_

#include "sys.h"


extern s8 Key_Flag;
extern u8 Press_Flag;
extern u8 Press_Flag_4X4;
extern u16 AimAngleSet;
extern u16 SetAngle;

/********************************************************************************
函数功能：画水平线
入口参数：x0,y0:坐标；
		  len:线长度
		  color:颜色
返回参数：无
*********************************************************************************/
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);

/********************************************************************************
函数功能：画实心圆
入口参数：x0,y0:坐标
		  r:半径
		  color:颜色
返回参数：无
*********************************************************************************/
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);

/********************************************************************************
函数功能：画一条粗线
入口参数：(x1,y1),(x2,y2):线条的起始坐标
		  size：线条的粗细程度
		  color：线条的颜色
返回参数：无
*********************************************************************************/
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);

/********************************************************************************
函数功能：显示4*4数字键盘
入口参数：(x1,y1),(x2,y2):键盘的对角坐标
		  size：键盘数字大小
返回参数：无
函数作者：@FUYOU
*********************************************************************************/
void Display_4X4_Keypad(u16 x1, u16 y1, u16 x2, u16 y2, u8 size);

/********************************************************************************
函数功能：4*4触摸按键,支持连按
入口参数：(x1,y1),(x2,y2):键盘的对角坐标
返回参数：按键值
函数作者：@FUYOU
*********************************************************************************/
s8 Touch_Keyboard(u16 x1, u16 y1, u16 x2, u16 y2);

/********************************************************************************
函数功能：显示4*1触摸按键,圆形
入口参数：无
返回参数：无
函数作者：@FUYOU
*********************************************************************************/
void Display_4X1_Key(u16 x1,u16 y1,u16 x2,u16 y2);

/********************************************************************************
函数功能：4*1触摸按键,支持连按
入口参数：无
返回参数：按键值
函数作者：@FUYOU
*********************************************************************************/
u8 Touch_Key(u16 x1,u16 y1,u16 x2,u16 y2);

/********************************************************************************
函数功能：触摸按键设置
入口参数：无
返回参数：无
函数作者：@FUYOU
*********************************************************************************/
void TouchKey_Set(void);

#endif
