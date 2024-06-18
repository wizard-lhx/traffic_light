#include "bsp_ano_dt.h" // 数传串口驱动函数，主要与上位机进行通信。

_led_dt_un led_dt;
_ctrl_time_st ctrl_time;
static uint8_t _datatemp[15];
static uint8_t rx_buffer[15];
static uint8_t buffer_a[15];
static uint8_t buffer_b[15];

static uint8_t *buffer_ready_for_user;
static uint8_t *buffer_ready_for_reception;

void ano_dt_init(void)
{
	buffer_ready_for_user = buffer_a;
	buffer_ready_for_reception = buffer_b;
	
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, 10))
	{
		Error_Handler();
	}
}

//ANO_DT_GetOneByte是初级数据解析函数，串口每接收到一字节上位机数据，调用本函数一次，函数参数就是串口收到的数据
//当本函数多次被调用，最终接收到完整的一帧数据后，会自动调用数据解析函数ANO_DT_DataAnl
static void ANO_DT_GetOneByte(uint8_t data)
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

	if (*(data + 2) == 0X01) //移动指令
	{
		ctrl_time.vertical_green_time = *(data);
    ctrl_time.horizontal_green_time = *(data + 1);
    ctrl_time.vertical_turn_left_green_time = *(data + 2);
    ctrl_time.horizontal_turn_left_green_time = *(data + 3);
    ctrl_time.people_time = *(data + 4);
	}
}

//===================================================================
//数据发送实现程序
//===================================================================
static uint8_t send_buffer[15];

static void Add_Send_Data(uint8_t frame_num, uint8_t *_cnt, uint8_t send_buffer[])
{
	//根据需要发送的帧ID，也就是frame_num，来填充数据，填充到send_buffer数组内
	switch (frame_num)
	{
	case 0x04: //发送位置数据
	{
		for (uint8_t i = 0; i < 5; i++)
		{
			send_buffer[(*_cnt)++] = led_dt.byte_data[i];
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

	//USART_Send_Data(send_buffer, _cnt);  //需要替换成自己发送字符串的函数
	HAL_UART_Transmit(&huart1, send_buffer, _cnt, 0xffff);
	//HAL_UART_Transmit_IT(&huart1, send_buffer, _cnt);
}

void ano_dt_rx_data_handle(uint16_t size)
{
	static uint8_t old_pos = 0;
	static uint16_t num_of_new_char = 0;
	uint8_t *ptemp;
	uint8_t i;

	/* Check if number of received data in recpetion buffer has changed */
	if (size != old_pos)
	{
	/* Check if position of index in reception buffer has simply be increased
	   of if end of buffer has been reached */
	if (size > old_pos)
	{
	  /* Current position is higher than previous one */
	  num_of_new_char = size - old_pos;
	  /* Copy received data in "User" buffer for evacuation */
	  for (i = 0; i < num_of_new_char; i++)
	  {
		buffer_ready_for_user[i] = rx_buffer[old_pos + i];
	  }
	}
	else
	{
	  /* Current position is lower than previous one : end of buffer has been reached */
	  /* First copy data from current position till end of buffer */
	  num_of_new_char = 15 - old_pos;
	  /* Copy received data in "User" buffer for evacuation */
	  for (i = 0; i < num_of_new_char; i++)
	  {
		buffer_ready_for_user[i] = rx_buffer[old_pos + i];
	  }
	  /* Check and continue with beginning of buffer */
	  if (size > 0)
	  {
		for (i = 0; i < size; i++)
		{
		  buffer_ready_for_user[num_of_new_char + i] = rx_buffer[i];
		}
		num_of_new_char += size;
	  }
	}
	/* Process received data that has been extracted from Rx User buffer */
	for(i = 0; i < num_of_new_char; i++)
	{
		ANO_DT_GetOneByte(buffer_ready_for_user[i]);
	}

	/* Swap buffers for next bytes to be processed */
	ptemp = buffer_ready_for_user;
	buffer_ready_for_user = buffer_ready_for_reception;
	buffer_ready_for_reception = ptemp;
	}
	/* Update old_pos as new reference of position in User Rx buffer that
	 indicates position to which data have been processed */
	old_pos = size;
}
