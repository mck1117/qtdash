#pragma once

#include "../config/JsonConfigured.h"

class Converter 
{
private:
    float _multiply, _divide, _add;

public:
    Converter();
    Converter(const json& j);

    float Convert(float value);
};
