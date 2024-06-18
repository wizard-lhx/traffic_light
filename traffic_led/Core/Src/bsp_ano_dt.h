#ifndef __BSP_ANO_DT_H
#define __BSP_ANO_DT_H

#include "usart.h"

//==定义/声明

typedef struct
{
	int8_t vertical_green_time;
	int8_t horizontal_green_time;
	int8_t vertical_turn_left_green_time;
	int8_t horizontal_turn_left_green_time;
	int8_t people_time;
} _led_dt_st;
typedef union 
{
	uint8_t byte_data[5];
	_led_dt_st st_data;
}_led_dt_un;

typedef struct
{
	int8_t vertical_green_time;
	int8_t horizontal_green_time;
	int8_t vertical_turn_left_green_time;
	int8_t horizontal_turn_left_green_time;
	int8_t people_time;
} _ctrl_time_st;

//==数据声明
extern _led_dt_un led_dt;
extern _ctrl_time_st ctrl_time;
//==函数声明
//static
static void ANO_DT_DataAnl(uint8_t *data_buf, uint8_t num);
static void ANO_DT_GetOneByte(uint8_t data);

//public
void ano_dt_init(void);
void ano_dt_rx_data_handle(uint16_t size);
void Frame_Send(uint8_t frame_num);
#endif
