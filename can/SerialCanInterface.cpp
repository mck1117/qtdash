#include "SerialCanInterface.h"

#ifdef WIN32
#include <Windows.h>
#else

#endif

SerialCanInterface::SerialCanInterface(nlohmann::json& j)
{
	this->_portName = j["port"];
	this->_baud = j["baudrate"];

	_rxThread = new std::thread(SerialCanInterface::StaticRxThread, this);
}


struct SerialPortRef
{
#ifdef WIN32
	HANDLE handle;
#else
	int sp;
#endif
};





SerialPortRef SerialPortInit(std::string portName, int baud)
{
#ifdef WIN32
	HANDLE hSerial = CreateFileA(portName.c_str(),
						GENERIC_READ | GENERIC_WRITE,
						0,
						0,
						OPEN_EXISTING,
						0,
						0);

	if (hSerial == INVALID_HANDLE_VALUE)
	{
		DWORD e = GetLastError();
		printf("Problem opening serial port, %d\n", e);


		return { INVALID_HANDLE_VALUE };
	}

	DCB dcb = { 0 };

	bool result = GetCommState(hSerial, &dcb);

	dcb.BaudRate = baud;
	
	// 8N1
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = ONESTOPBIT;

	result = SetCommState(hSerial, &dcb);

	SerialPortRef r;
	r.handle = hSerial;
	return r;
#else

#endif
}

void SerialPortRead(SerialPortRef sp, void* buffer, size_t length)
{
#if WIN32
	DWORD bytesRead = 0;
	OVERLAPPED ovRead;

	
	bool rfRet = ReadFile(sp.handle, buffer, length, &bytesRead, NULL);


#else

#endif
}


void SerialCanInterface::RxThread()
{
	SerialPortRef sp = SerialPortInit(this->_portName, 115200);

	while (1)
	{
		uint8_t buffer[32];
		SerialPortRead(sp, buffer, 32);


	}
}