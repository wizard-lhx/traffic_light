#ifndef __DRV_ANO_DT_H
#define __DRV_ANO_DT_H

//==引用
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

//==定义/声明

typedef struct
{
	int16_t x;
	int16_t y;

	int16_t chassis_angle;

	int16_t yaw;
	int16_t pitch;
} _car_dt_st;

typedef struct
{
	int16_t x;
	int16_t y;

	int16_t speed_rotate;

	int16_t angle_yaw;
	int16_t angle_pitch;
} _ctrl_move_st;
typedef union 
{
	uint8_t byte_data[10];
	_ctrl_move_st st_data;
}_ctrl_move_un;

typedef struct
{
	uint8_t shoot_num; //发射数量
	uint16_t speed_shoot;   //发射速度
} _ctrl_shoot_st;
typedef union 
{
	uint8_t byte_data[3];
	_ctrl_shoot_st st_data;
}_ctrl_shoot_un;

typedef struct
{
	uint8_t photo_num; //拍照数量
} _ctrl_photo_st;
typedef union 
{
	uint8_t byte_data[1];
	_ctrl_photo_st st_data;
}_ctrl_photo_un;

//==数据声明
extern _car_dt_st car_dt;
extern _ctrl_move_un ctrl_move;
extern _ctrl_photo_un ctrl_photo;
extern _ctrl_shoot_un ctrl_shoot;
//==函数声明
//static
static void ANO_DT_DataAnl(uint8_t *data_buf, uint8_t num);

//public
void ANO_DT_GetOneByte(uint8_t data);
void Frame_Send(uint8_t frame_num);
#endif
