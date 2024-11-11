#include <AA_MCP2515.h>
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
      config(CANBitrate::Config_8MHz_250kbps, CAN_PIN_CS, CAN_PIN_INT, SPI),
      CAN(config) {}

// Initialize the CAN interface
bool CANBus::begin() {
    while (CAN.begin(CANController::Mode::Loopback) != 0) {
        Serial.println("CAN initialization failed. Retrying...");
        delay(1000); // Retry delay
    }
    Serial.println("CAN initialization successful!");
    return true;
}


// Write a message to the CAN bus
bool CANBus::writeMessage(uint8_t const* data, size_t length) {
    if (length > 8) {
        Serial.println("Error: CAN data length exceeds 8 bytes.");
        return false; // CAN frames are limited to 8 bytes
    }

    CANFrame frame(canId, data, length);

    // Attempt to write the CAN frame
    CANController::IOResult result = CAN.write(frame);

    // Debug print for write result
    Serial.print("CAN.write result: ");
    switch (result) {
        case CANController::IOResult::OK:
            Serial.println("OK");
            frame.print("CAN TX"); // Successfully sent
            return true;
        case CANController::IOResult::FAIL:
            Serial.println("FAIL");
            break;
        case CANController::IOResult::NODATA:
            Serial.println("NODATA");
            break;
        case CANController::IOResult::NOBUFFER:
            Serial.println("NOBUFFER");
            break;
        case CANController::IOResult::TIMEOUT:
            Serial.println("TIMEOUT");
            break;
        default:
            Serial.println("UNKNOWN ERROR");
    }

    // If the write fails, print detailed error information
    Serial.println("Failed to send CAN message.");
    Serial.print("Data: ");
    for (size_t i = 0; i < length; i++) {
        Serial.print(data[i], HEX); // Print each byte in HEX format
        Serial.print(" ");
    }
    Serial.println();

    // Fetch and print detailed CAN controller errors
    CANErrors errors = CAN.getErrors();
    Serial.print("CAN Errors: ");
    errors.print();

    return false;
}


