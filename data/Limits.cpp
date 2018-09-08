#include "Limits.h"

Limit::Limit()
{
	this->_exists = false;
	this->_value = 0;
}

Limit::Limit(float value)
{
	this->_exists = true;
	this->_value = value;
}

bool Limit::Exists()
{
	return _exists;
}

float Limit::GetValue()
{
	return _value;
}

bool Limits::TestLt(Limit& l, float value)
{
    if(!l.Exists())
    {
        return false;
    }

    if(value < l.GetValue())
    {
        return true;
    }

    return false;
}

bool Limits::TestGt(Limit& l, float value)
{
    if(!l.Exists())
    {
        return false;
    }

    if(value > l.GetValue())
    {
        return true;
    }

    return false;
}

LimitResult Limits::GetLimitResult(float value)
{
    if(TestLt(_cautionLow, value))
    {
        return LimitResult::CautionLow;
    }
    else if (TestLt(_warningLow, value))
    {
        return LimitResult::WarningLow;
    }
    else if (TestGt(_cautionHigh, value))
    {
        return LimitResult::CautionHigh;
    }
    else if (TestGt(_warningHigh, value))
    {
        return LimitResult::WarningHigh;
    }

    return LimitResult::Normal;
}

Limits::Limits() { }

Limits::Limits(const json& j)
{
	try
	{
		json l = j.at("limits");

		_warningLow = JGet<Limit>(l, "warningLow");
		_warningHigh = JGet<Limit>(l, "warningHigh");
		_cautionLow = JGet<Limit>(l, "cautionLow");
		_cautionHigh = JGet<Limit>(l, "cautionHigh");
		_min = JGet<Limit>(l, "min");
		_max = JGet<Limit>(l, "max");
	}
	catch (...)
	{
		return;
	}
}

float Limits::GetMin()
{
	return _min.Exists() ? _min.GetValue() : 0.0f;
}

float Limits::GetMax()
{
	return _max.Exists() ? _max.GetValue() : 0.0f;
}
