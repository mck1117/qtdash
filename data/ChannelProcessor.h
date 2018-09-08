#pragma once

#include <mutex>
#include <map>
#include <list>
#include <string>

#include "can/CanInterface.h"

#include "nlohmann\json.hpp"

class DataChannel;

class ChannelProcessor : public CanInterfaceCallbacks
{
private:
    std::multimap<uint16_t, DataChannel*> _channelLookupId;
    std::map<std::string, DataChannel*> _channelLookupName;
	
	void AddDataChannel(DataChannel& channel);

	std::mutex _mutex;
protected:
	virtual void OnFrameReceived(const can_frame_t& frame);
public:
    ChannelProcessor(const nlohmann::json& j);

	DataChannel* GetChannel(std::string const& name);

	void AddCanInterface(CanInterface& iface);
};
