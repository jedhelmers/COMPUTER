#ifndef CANBUS_H
#define CANBUS_H

#include <Arduino_CAN.h>

class CANBus {
private:
    uint32_t canId;

    // Private constructor to prevent instantiation
    CANBus(uint32_t id);

    // Delete copy constructor and assignment operator
    CANBus(const CANBus&) = delete;
    CANBus& operator=(const CANBus&) = delete;

public:
    // Method to get the singleton instance
    static CANBus& getInstance(uint32_t id = 0x20); // Default CAN ID

    // Initialize the CAN interface
    bool begin();

    // Write a message to the CAN bus
    bool writeMessage(uint8_t const* data, size_t length);
};

#endif
