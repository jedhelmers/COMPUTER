#include <Arduino.h>
#include "Arduino_H7_Video.h"
#include "AppData.h"
#include "styles.h"
#include "ScreenManager.h"
#include "SensorManager.h"
#include "CompassSensor.h"
#include "CANBus.h"


static const uint32_t CAN_ID = 0x19;
CANBus canBus(CAN_ID);
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
    delay(100);
}
