#ifndef CANBUS_H
#define CANBUS_H

#include <Arduino_CAN.h>

class CANBus {
private:
    uint32_t canId;

public:
    // Constructor
    CANBus(uint32_t id);

    // Initialize the CAN interface
    bool begin();

    // Write a message to the CAN bus
    bool writeMessage(uint8_t const* data, size_t length);
};

#endif
