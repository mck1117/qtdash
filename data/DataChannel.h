#pragma once

#include "../config/JsonConfigured.h"

#include <string>
#include <mutex>
#include "can/CanInterface.h"

#include "Converter.h"
#include "Limits.h"

#include "ChannelProcessor.h"

class DataChannel 
{
private:
	std::string _name;
	std::string _friendlyName;

	uint16_t _id;
	uint8_t _offset, _length;
	bool _bigEndian;

	int _precision;
	
	Converter _converter;
	Limits _limits;

	float _value;

	std::mutex _mutex;

	friend class ChannelProcessor;

	void UpdateFromCanFrame(can_frame_t frame);

    DataChannel(const json& j, std::string name);

public:
	DataChannel(const DataChannel&) = delete;
	DataChannel& operator =(const DataChannel&) = delete;

	float GetValue();
	LimitResult GetLimitHits();

	std::string GetFormattedString();
};
