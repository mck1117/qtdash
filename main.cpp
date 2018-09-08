#include "mainwindow.h"
#include <QApplication>

#include <fstream>

#include "Logger.h"
#include "data/ChannelProcessor.h"
#include "data/DataChannel.h"
#include "nlohmann\json.hpp"
#include "can/TestCanInterface.h"
#include "can/SerialCanInterface.h"

static CanInterface* canInterface;
static ChannelProcessor* channelProcessor;

int main(int argc, char *argv[])
{
	nlohmann::json j;

	{
		std::ifstream jfile("config.json");
		jfile >> j;
	}
		
	channelProcessor = new ChannelProcessor(j);

	json caniface = j["interface"];
	std::string ifaceName = caniface["type"];

	json ifaceConfig = caniface["config"];

	if (0 == ifaceName.compare("serial"))
	{
		canInterface = new SerialCanInterface(ifaceConfig);
		channelProcessor->AddCanInterface(*canInterface);
	}

	DataChannel* clt = channelProcessor->GetChannel("CLT");
	DataChannel* iat = channelProcessor->GetChannel("IAT");

	can_frame_t frame;

	frame.id = 135;
	frame.length = 8;
	frame.data[0] = 0x01;
	frame.data[1] = 0x02;
	frame.data[2] = 0x03;
	frame.data[3] = 0x04;
	frame.data[4] = 0x05;
	frame.data[5] = 0x06;
	frame.data[6] = 0x07;
	frame.data[7] = 0x08;

	//Logger::Log(d.GetFormattedString());

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
