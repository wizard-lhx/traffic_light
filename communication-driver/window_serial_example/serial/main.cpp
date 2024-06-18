#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
extern "C"
{
	#include "serial.h"
	#include "Drv_ANO_DT.h"
}

int r[3][4] = {{30, 20, 130, 60}, {170, 20, 220, 60}, {260, 20, 310, 60}}; //三个按钮的二维数组
int16_t moveX = 0, moveY = 0; //X、Y坐标
int16_t moveYAW = 0, movePITCH = 0;
//按钮判断函数
int button_judge(int x, int y) {
	if (x > r[0][0] && x < r[0][2] && y > r[0][1] && y < r[0][3])
		return 1;
	if (x > r[1][0] && x < r[1][2] && y > r[1][1] && y < r[1][3])
		return 2;
	if (x > r[2][0] && x < r[2][2] && y > r[2][1] && y < r[2][3])
		return 3;
	return 0;
}
//初始化图像
void init_figure() {
	short win_width, win_height; //定义窗口的宽度和高度
	win_width = 800;
	win_height = 460;
	initgraph(win_width, win_height, EX_SHOWCONSOLE); //初始化窗口（黑屏）
	setbkcolor(RGB(255, 255, 255)); //设置背景色，原来默认黑色
	cleardevice();//清屏（取决于背景色）

	RECT R1 = {r[0][0], r[0][1], r[0][2], r[0][3]};
	RECT R2 = {r[1][0], r[1][1], r[1][2], r[1][3]};
	RECT R3 = {r[2][0], r[2][1], r[2][2], r[2][3]};
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	_tcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	drawtext(_T("输入参数"), &R1, DT_CENTER | DT_VCENTER |
	         DT_SINGLELINE); //在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("运行"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("退出"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);

	outtextxy(30, 80, _T("目标位置为(0,0),云台偏航和俯仰目标角度为(0,0)"));
}

void sendData() {
	TCHAR tgt[30];
	_stprintf_s(tgt, _T("(%hd,%hd,%hd,%hd)，运行成功"), moveX, moveY,moveYAW,movePITCH);
	outtextxy(30, 100, tgt);
	//uint8_t temp_data;
    // 向串口写入数据（发送指令）
    for(int i=0;i<10;i++)
	{
		ctrl_move.st_data.x = moveX;
	    ctrl_move.st_data.y = moveY;
		ctrl_move.st_data.angle_yaw = moveYAW;
		ctrl_move.st_data.angle_pitch = movePITCH;
	    Frame_Send(0x01);
	}
}

 // 画图和发消息线程
DWORD WINAPI thread_mousemsg(LPVOID lpParameter) {
	init_figure();

	int event = 0;
	TCHAR s[60];//输入字符串变量
	MOUSEMSG m;//鼠标指针

	TCHAR car_data[40];  //车子信息字符串

	while (true) {
		if (MouseHit())
		{
			m = GetMouseMsg();//获取一条鼠标消息
			switch (m.uMsg) {
			case WM_MOUSEMOVE:
				setrop2(R2_XORPEN);
				setlinecolor(LIGHTCYAN);//线条颜色为亮青色
				setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
				setfillcolor(WHITE);//填充颜色为白色
				if (button_judge(m.x, m.y) != 0) {
					if (event != button_judge(m.x, m.y)) {
						event = button_judge(m.x, m.y); //记录这一次触发的按钮
						fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]); //有框填充矩形（X1,Y1,X2,Y2）
					}
				}
				else {
					if (event != 0) { //上次触发的按钮未被修正为原来的颜色
						fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]); //两次同或为原来颜色
						event = 0;
					}
				}
				break;
			case WM_LBUTTONDOWN:
				//按照按钮判断左键单击后的操作
				switch (button_judge(m.x, m.y)) {
					//复原按钮原型
				case 1:
					InputBox(s, 60, _T("请输入目标X、Y坐标和角度(X,Y,YAW,PITCH)"));
					_stscanf_s(s, _T("%hd,%hd,%hd,%hd"), &moveX, &moveY,&moveYAW,&movePITCH); //将输入字符串依次扫描到全局变量里面

					clearrectangle(30, 80, 400, 120);
					TCHAR tgt[60];
					_stprintf_s(tgt, _T("目标位置为(%hd,%hd),云台偏航角,俯仰角(%hd,%hd)"), moveX, moveY, moveYAW, movePITCH);
					outtextxy(30, 80, tgt);

					FlushMouseMsgBuffer();//单击事件后清空鼠标消息
					break;
				case 2:
					sendData();//发送数据
					FlushMouseMsgBuffer();//单击事件后清空鼠标消息
					break;
				case 3:
					closegraph();//关闭绘图环境
					exit(0);//正常退出
				default:
					//						printf("\r\n(%d,%d)",m.x,m.y);
					FlushMouseMsgBuffer();//单击事件后清空鼠标消息
					break;
				}
				break;
			}
		}
		_stprintf_s(car_data, _T("X:%hd,Y:%hd,YAW:%hd,PITCH:%hd"), car_dt.x, car_dt.y, car_dt.yaw, car_dt.pitch);
		outtextxy(530, 80, car_data);
		clearrectangle(530, 80, 800, 100);
		outtextxy(430, 80, _T("读取到数据:"));
	}
}
// 串口接收数据线程
DWORD WINAPI thread_serial_read(LPVOID lpParameter)
{
	if (serial_init() == FALSE)
	{
		return 1;
	}


	char rx_buffer[20] = { 0x00 };//输入数据缓存

	// 利用错误信息来获取进入串口缓冲区数据的字节数
	DWORD dwErrors;     // 错误信息
	COMSTAT Rcs;        // COMSTAT结构通信设备的当前信息
	int Len = 0;
	DWORD length = 20;               //用来接收读取的字节数
	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			rx_buffer[i] = 0;
		}

		ClearCommError(hSerial, &dwErrors, &Rcs);            // 获取读缓冲区数据长度
		Len = Rcs.cbInQue;
		ReadFile(hSerial, rx_buffer, Len, &length, NULL);   //获取字符串
		for (int i = 0; i < Len; i++)
		{
			// 串口读取数据（接收车子反馈数据）
			ANO_DT_GetOneByte(rx_buffer[i]);
		}
		PurgeComm(hSerial, PURGE_RXCLEAR);  //清空缓冲区
	}
	return 0;
}

int main() {
	// 创建两个线程
	HANDLE h_mouse_msg, h_serial_read;
	h_mouse_msg = CreateThread(NULL, 0, thread_mousemsg, NULL, 0, NULL);
	h_serial_read = CreateThread(NULL, 0, thread_serial_read, NULL, 0, NULL);

	while (1)
	{

	}
	CloseHandle(h_mouse_msg);
	CloseHandle(h_serial_read);

	return 0;
}

