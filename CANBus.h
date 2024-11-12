#ifndef CANBUS_H
#define CANBUS_H

#include "CAN.h"
#include "config.h"

class CANBus {
private:
    uint32_t canId;

    // Private constructor to prevent instantiation
    CANBus(uint32_t id);

    // Delete copy constructor and assignment operator
    CANBus(const CANBus&) = delete;
    CANBus& operator=(const CANBus&) = delete;

    // Internal write function
    bool _writeMessage(uint32_t id, uint8_t const* data, size_t length);

    mbed::CAN can1; // CAN object

public:
    // Static method to get the singleton instance
    static CANBus& getInstance(uint32_t id = 0x20);

    // Initialize the CAN interface
    bool begin();

    // Write a message to the CAN bus
    bool writeMessage(uint8_t const* data, size_t length);
    bool writeMessage(uint32_t id, uint8_t const* data, size_t length);

    // Optional: Add receive functionality
    void receive();
};

#endif
