#include <Arduino.h>
#include "Arduino_H7_Video.h"
#include "AppData.h"
#include "styles.h"
#include "ScreenManager.h"
#include "SensorManager.h"
#include "CompassSensor.h"
#include "CANBus.h"


CompassSensor compassSensor;
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

void setup() {
    Serial.begin(9600);
    Display.begin();
    lv_init();
    init_styles();

    // Register the compass sensor with the SensorManager
    SensorManager& sensorManager = SensorManager::getInstance();
    sensorManager.addSensor(&compassSensor);

    // Initialize all sensors
    sensorManager.initializeSensors();

    // Initialize CAN
    // Access the singleton instance
    CANBus& canBus = CANBus::getInstance(0x20);

    if (!canBus.begin()) {
        while (true) {} // Halt on initialization failure
    }

    Serial.println("CAN bus initialized.");
}

void loop() {
    static int value = 0;

    // Poll sensors via the SensorManager
    SensorManager& sensorManager = SensorManager::getInstance();
    sensorManager.pollSensors();

    // Example: Access compass data
    // Serial.print("Heading: ");
    // Serial.println(compassSensor.getHeading());
    AppData::getInstance().setHeading(compassSensor.getHeading() * 10);

    // Simulate data changes
    AppData::getInstance().setCounter(value++);

    if (millis() < 5000) {
      ScreenManager::getInstance().switchTo(Screen::LOAD);
    } else if (millis() > 10000 && millis() < 15000) {
      ScreenManager::getInstance().switchTo(Screen::MENU);
    } else if (millis() > 5000 && millis() < 10000) {
      ScreenManager::getInstance().switchTo(Screen::DEVICES);
    } else {
      ScreenManager::getInstance().switchTo(Screen::MAIN);
    }

    // Allow LVGL to handle tasks
    lv_task_handler();
    delay(1000);

    static uint32_t msg_cnt = 0;

    uint8_t msg_data[] = {0xCA, 0xFE, 0, 0, 0, 0, 0, 0};
    memcpy(&msg_data[4], &msg_cnt, sizeof(msg_cnt));

    // Use the singleton instance to send a message
    CANBus::getInstance().writeMessage(msg_data, sizeof(msg_data));

    msg_cnt++;
}
