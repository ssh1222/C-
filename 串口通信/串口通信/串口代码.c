#include <stdio.h>
#include <stdlib.h>

typedef struct {
	HANDLE hCom;
	uint32_t baudrate;
	uint32_t bytesize;
	char parity;
	uint32_t stopbit;
}rs232_device; 

int set_opt(HANDLE hFile, int nSpeed, int nBits, char nEvent, int nStop)
{
	DCB dcb;
	COMMTIMEOUTS timeouts;//set input buf and output buf
	SetupComm(hFile, 512, 512);//set read timeout
	timeouts.ReadIntervalTimeout = 1000;
	timeouts.ReadTotalTimeoutMultiplier = 500;
	timeouts.ReadTotalTimeoutConstant = 5000;
	//set write timeout
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hFile, &timeouts);//store current setting
	if (0 == GetCommState(hFile, &dcb)){
		return -1;
	}//set BaudRate
	switch (nSpeed){
	case 2400:
		dcb.BaudRate = CBR_2400;
		break;
	case 4800:
		dcb.BaudRate = CBR_4800;
		break;
	case 115200:
		dcb.BaudRate = CBR_115200;
		break;
	default:
		dcb.BaudRate = CBR_9600;
		break;
	}//set ByteSize
	switch (nBits){
	case 7:
		dcb.ByteSize = 7;
		break;
	case 8:
		dcb.ByteSize = 8;
		break;
	default:
		dcb.ByteSize = 8;
		break;
	}//set Parity
	switch (nEvent){
	case 'N':
		dcb.Parity = NOPARITY;
		break;
	case 'O':
		dcb.Parity = ODDPARITY;
		break;
	case 'E':
		dcb.Parity = EVENPARITY;
		break;
	}//set StopBit
	switch (nStop){
	case 1:
		dcb.StopBits = ONESTOPBIT;
		break;
	case 2:
		dcb.StopBits = TWOSTOPBITS;
		break;
	} if (0 == SetCommState(hFile, &dcb)){
		return -1;
	}    return 0;
} rs232_device rs232_dev;
rs232_dev.baudrate = 119200;
rs232_dev.bytesize = 8;
rs232_dev.parity = 'N';
rs232_dev.stopbit = 1;
//打开串口4
rs232_dev.hCom = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
if (rs232_dev.hCom != INVALID_HANDLE_VALUE){
	printf("Open COM4 OK!\n");
}
else
printf("Open COM4 Fail!\n");
//通讯设置
if (-1 == set_opt(rs232_dev.hCom,
	rs232_dev.baudrate,
	rs232_dev.bytesize,
	rs232_dev.parity,
	rs232_dev.stopbit))
{
	if (INVALID_HANDLE_VALUE != rs232_dev.hCom)
		CloseHandle(rs232_dev.hCom);
} unsigned char readBuf[1024] = { 0 };
char writeBuf[1024] = "Hello Ketty!";
int count = 100;
DWORD readsize = 0;
DWORD writesize = 0;
int i;
while (1){
	if (INVALID_HANDLE_VALUE != rs232_dev.hCom){
		printf("Start Read!\n");
		//串口读操作
		ReadFile(rs232_dev.hCom, readBuf, count, &readsize, NULL);
		printf("Read Buf=");
		for (i = 0; i<readsize; i++)
			printf("%x ", readBuf[i]);
		printf("\n");
	}  
	//串口写操作
	WriteFile(rs232_dev.hCom, writeBuf, count, &writesize, NULL);
}
