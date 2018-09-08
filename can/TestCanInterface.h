#pragma once

#include "CanInterface.h"

class TestCanInterface : public CanInterface
{
public:
	void SimulateFrame(const can_frame_t& frame);
};