#include <Arduino.h>
#include "CANBus.h"
#include "config.h"

// Static method to get the singleton instance
CANBus& CANBus::getInstance(uint32_t id) {
    static CANBus instance(id); // Created only once
    return instance;
}

// Private constructor
CANBus::CANBus(uint32_t id)
    : canId(id),
      can1(PB_5, PB_13) { // Initialize CAN with specified pins
}

// Initialize the CAN interface
bool CANBus::begin() {
    if (can1.frequency(1000000)) { // Set CAN frequency
        Serial.println("CAN initialized successfully!");
        return true;
    } else {
        Serial.println("Failed to initialize CAN.");
        return false;
    }
}

// Internal method to write a CAN message
bool CANBus::_writeMessage(uint32_t id, uint8_t const* data, size_t length) {
    if (length > 8) {
        Serial.println("Error: CAN data length exceeds 8 bytes.");
        return false;
    }

    mbed::CANMessage message(id, data, length);

    if (can1.write(message)) {
        Serial.print("Message sent successfully. ID: 0x");
        Serial.print(id, HEX);
        Serial.print(" Data: ");
        for (size_t i = 0; i < length; i++) {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        return true;
    } else {
        Serial.println("Failed to send CAN message.");
        Serial.print("Transmission error: ");
        Serial.println(can1.tderror());
        can1.reset();
        return false;
    }
}

// Public method to write a CAN message with the default ID
bool CANBus::writeMessage(uint8_t const* data, size_t length) {
    return CANBus::_writeMessage(CANBus::canId, data, length);
}

// Public method to write a CAN message with a specific ID
bool CANBus::writeMessage(uint32_t id, uint8_t const* data, size_t length) {
    return CANBus::_writeMessage(id, data, length);
}

// Method to receive CAN messages
void CANBus::receive() {
    mbed::CANMessage msg;
    if (can1.read(msg)) {
        Serial.print("Message received. ID: 0x");
        Serial.print(msg.id, HEX);
        Serial.print(" Data: ");
        for (size_t i = 0; i < msg.len; i++) {
            Serial.print(msg.data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        Serial.println("No CAN message available.");
    }
}
