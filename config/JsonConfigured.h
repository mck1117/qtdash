#pragma once

#include <string>

#include "nlohmann\json.hpp"

using namespace nlohmann;

template <typename T>
T JGetOrDefault(const json& j, std::string name, T defaultValue);

template <typename T>
T JGet(const json& j, std::string name);
