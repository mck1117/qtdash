#pragma once

#include "../config/JsonConfigured.h"

typedef enum e_LimitResult
{
    CautionLow,
    WarningLow,
    Normal,
    WarningHigh,
    CautionHigh,
} LimitResult;

class Limit
{
private:
    float _value;
    bool _exists;

public:
	Limit();
	Limit(float value);

    bool Exists();
    float GetValue();
};

class Limits
{
private:
    Limit _min;
    Limit _max;
    Limit _warningLow;
    Limit _warningHigh;
    Limit _cautionLow;
    Limit _cautionHigh;


    bool TestLt(Limit& l, float value);
    bool TestGt(Limit& l, float value);
public:
	Limits();
	Limits(const json& j);

    LimitResult GetLimitResult(float value);

	float GetMin();
	float GetMax();
};
