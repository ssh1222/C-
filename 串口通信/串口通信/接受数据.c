#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h> 

#define TRUE 1
#define FALSE 0 

int analysis(char *buff);
int OpenDev(char *Dev);
void set_speed(int fd, int speed);
int set_Parity(int fd,int databits,int stopbits,int parity); 
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400, 19200, 9600, 4800, 2400, 1200, 300, 38400, 19200, 9600, 4800, 2400, 1200, 300, };
int OpenDev(char *Dev)
{  
	int fd = open(Dev,O_RDWR | O_NOCTTY | O_NONBLOCK);  
	if(-1 == fd)    
	{      
		perror("Can't Open Serial Port");      
		return -1;    
	}   
	else     
	{      
		printf("Open com success!!!!!!!!!!!");      
		return fd;    
	}
} 
void set_speed(int fd, int speed)
{   
	int i;   
	int status;   
	struct termios Opt; tcgetattr(fd, &Opt);   
	for ( i= 0; i < sizeof(speed_arr) / sizeof(int); i++)   
	{       
		if (speed == name_arr[i])         
		{           
			tcflush(fd, TCIOFLUSH);           
			cfsetispeed(&Opt, speed_arr[i]);         
			cfsetospeed(&Opt, speed_arr[i]);         
			status = tcsetattr(fd, TCSANOW, &Opt);           
			if (status != 0) perror("tcsetattr fd1");         
			return;       
		}     
		tcflush(fd,TCIOFLUSH);    
	}
}
int set_Parity(int fd,int databits,int stopbits,int parity) 
{   
	struct termios options;   
	if ( tcgetattr( fd,&options) != 0)   
	{   
		perror("SetupSerial 1");   
		return(FALSE); 
	}   
	bzero(&options,sizeof(options));   
	options.c_cflag |= CLOCAL | CREAD; 
	options.c_cflag &= ~CSIZE;   
	switch (databits)   
	{     
	case 7:     
		options.c_cflag |= CS7;   
		break;   
	case 8:   
		options.c_cflag |= CS8;   
		break;     
	default: 
		fprintf(stderr,"Unsupported data size\n");   
		return (FALSE);   
	}   
	switch (parity)   
	{   
	case 'n':     
	case 'N':   
		options.c_cflag &= ~PARENB;   
		options.c_iflag &= ~INPCK;     
		break;     
	case 'o':   
	case 'O':     
		options.c_cflag |= (PARODD | PARENB);   
		options.c_iflag |= (INPCK | ISTRIP);     
		break;     
	case 'e':     
	case 'E':     
		options.c_cflag |= PARENB;   
		options.c_cflag &= ~PARODD;     
		options.c_iflag |= (INPCK | ISTRIP);     
		break;     
	case 'S':     
	case 's':     
		options.c_cflag &= ~PARENB;     
		options.c_cflag &= ~CSTOPB;   
		break;   
	default: 
		fprintf(stderr,"Unsupported parity\n");    
		return (FALSE);   
	}   
	switch (stopbits) 
	{     
	case 1:   
		options.c_cflag &= ~CSTOPB;     
		break;     
	case 2:     
		options.c_cflag |= CSTOPB;   
		break;     
	default: 
		fprintf(stderr,"Unsupported stop bits\n");     
		return (FALSE);     
	}     
	if (parity != 'n')     
		options.c_iflag |= INPCK;     
	options.c_cc[VTIME] = 0;   
	options.c_cc[VMIN] = 0;   
	tcflush(fd,TCIFLUSH);     
	if (tcsetattr(fd,TCSANOW,&options) != 0)   
	{          
		perror("SetupSerial 3");         
		return (FALSE);   
	}     
	return (TRUE);
} 

int analysis(char *buff）
{  
	int i;  
	char *p;
	p=buff;  
	for (i = 0; i < 255; i++)
	{      
		printf("%s ",p[i]);    
	}  
	return 0;
} 

void main(void)
{  
	int fd;  
	int nread;  
	char buff[255];  
	char *dev_name = "/dev/ttymxc4";//根据实际情况选择串口  
	while(1)     
	{        
		fd = OpenDev(dev_name); //打开串口        
		if(fd>0)       
			set_speed(fd,9600); //设置波特率       
		else       
		{          
			printf("Can't Open Serial Port!\n");          
			sleep(1);        
			continue;       
		}   
		break;
	} 
	if(set_Parity(fd,8,1,'N')==FALSE) //设置校验位 
	{  
		printf("Set Parity Error\n");   
		exit(1);
	} 
	while(1)   
	{     
		sleep(3);     
		nread = read(fd,buff,sizeof(buff));    
		if((nread>0))      
		{			
			printf("Success!\n");       
		}    
		analysis(buff);
	}
}

