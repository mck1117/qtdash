#ifndef CanInterface_H
#define CanInterface_H

#include <cstdint>

typedef struct can_frame_e
{
    uint32_t id;
    uint8_t length;
    uint8_t data[8];
} can_frame_t;

class CanInterfaceCallbacks
{
	friend class CanInterface;

protected:
	virtual void OnFrameReceived(const can_frame_t& frame) = 0;
};

class CanInterface
{
private:
    CanInterfaceCallbacks* _callbacks = nullptr;
protected:
    virtual void OnFrameReceived(const can_frame_t& frame) final;
public:
    CanInterface();
    virtual void SetCallbacks(CanInterfaceCallbacks* callbacks) final;
};

#endif // CanInterface_H
