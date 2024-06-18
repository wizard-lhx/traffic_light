#include "serial.h"
#include <stdio.h>

HANDLE hSerial;

// 串口初始化
BOOL serial_init(void)
{
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    // 打开串口
    LPCWSTR portname = TEXT("COM6");
    hSerial = CreateFile(portname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("无法打开串口\n");
        return 0;
    }

    // 配置串口参数
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("获取串口参数失败\n");
        CloseHandle(hSerial);
        return 0;
    }
    //printf("%u", dcbSerialParams.BaudRate);
    dcbSerialParams.BaudRate = 500000;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("配置串口参数失败\n");
        CloseHandle(hSerial);
        return 0;
    }

    // 配置串口超时时间
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("配置串口超时时间失败\n");
        CloseHandle(hSerial);
        return 0;
    }

    return 1;
}

BOOL serial_write(char* write_buffer, DWORD num_to_write)
{
    DWORD bytesWritten;
    if (!WriteFile(hSerial, write_buffer, num_to_write, &bytesWritten, NULL)) {
        printf("写入数据失败\n");
        CloseHandle(hSerial);
        return 0;
    }
    return 1;
}

BOOL serial_read(char* read_buffer, DWORD num_to_read)
{
    // 从串口读取数据
    DWORD bytesRead;
    if (!ReadFile(hSerial, read_buffer, num_to_read, &bytesRead, NULL)) {
        printf("读取数据失败\n");
        CloseHandle(hSerial);
        return 0;
    }
    return 1;
}

void serial_close()
{
    // 关闭串口
    CloseHandle(hSerial);
}
