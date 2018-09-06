#include "CanInterface.h"

CanInterface::CanInterface()
{

}


void CanInterface::SetCallbacks(CanInterfaceCallbacks_t* callbacks) 
{   
    this->_callbacks = callbacks;
}

void CanInterface::OnFrameReceived(can_frame_t frame)
{
    if (nullptr != this->_callbacks
        && nullptr != this->_callbacks->OnFrameReceived)
    {
        this->_callbacks->OnFrameReceived(frame);
    }
}
