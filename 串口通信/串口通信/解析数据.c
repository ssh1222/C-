////��ȷ�������ݴ������ݣ��õ���γ�ȡ����ں�ʱ����Ϣ
//
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef int bit;
//typedef char uchar;
//
//bit ReceivingF = 0;
//bit EndF = 0;
//bit NewByteF = "0";
//
//uchar GPS_time[9];                  //UTCʱ��
//uchar GPS_wd[11];                  //γ��
//uchar GPS_jd[12];                  //����
//uchar GPS_warn;                          //��λ����
//uchar GPS_status;                  //��λ״̬
//uchar GPS_alt[8];                  //����
//uchar GPS_sv[3];                  //ʹ������
//uchar GPS_speed[6];                  //�ٶ�
//uchar GPS_date[9];                  //UTC����
//
//uchar Segment;                           //���ż���
//uchar Bytes_counter;
//uchar Command;
//uchar tmp;
//
//void uart(void) 
//{
//	if (RI)
//	{
//		tmp = SBUF;
//		NewByteF = 1;
//		RI = 0;
//		return;
//	}
//}
//
//void gps(void)
//{
//	if (tmp == '$')//��ʼ��־
//	{
//		ReceivingF = 1;
//		Bytes_counter = 0;
//		Segment = 0;   //������μ�����
//		return;
//	}
//	if (ReceivingF)
//	{
//		if (tmp == ',')
//		{
//			Segment;
//			Bytes_counter = 0;//��ն��ֽڼ�����
//		}
//		if (tmp == '*')//�յ�������־
//		{
//			Command = 0;
//			ReceivingF = 0;
//			EndF = 1;
//			return;
//		}
//		switch (Segment)          //�ֶδ���
//		{
//		case 0:if (Bytes_counter == 3) //��0����������ж�
//			switch (tmp)
//		{
//			case 'G':Command = 1;//������� $GPGGA
//				break;
//			case 'M':Command = 2;//������� $GPRMC
//				break;
//			default:Command = 0; //����Ч�������ͣ���ֹ��ǰ���ݽ���
//				ReceivingF = 0;
//				break;
//		}
//			   break;
//		case 1:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 2 || Bytes_counter == 5)        //$GPGGA��1��UTCʱ�䣬hhmmss��ʱ���룩��ʽ,ȡǰ6λ ת��ΪHH:MM:SS��ʽ
//
//			GPS_time[Bytes_counter] = tmp;
//			if (Bytes_counter>1 && Bytes_counter<4)
//				break;
//		case 2:break;                                                 //$GPRMC��1�δ��� ����        
//		}
//			   break;
//
//		case 2:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 2)                                  //$GPGGA ��2���� γ��ddmm.mmmm���ȷ֣���ʽ
//		{
//						   GPS_wd[Bytes_counter] = '.';        //���յڶ����ֽں����'.'
//						   Bytes_counter;
//						   GPS_wd[10] = '\0';
//		}
//					   if (Bytes_counter == 0)
//						   Bytes_counter;
//					   GPS_wd[Bytes_counter] = tmp;
//					   break;
//		case 2:        GPS_warn = tmp; //$GPRMC�ڶ��δ��� ��λ״̬��A=��Ч��λ��V=��Ч��λ
//			break;
//		}
//			   break;
//		case 3:switch (Command)
//		{
//		case 1:        GPS_wd[0] = tmp; //$GPGGA��3�δ��� γ�Ȱ���N�������򣩻�S���ϰ���break;
//		case 2:                                         //$GPRMC��3�δ��� ����
//			break;
//		}
//			   break;
//		case 4:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 3)                                  //$GPGGA ��4���� ����dddmm.mmmm���ȷ֣���ʽ
//		{
//						   GPS_jd[Bytes_counter] = '.';        //���յ�3���ֽں����'.'
//						   Bytes_counter;
//						   GPS_jd[11] = '\0';
//		}
//					   if (Bytes_counter == 0)
//						   Bytes_counter;
//					   GPS_jd[Bytes_counter] = tmp;
//					   break;
//		case 2:                                                                         //$GPRMC��4�� ����
//			break;
//		}
//			   break;
//		case 5:        switch (Command)
//		{
//		case 1:        GPS_jd[0] = tmp;         //$GPGGA��5�δ��� ���Ȱ���E����������W��������
//			break;
//		case 2:                                                 //$GPRMC��5�δ��� ����
//			break;
//		}
//					   break;
//		case 6:        switch (Command)
//		{
//		case 1:        GPS_status = tmp;         //$GPGGA��6�δ��� GPS״̬��0=δ��λ��1=�ǲ�ֶ�λ��2=��ֶ�λ��6=���ڹ���
//			break;
//		case 2:                                                 //$GPRMC��6�δ��� ����
//			break;
//		}
//					   break;
//		case 7:        switch (Command)
//		{
//		case 1:        if (Bytes_counter<2)        //$GPGGA��7�δ���  ����ʹ�ý���λ�õ�����������00~12����ǰ���0Ҳ�������䣩
//			GPS_sv[Bytes_counter] = tmp;
//			GPS_sv[2] = '\0';
//			break;
//		case 2:        if (Bytes_counter<5)        //$GPRMC��7�δ��� �������ʣ�000.0~999.9�ڣ�ǰ���0Ҳ�������䣩
//		{
//						   GPS_speed[Bytes_counter] = tmp;
//						   GPS_speed[Bytes_counter 1] = '\0';
//		}
//					   break;
//		}
//					   break;
//		case 9:        switch (Command)
//		{
//		case 1:        if (Bytes_counter<7)         //$GPGGA��9�δ��� ���θ߶ȣ�-9999.9~99999.9��
//		{
//						   GPS_alt[Bytes_counter] = tmp;
//						   GPS_alt[Bytes_counter 1] = '\0';
//		}
//					   break;
//		case 2:        if (Bytes_counter<2)        //$GPRMC��9�δ��� UTC���ڣ�ddmmyy�������꣩��ʽת��Ϊyy.mm.dd
//		{
//						   GPS_date[6 Bytes_counter] = tmp;
//		}
//					   if (Bytes_counter>1 && Bytes_counter<4)//��
//					   {
//						   GPS_date[1 Bytes_counter] = tmp;
//						   GPS_date[5] = '-';
//					   }
//					   if (Bytes_counter>3 && Bytes_counter<6)//��
//					   {
//						   GPS_date[Bytes_counter - 4] = tmp;
//						   GPS_date[2] = '-';
//						   GPS_date[8] = '\0';
//					   }
//					   break;
//		}
//					   break;
//		default:break;
//		}
//		Bytes_counter;
//	}
//	NewByteF = 0;
//}
