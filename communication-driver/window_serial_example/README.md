# Window 下串口通信例程
## 1 编译环境
1. 平台：Visual Studio 2022
2. 语言：C/C++

## 1 使用方法
1. 在 `serial.c` 文件中将串口初始化函数的串口号替换成设备管理器中看到的串口号。
``` C
LPCWSTR portname = TEXT("COM6");//COM6替换成自己的串口号
```