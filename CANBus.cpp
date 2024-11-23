#include <Arduino.h>
#include "AppData.h"
#include "CANBus.h"
#include "config.h"
#include <algorithm>
#include <cstring>
#include <string>

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
    // Set CAN frequency to 1 Mbps
    if (can1.frequency(250000)) {
        Serial.println("CAN frequency set to 1 Mbps.");

        // Reset the CAN controller to ensure it's in a known state
        // can1.reset();

        // Directly set loopback mode via register access (if needed)
        // Assuming your platform requires additional steps, you might need specific instructions here.
        // Uncomment and modify as necessary:
        // can1.MODE_REGISTER = (current_value & mask) | loopback_value;

        Serial.println("CAN initialized in loopback mode successfully!");
        can1.mode(mbed::CAN::Normal);

        return true;
    } else {
        Serial.println("Failed to set CAN frequency.");
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
    // mbed::CANMessage message(0x20, data, length, mbed::CANData, mbed::CANStandard);


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

uint32_t CANBus::bytesToInt(const uint8_t* data, size_t length) {
    uint32_t result = 0;

    // Assuming big-endian byte order
    for (size_t i = 0; i < length; i++) {
        result = (result << 8) | data[i];
    }

    return result;
}

int CANBus::bigEndianByteArrayToInt(const unsigned char* byteArray, int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result = (result << 8) | byteArray[i];
    }
    return result;
}

float CANBus::bytesToFloatBigEndian(const uint8_t* data) {
    double result;
    memcpy(&result, data, sizeof(result)); // Copy 8 bytes into a double
    return result;
}

float CANBus::bytesToFloat(const unsigned char* bytes) {
    float result;
    unsigned char* floatBytes = reinterpret_cast<unsigned char*>(&result);

    // Copy bytes in reverse order for big endian
    for (int i = 0; i < sizeof(float); ++i) {
        floatBytes[i] = bytes[sizeof(float) - 1 - i];
    }

    return result;
}


// Method to receive CAN messages
void CANBus::receive() {
    mbed::CANMessage msg;
    if (can1.read(msg)) {
        String dataString;
        float floatValue;

        switch(msg.id) {
            case MessageType::Message:
                Serial.print("Message received. ID: 0x");
                Serial.print(msg.id, HEX);
                // Serial.print(" Data: ");

                for (size_t i = 0; i < msg.len; i++) {
                    // Serial.print(msg.data[i], HEX);
                    // Serial.print(" ");
                    dataString += (char)msg.data[i];
                }

                AppData::getInstance().setMessage(dataString);
                Serial.println(AppData::getInstance().getMessage());
                break;
            case MessageType::Tank1:
                AppData::getInstance().setTank1(bigEndianByteArrayToInt(msg.data, 8));
                break;
            case MessageType::Tank2:
                AppData::getInstance().setTank2(bigEndianByteArrayToInt(msg.data, 8));
                break;
            default:
                dataString = "";
                AppData::getInstance().setMessage(dataString);
        }
    } else {
        // Serial.println("No CAN message available.");
    }
}

// Programmatic message reading
bool CANBus::readMessage(uint32_t& id, uint8_t* data, size_t& length) {
    mbed::CANMessage msg;
    if (can1.read(msg)) {
        id = msg.id;          // Extract the message ID
        length = msg.len;     // Extract the length
        memcpy(data, msg.data, length); // Copy the data payload
        return true;
    }
    return false;
}