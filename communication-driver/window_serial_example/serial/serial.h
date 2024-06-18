#pragma once
#include <windows.h>

extern HANDLE hSerial;

BOOL serial_init(void);
BOOL serial_write(char* write_buffer, DWORD num_to_write);
BOOL serial_read(char* read_buffer, DWORD num_to_read);
void serial_close(void);
