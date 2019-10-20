#include "usart.h"
#include "stdarg.h"
#include "string.h"
  
	 
/*************************************************************************
函数功能：	串口初始化
入口参数：	baud：波特率，最大14400
返回参数：	无
函数作者：	fy
**************************************************************************/
void USART_Init(u16 baud)
{		   
	double arr,temp;
//	double _SysClock = 12000000;//系统时钟
//	double _psc = 12;			//分频系数
	 	
	/*
	波特率公式：baud = (2/32) * (1/t)	 
	定时器定时时间：t = 1/(SysClock/12)*(256-arr)	
	*/

	temp = 1.0 / ((double)(baud / (2.0/32.0)));		//计算定时器定时时间
	temp *= SysClock/SysPsc;						//计算定时器计数值
	arr = 256.0 - temp;								//计算重装值	
	
	PCON |= 0x80;	//使能波特率倍速位SMOD
	SCON = 0x50;	//8位数据,可变波特率
	TMOD &= 0x0F;	//清除定时器1模式位
	TMOD |= 0x20;	//设定定时器1为8位自动重装方式
	TL1 = (u8)arr;	//设定定时初值
	TH1 = (u8)arr;	//设定定时器重装值
	ET1 = 0;		//禁止定时器中断
	ES = 1;		   	//打开串口中断
	EA = 1;			//打开总中断   
	TI = 1;	
	TR1 = 1;		//启动定时器1	
}



/*************************************************************************
函数功能：	串口中断服务函数
入口参数：	无
返回参数：	无
**************************************************************************/
void USART_Int() interrupt 5
{
	if(RI)
	{
		RI = 0;
	}
	if(TI)
	{
		TI = 0;
	}
}



/*定义下面的宏使用系统PRINTF*/
//#define SYSPRINTF

/******************************************************************************************/ 
/*使用系统PRINTF*/
#ifdef SYSPRINTF
/*************************************************************************
函数功能：	串口打印函数
入口参数：	无
返回参数：	无
**************************************************************************/
void uart_printf(char* fmt,...)
{
	u16 i,j;
	static xu8 USART_TX_BUF[50]; 	//定义发送数组，存发送数据
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_TX_BUF);
	for(j=0;j<i;j++)
	{
		SBUF = USART_TX_BUF[j];		//把串口1的数据发送到串口2
		while(!TI);					//等待发送结束
		TI = 0;
	}
}

/******************************************************************************************/ 
/*使用自定义PRINTF*/
#else

/*************************************************************************
函数功能：	发送一个字符
入口参数：	c：发送的字符
返回参数：	无
**************************************************************************/
void sendbyte(unsigned char c)  
{  
    if(c=='\n')//如果遇到\n就换行  
    {  
        //发送CR(carriage return)  
        SBUF=0x0D;   
        while(!TI);//等待发送完成  
        TI=0;  
          
        //发送 LF(NL line feed,new line)  
        SBUF=0x0A;   
        while(!TI);//等待发送完成  
        TI=0;         
    }  
    else  
    {  
        SBUF=c;  
        while(!TI);//等待发送完成  
        TI=0;  
    }  
}  

 
/*************************************************************************
函数功能：	发送字符串
入口参数：	string：字符串首地址
返回参数：	无
**************************************************************************/ 
void sendstring(unsigned char *string)//此处*string相当于数组  
{  
    while(*string!='\0')//判断是否到字符串末尾  
    {  
        sendbyte(*string);  
        string++;  
    }  
}  


/*************************************************************************
函数功能：	串口打印函数
入口参数：	无
返回参数：	无
**************************************************************************/  
void uart_printf(const char *fmt,...)  
{  
    va_list ap;  
    xdata char string[50];//访问内部拓展RAM，非访问外部RAM，不能超过内部拓展RAM大小(此处为1024)  
      
    va_start(ap,fmt);  
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去  
    sendstring(string);  
    va_end(ap);  
} 

#endif 