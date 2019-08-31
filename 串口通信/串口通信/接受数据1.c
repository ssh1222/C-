//#include <Windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//HANDLE hCom;
//int main(void)
//{
//	hCom = CreateFile(TEXT("COM4"),   //COM4口
//		GENERIC_READ | GENERIC_WRITE, //允许读和写
//		0, //独占方式
//		NULL,
//		OPEN_EXISTING, //打开而不是创建
//		0, //同步方式
//		NULL);
//	if (hCom == (HANDLE)-1)
//	{
//		printf("打开COM失败!\n");
//		return FALSE;
//	}
//	else
//	{
//		printf("COM打开成功！\n");
//	}
//	SetupComm(hCom, 1024, 1024);        //输入缓冲区和输出缓冲区的大小都是1024
//	COMMTIMEOUTS TimeOuts;
//	//设定读超时
//	TimeOuts.ReadIntervalTimeout = 2000;
//	TimeOuts.ReadTotalTimeoutMultiplier = 500;
//	TimeOuts.ReadTotalTimeoutConstant = 5000;
//	//设定写超时
//	TimeOuts.WriteTotalTimeoutMultiplier = 500;
//	TimeOuts.WriteTotalTimeoutConstant = 2000;
//	SetCommTimeouts(hCom, &TimeOuts);     //设置超时
//	DCB dcb;
//	GetCommState(hCom, &dcb);
//	dcb.BaudRate = 9600;       //波特率为9600
//	dcb.ByteSize = 8;          //每个字节有8位
//	dcb.Parity = NOPARITY;     //无奇偶校验位
//	dcb.StopBits = ONE5STOPBITS;     //两个停止位
//	SetCommState(hCom, &dcb);
//	DWORD wCount;              //读取的字节数
//	BOOL bReadStat;
//	while (1)
//	{
//		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);       //清空缓冲区
//		char str[9] = { 0 };
//		printf("%s\n", str);
//		bReadStat = ReadFile(hCom, str, 9, &wCount, NULL);
//		if (!bReadStat)
//		{
//			printf("读串口失败!");
//			return FALSE;
//		}
//		else
//		{
//			str[8] = '\0';
//			printf("%s\n", str);
//		}
//		Sleep(100);	
//	}
//	system("pause");
//}