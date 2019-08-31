////正确解析数据串口数据，得到经纬度、日期和时间信息
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
//uchar GPS_time[9];                  //UTC时间
//uchar GPS_wd[11];                  //纬度
//uchar GPS_jd[12];                  //经度
//uchar GPS_warn;                          //定位警告
//uchar GPS_status;                  //定位状态
//uchar GPS_alt[8];                  //海拔
//uchar GPS_sv[3];                  //使用卫星
//uchar GPS_speed[6];                  //速度
//uchar GPS_date[9];                  //UTC日期
//
//uchar Segment;                           //逗号计数
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
//	if (tmp == '$')//起始标志
//	{
//		ReceivingF = 1;
//		Bytes_counter = 0;
//		Segment = 0;   //清空语句段计数器
//		return;
//	}
//	if (ReceivingF)
//	{
//		if (tmp == ',')
//		{
//			Segment;
//			Bytes_counter = 0;//清空段字节计数器
//		}
//		if (tmp == '*')//收到结束标志
//		{
//			Command = 0;
//			ReceivingF = 0;
//			EndF = 1;
//			return;
//		}
//		switch (Segment)          //分段处理
//		{
//		case 0:if (Bytes_counter == 3) //段0，语句类型判断
//			switch (tmp)
//		{
//			case 'G':Command = 1;//语句类型 $GPGGA
//				break;
//			case 'M':Command = 2;//语句类型 $GPRMC
//				break;
//			default:Command = 0; //非有效数据类型，终止当前数据接收
//				ReceivingF = 0;
//				break;
//		}
//			   break;
//		case 1:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 2 || Bytes_counter == 5)        //$GPGGA段1，UTC时间，hhmmss（时分秒）格式,取前6位 转换为HH:MM:SS格式
//
//			GPS_time[Bytes_counter] = tmp;
//			if (Bytes_counter>1 && Bytes_counter<4)
//				break;
//		case 2:break;                                                 //$GPRMC第1段处理 忽略        
//		}
//			   break;
//
//		case 2:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 2)                                  //$GPGGA 段2处理 纬度ddmm.mmmm（度分）格式
//		{
//						   GPS_wd[Bytes_counter] = '.';        //接收第二个字节后插入'.'
//						   Bytes_counter;
//						   GPS_wd[10] = '\0';
//		}
//					   if (Bytes_counter == 0)
//						   Bytes_counter;
//					   GPS_wd[Bytes_counter] = tmp;
//					   break;
//		case 2:        GPS_warn = tmp; //$GPRMC第二段处理 定位状态，A=有效定位，V=无效定位
//			break;
//		}
//			   break;
//		case 3:switch (Command)
//		{
//		case 1:        GPS_wd[0] = tmp; //$GPGGA第3段处理 纬度半球N（北半球）或S（南半球）break;
//		case 2:                                         //$GPRMC第3段处理 忽略
//			break;
//		}
//			   break;
//		case 4:switch (Command)
//		{
//		case 1:        if (Bytes_counter == 3)                                  //$GPGGA 段4处理 经度dddmm.mmmm（度分）格式
//		{
//						   GPS_jd[Bytes_counter] = '.';        //接收第3个字节后插入'.'
//						   Bytes_counter;
//						   GPS_jd[11] = '\0';
//		}
//					   if (Bytes_counter == 0)
//						   Bytes_counter;
//					   GPS_jd[Bytes_counter] = tmp;
//					   break;
//		case 2:                                                                         //$GPRMC第4段 忽略
//			break;
//		}
//			   break;
//		case 5:        switch (Command)
//		{
//		case 1:        GPS_jd[0] = tmp;         //$GPGGA第5段处理 经度半球E（东经）或W（西经）
//			break;
//		case 2:                                                 //$GPRMC第5段处理 忽略
//			break;
//		}
//					   break;
//		case 6:        switch (Command)
//		{
//		case 1:        GPS_status = tmp;         //$GPGGA第6段处理 GPS状态：0=未定位，1=非差分定位，2=差分定位，6=正在估算
//			break;
//		case 2:                                                 //$GPRMC第6段处理 忽略
//			break;
//		}
//					   break;
//		case 7:        switch (Command)
//		{
//		case 1:        if (Bytes_counter<2)        //$GPGGA第7段处理  正在使用解算位置的卫星数量（00~12）（前面的0也将被传输）
//			GPS_sv[Bytes_counter] = tmp;
//			GPS_sv[2] = '\0';
//			break;
//		case 2:        if (Bytes_counter<5)        //$GPRMC第7段处理 地面速率（000.0~999.9节，前面的0也将被传输）
//		{
//						   GPS_speed[Bytes_counter] = tmp;
//						   GPS_speed[Bytes_counter 1] = '\0';
//		}
//					   break;
//		}
//					   break;
//		case 9:        switch (Command)
//		{
//		case 1:        if (Bytes_counter<7)         //$GPGGA第9段处理 海拔高度（-9999.9~99999.9）
//		{
//						   GPS_alt[Bytes_counter] = tmp;
//						   GPS_alt[Bytes_counter 1] = '\0';
//		}
//					   break;
//		case 2:        if (Bytes_counter<2)        //$GPRMC第9段处理 UTC日期，ddmmyy（日月年）格式转换为yy.mm.dd
//		{
//						   GPS_date[6 Bytes_counter] = tmp;
//		}
//					   if (Bytes_counter>1 && Bytes_counter<4)//月
//					   {
//						   GPS_date[1 Bytes_counter] = tmp;
//						   GPS_date[5] = '-';
//					   }
//					   if (Bytes_counter>3 && Bytes_counter<6)//年
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
