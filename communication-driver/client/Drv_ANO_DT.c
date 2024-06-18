#include "Drv_ANO_DT.h" // 数传串口驱动函数，主要与小车进行通信。
//#include "Drv_Uart.h"

_car_dt_st car_dt;
_ctrl_move_un ctrl_move;
_ctrl_shoot_un ctrl_shoot;
_ctrl_photo_un ctrl_photo;
static uint8_t _datatemp[20];

//ANO_DT_GetOneByte是初级数据解析函数，串口每接收到一字节小车数据，调用本函数一次，函数参数就是串口收到的数据
//当本函数多次被调用，最终接收到完整的一帧数据后，会自动调用数据解析函数ANO_DT_DataAnl
void ANO_DT_GetOneByte(uint8_t data)
{
	static uint8_t _data_len = 0, _data_cnt = 0;
	static uint8_t rxstate = 0;

	if (rxstate == 0 && data == 0xAA)
	{
		rxstate = 1;
		_datatemp[0] = data;
	}
	else if (rxstate == 1 && data == 0xFF)
	{
		rxstate = 2;
		_datatemp[1] = data;
	}
  else if (rxstate == 2)
	{
		rxstate = 3;
		_datatemp[2] = data;
	}
	else if (rxstate == 3 && data < 15)
	{
		rxstate = 4;
		_datatemp[3] = data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if (rxstate == 4 && _data_len > 0)
	{
		_datatemp[4 + _data_cnt] = data;
		_data_cnt += 1;
		if(_data_cnt >= _data_len)
		{
			_data_cnt = 0;
			rxstate = 5;
		}
	}
	else if (rxstate == 5)
	{
		rxstate = 6;
		_datatemp[4 + _data_len] = data;
	}
	else if (rxstate == 6)
	{
		rxstate = 0;
		_datatemp[5 + _data_len] = data;
		ANO_DT_DataAnl(_datatemp, _data_len + 6); //
	}
	else
	{
		rxstate = 0;
	}
}

//ANO_DT_DataAnl为数传数据解析函数，可以通过本函数得到数传输出的各项数据
static void ANO_DT_DataAnl(uint8_t *data, uint8_t len)
{
	uint8_t check_sum1 = 0, check_sum2 = 0;
	if (*(data + 3) != (len - 6)) //判断数据长度是否正确
		return;
	for (uint8_t i = 0; i < len - 2; i++)
	{
		check_sum1 += *(data + i);
		check_sum2 += check_sum1;
	}
	if ((check_sum1 != *(data + len - 2)) || (check_sum2 != *(data + len - 1))) //判断sum校验
		return;
	//================================================================================

	if (*(data + 2) == 0X04) //位置数据
	{
		car_dt.x = *((int16_t *)(data + 4));
    car_dt.y = *((int16_t *)(data + 6));
	}
  else if (*(data + 2) == 0X05) //底盘朝向数据
	{
		car_dt.chassis_angle = *((int16_t *)(data + 4));
	}
  else if (*(data + 2) == 0X06) //云台角度数据
	{
		car_dt.yaw = *((int16_t *)(data + 4));
    car_dt.pitch = *((int16_t *)(data + 6));
	}
}

//===================================================================
//数据发送实现程序
//===================================================================
static uint8_t send_buffer[20];

static void Add_Send_Data(uint8_t frame_num, uint8_t *_cnt, uint8_t send_buffer[])
{
	//根据需要发送的帧ID，也就是frame_num，来填充数据，填充到send_buffer数组内
	switch (frame_num)
	{
	case 0x01: //控制运动数据
	{
		for (uint8_t i = 0; i < 10; i++)
		{
			send_buffer[(*_cnt)++] = ctrl_move.byte_data[i];
		}
	}
	break;
  case 0x02: //控制拍照数据
	{
		for (uint8_t i = 0; i < 1; i++)
		{
			send_buffer[(*_cnt)++] = ctrl_photo.byte_data[i];
		}
	}
	break;
  case 0x03: //控制射击数据
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			send_buffer[(*_cnt)++] = ctrl_shoot.byte_data[i];
		}
	}
	break;
	default:
		break;
	}
}

//===================================================================
void Frame_Send(uint8_t frame_num)
{
	uint8_t _cnt = 0;

	send_buffer[_cnt++] = 0xAA;
	send_buffer[_cnt++] = 0xFF;
	send_buffer[_cnt++] = frame_num;
	send_buffer[_cnt++] = 0;
	//==
	//add_send_data
	Add_Send_Data(frame_num, &_cnt, send_buffer);
	//==
	send_buffer[3] = _cnt - 4;
	//==
	uint8_t check_sum1 = 0, check_sum2 = 0;
	for (uint8_t i = 0; i < _cnt; i++)
	{
		check_sum1 += send_buffer[i];
		check_sum2 += check_sum1;
	}
	send_buffer[_cnt++] = check_sum1;
	send_buffer[_cnt++] = check_sum2;

	USART_Send_Data(send_buffer, _cnt);  //需要替换成自己发送字符串的函数
}
