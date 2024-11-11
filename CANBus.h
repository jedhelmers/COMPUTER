#ifndef CANBUS_H
#define CANBUS_H

#include <AA_MCP2515.h>
#include "config.h"

class CANBus {
private:
    uint32_t canId;

    // CAN Configuration and Controller
    CANConfig config;
    CANController CAN;

    // Private constructor to prevent instantiation
    CANBus(uint32_t id);

    // Delete copy constructor and assignment operator
    CANBus(const CANBus&) = delete;
    CANBus& operator=(const CANBus&) = delete;
    bool _writeMessage(uint32_t id, uint8_t const* data, size_t length);

public:
    // Get the singleton instance
    static CANBus& getInstance(uint32_t id = 0x20);

    // Initialize the CAN interface
    bool begin();

    // Write a message to the CAN bus
    bool writeMessage(uint8_t const* data, size_t length);
    bool writeMessage(uint32_t id, uint8_t const* data, size_t length);
};

#endif
