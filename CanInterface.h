#ifndef CanInterface_H
#define CanInterface_H

#include <cstdint>

typedef struct can_frame_e
{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_frame_t;

typedef struct CanInterfaceCallbacks
{
    void (*OnFrameReceived)(can_frame_t frame);
} CanInterfaceCallbacks_t;

class CanInterface
{
private:
    CanInterfaceCallbacks_t* _callbacks = nullptr;
protected:
    virtual void OnFrameReceived(can_frame_t frame) final;
public:
    CanInterface();
    virtual void SetCallbacks(CanInterfaceCallbacks_t* callbacks) final;
};

#endif // CanInterface_H
