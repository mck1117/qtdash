#pragma once

#include "TestCanInterface.h"

void TestCanInterface::SimulateFrame(const can_frame_t& frame)
{
	this->OnFrameReceived(frame);
}