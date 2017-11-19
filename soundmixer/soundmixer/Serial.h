#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	Serial(char *portName);
	~Serial();

	int readSerial(char *buffer, unsigned int buf_size);
	bool writeSerial(char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H