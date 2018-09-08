#include "CanInterface.h"

CanInterface::CanInterface()
{
    
}


void CanInterface::SetCallbacks(CanInterfaceCallbacks* callbacks) 
{   
    this->_callbacks = callbacks;
}

void CanInterface::OnFrameReceived(const can_frame_t& frame)
{
    if (nullptr != this->_callbacks)
    {
        this->_callbacks->OnFrameReceived(frame);
    }
}
