#ifndef BEAGLEBONECANPROVIDER_H
#define BEAGLEBONECANPROVIDER_H

#include "CanInterface.h"

#include "nlohmann/json.hpp"

#include <thread>

class SerialCanInterface : public CanInterface
{
private:
	std::string _portName;
	int _baud;

	std::thread* _rxThread;

	static void StaticRxThread(SerialCanInterface* instance) { instance->RxThread(); }
	void RxThread();
public:
    SerialCanInterface(nlohmann::json& j);
};

#endif // BEAGLEBONECANPROVIDER_H
