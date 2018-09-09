#include "ChannelProcessor.h"

#include "DataChannel.h"

#include "Logger.h"

ChannelProcessor::ChannelProcessor(const nlohmann::json& j)
{
	json channels = j["channels"];

	for (auto it = channels.begin(); it != channels.end(); it++)
	{
		// Fetch key and value from iterator
		auto k = it.key();
		auto v = it.value();

		// Create a channel, add it
		DataChannel* d = new DataChannel(v, k);
		AddDataChannel(*d);
		
		Logger::Log("Added channel: ");
		Logger::Log(k);
	}
}

void ChannelProcessor::AddDataChannel(DataChannel& channel)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_channelLookupId.insert(std::make_pair(channel._id, &channel));

	_channelLookupName[channel._name] = &channel;
}
DataChannel* ChannelProcessor::GetChannel(std::string const& name)
{
	return _channelLookupName[name];
}

void ChannelProcessor::AddCanInterface(CanInterface& iface)
{
	iface.SetCallbacks(this);
}

void ChannelProcessor::OnFrameReceived(const can_frame_t& frame)
{
	// This needs a lock because multiple CAN interfaces might be active
	// and potentially try to hit us at the same time
	std::lock_guard<std::mutex> lock(_mutex);

	// Grab an iterator for all frames that match this id
	// (get everyone who cares)
	auto result = _channelLookupId.equal_range(frame.id);

	// Loop thru, and process frame for each data channel
	for (auto it = result.first; it != result.second; it++)
	{
		it->second->UpdateFromCanFrame(frame);
	}
}
