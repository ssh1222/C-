//#include <Windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//HANDLE hCom;
//int main(void)
//{
//	hCom = CreateFile(TEXT("COM4"),   //COM4��
//		GENERIC_READ | GENERIC_WRITE, //�������д
//		0, //��ռ��ʽ
//		NULL,
//		OPEN_EXISTING, //�򿪶����Ǵ���
//		0, //ͬ����ʽ
//		NULL);
//	if (hCom == (HANDLE)-1)
//	{
//		printf("��COMʧ��!\n");
//		return FALSE;
//	}
//	else
//	{
//		printf("COM�򿪳ɹ���\n");
//	}
//	SetupComm(hCom, 1024, 1024);        //���뻺����������������Ĵ�С����1024
//	COMMTIMEOUTS TimeOuts;
//	//�趨����ʱ
//	TimeOuts.ReadIntervalTimeout = 2000;
//	TimeOuts.ReadTotalTimeoutMultiplier = 500;
//	TimeOuts.ReadTotalTimeoutConstant = 5000;
//	//�趨д��ʱ
//	TimeOuts.WriteTotalTimeoutMultiplier = 500;
//	TimeOuts.WriteTotalTimeoutConstant = 2000;
//	SetCommTimeouts(hCom, &TimeOuts);     //���ó�ʱ
//	DCB dcb;
//	GetCommState(hCom, &dcb);
//	dcb.BaudRate = 9600;       //������Ϊ9600
//	dcb.ByteSize = 8;          //ÿ���ֽ���8λ
//	dcb.Parity = NOPARITY;     //����żУ��λ
//	dcb.StopBits = ONE5STOPBITS;     //����ֹͣλ
//	SetCommState(hCom, &dcb);
//	DWORD wCount;              //��ȡ���ֽ���
//	BOOL bReadStat;
//	while (1)
//	{
//		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);       //��ջ�����
//		char str[9] = { 0 };
//		printf("%s\n", str);
//		bReadStat = ReadFile(hCom, str, 9, &wCount, NULL);
//		if (!bReadStat)
//		{
//			printf("������ʧ��!");
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