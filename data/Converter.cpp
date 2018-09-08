#include "Converter.h"

Converter::Converter()
{
    // Default to identity conversion
    _multiply = 1.0f;
    _divide = 1.0f;
    _add = 0.0f;
}

Converter::Converter(const json& j)
{
	try
	{
		json c = j.at("converter");
		//json c = j["converter"];

		_multiply = JGetOrDefault<float>(c, "multiply", 1);
		_divide = JGetOrDefault<float>(c, "divide", 1);
		_add = JGetOrDefault<float>(c, "add", 0);
	}
	catch (...)
	{
		return;
	}

   
}

float Converter::Convert(float value)
{
    return value * this->_multiply / this->_divide + this->_add;
}