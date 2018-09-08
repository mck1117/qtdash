#include "JsonConfigured.h"

#include "../data/Limits.h"

template<typename T>
T JGetOrDefault(const json& j, std::string name, T defaultValue)
{
	try
	{
		return j.at(name);
	}
	catch (...)
	{
		return defaultValue;
	}
}

template<>
Limit JGet(const json& j, std::string name)
{
	Limit l;

	try
	{
		float value = j.at(name);
		//float value = j[name];

		l = Limit(value);
	}
	catch (...)
	{
	}

	return l;
}

template int JGetOrDefault(const json& j, std::string name, int defaultValue);
template float JGetOrDefault(const json& j, std::string name, float defaultValue);
template uint32_t JGetOrDefault(const json& j, std::string name, uint32_t defaultValue);
template uint16_t JGetOrDefault(const json& j, std::string name, uint16_t defaultValue);
template uint8_t JGetOrDefault(const json& j, std::string name, uint8_t defaultValue);
template bool JGetOrDefault(const json& j, std::string name, bool defaultValue);
template std::string JGetOrDefault(const json& j, std::string name, std::string defaultValue);
