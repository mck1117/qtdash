#include "SerialCanInterface.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>

#endif

#include <string>
#include <sstream>

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





SerialPortRef SerialPortInit(const std::string& portName, const int baud)
{
	SerialPortRef r;

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

	r.handle = hSerial;
	return r;
#else
	int port = open(portName.c_str(), O_RDWR | O_NOCTTY);




	r.sp = port;
#endif

	return r;
}

int SerialPortRead(const SerialPortRef sp, void* buffer, int length)
{
#if WIN32
	DWORD bytesRead = 0;

	bool rfRet = ReadFile(sp.handle, buffer, length, &bytesRead, NULL);

	return bytesRead;
#else
	return read(sp.sp, buffer, length);
#endif
}


std::stringstream ReadCanLine(const SerialPortRef sp)
{
	std::stringstream str;

	for (int charsRead = 0; charsRead != 35; )
	{
		charsRead = 0;

		// Reset stream if we had to retry
		str.str(std::string());

		for (char c = 0; c != '\n'; )
		{
			// Read a byte
			int bytesRead = SerialPortRead(sp, &c, 1);

			// If we didn't read a byte for some reason, don't append?
			if (!bytesRead)
			{
				continue;
			}

			// Append to stream
			str << c;

			charsRead++;
		}
	}

	return str;
}

static bool ParseLine(std::stringstream& line, can_frame_t* outFrame)
{
	std::string token;

	memset(outFrame, 0, sizeof(can_frame_t));

	try
	{
		std::getline(line, token, '_');
		outFrame->id = std::stoul(token, nullptr, 16);

		std::getline(line, token, '_');
		outFrame->length = std::stoul(token, nullptr, 16);

		// not possible!
		if (outFrame->length > 8)
		{
			memset(outFrame, 0, sizeof(can_frame_t));
			return false;
		}

		for (int i = 0; i < outFrame->length; i++)
		{
			std::getline(line, token, '_');
			outFrame->data[i] = std::stoul(token, nullptr, 16);
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}

void SerialCanInterface::RxThread()
{
	SerialPortRef sp = SerialPortInit(this->_portName, 115200);
	
	uint8_t buffer[32];

	while (1)
	{
		std::stringstream line = ReadCanLine(sp);

		OutputDebugStringA(line.str().c_str());

		can_frame_t frame;

		if (ParseLine(line, &frame))
		{
			this->OnFrameReceived(frame);
		}
	}
}