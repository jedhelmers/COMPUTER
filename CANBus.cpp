#include "CANBus.h"

// Static method to get the singleton instance
CANBus& CANBus::getInstance(uint32_t id) {
    static CANBus instance(id); // Created only once
    return instance;
}

// Private constructor
CANBus::CANBus(uint32_t id) : canId(id) {}

// Initialize the CAN interface
bool CANBus::begin() {
    if (!CAN.begin(CanBitRate::BR_250k)) {
        Serial.println("CAN initialization failed");
        return false;
    }
    Serial.println("CAN initialized successfully");
    return true;
}

// Write a message to the CAN bus
bool CANBus::writeMessage(uint8_t const* data, size_t length) {
    CanMsg msg(CanStandardId(canId), length, data);
    int rc = CAN.write(msg);
    if (rc < 0) {
        Serial.print("CAN.write(...) failed with error code ");
        Serial.println(rc);
        return false;
    }
    Serial.print("Message sent: ");
    Serial.println(msg);
    return true;
}
