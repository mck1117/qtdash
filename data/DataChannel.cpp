#include "DataChannel.h"

#include <sstream>
#include <iomanip>

DataChannel::DataChannel(const json& j, std::string name)
{
	this->_name = name;

	this->_friendlyName = JGetOrDefault<std::string>(j, "friendlyName", name);

	this->_id = JGetOrDefault<uint16_t>(j, "id", 0);
	this->_offset = JGetOrDefault<uint8_t>(j, "offset", 0);
	this->_length = JGetOrDefault<uint8_t>(j, "length", 1);
	this->_bigEndian = JGetOrDefault<bool>(j, "bigEndian", false);

	this->_precision = JGetOrDefault<int>(j, "precision", 0);

	this->_converter = Converter(j);
	this->_limits = Limits(j);
}

#define SWAP16(x) ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))
#define SWAP32(x) (SWAP16((x) & 0xFFFF) << 16 | SWAP16(((x) >> 16) & 0xFFFF))

void DataChannel::UpdateFromCanFrame(can_frame_t frame)
{
	// Check ID match
	if (frame.id != _id)
	{
		return;
	}

	// Check that there are enough bytes to read
	if (frame.length < _offset + _length)
	{
		return;
	}

	uint32_t rawValue;

	//
	//  WARNING: THIS CODE ONLY WORKS PROPERLY ON LITTLE ENDIAN CPUs
	//

	uintptr_t dataStart;
	uint16_t data16;
	
	switch (_length)
	{
	case 1:
		// Single byte is easy, just read it
		rawValue = frame.data[_offset];
		break;
	case 2:
		// Compute address of the first (lowest address) byte
		dataStart = reinterpret_cast<uintptr_t>(frame.data) + _offset;

		// Read
		data16 = *reinterpret_cast<uint16_t*>(dataStart);

		// If big endian, swap
		if (_bigEndian)
		{
			data16 = SWAP16(data16);
		}

		rawValue = data16;
		break;
	case 4:
		dataStart = reinterpret_cast<uintptr_t>(frame.data) + _offset;

		rawValue = *reinterpret_cast<uint32_t*>(dataStart);

		if (_bigEndian)
		{
			rawValue = SWAP32(rawValue);
		}

		break;
	}

	float convertedValue = _converter.Convert((float)rawValue);
	
	// Locked access to _value
	// Probably not necessary on CPU with atomic 32 bit read/write
	{
		std::lock_guard<std::mutex> lock(_mutex);
		this->_value = convertedValue;
	}
}

LimitResult DataChannel::GetLimitHits()
{
	return _limits.GetLimitResult(_value);
}

float DataChannel::GetValue()
{
	return this->_value;
}

std::string DataChannel::GetFormattedString()
{
	float valLocal;
	
	// This is probably only necessary when 32 bit
	// read/write isn't an atomic operation
	{
		std::lock_guard<std::mutex> lock(_mutex);
		valLocal = this->_value;
	}

	std::stringstream ss;

	ss << std::fixed << std::setprecision(this->_precision) << valLocal;

	return ss.str();
}
