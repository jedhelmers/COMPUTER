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

    mbed::CAN can1;

    enum MessageType {
        Message = 0x411,
        Tank1 = 0x221,
        Tank2 = 0x222,
        Name = 0xD010004,
        PPO2 = 0xD040004,
        CellsStat = 0xdca0004,
        Status = 0xdcb0004
    };

public:
    // Static method to get the singleton instance
    static CANBus& getInstance(uint32_t id = 0x20);

    // Initialize the CAN interface
    bool begin();

    // Write a message to the CAN bus
    bool writeMessage(uint8_t const* data, size_t length);
    bool writeMessage(uint32_t id, uint8_t const* data, size_t length);
    uint32_t bytesToInt(const uint8_t* data, size_t length);
    float bytesToFloatBigEndian(const uint8_t* data);
    float bytesToFloat(const uint8_t* data);
    int bigEndianByteArrayToInt(const unsigned char* byteArray, int size);

    // Optional: Add receive functionality
    void receive();

    bool readMessage(uint32_t& id, uint8_t* data, size_t& length);
};

#endif
