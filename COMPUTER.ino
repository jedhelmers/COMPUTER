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
    Serial.begin(115200);
    while (!Serial) {}

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
        Serial.println("CAN bus initializing...");
        while (true) {} // Halt on initialization failure
    }

    Serial.println("CAN bus initialized.");
}

void loop() {
    static int value = 0;
    static uint32_t msg_cnt = 0;


    // Poll sensors via the SensorManager
    SensorManager& sensorManager = SensorManager::getInstance();
    sensorManager.pollSensors();

    // Example: Access compass data
    // Serial.print("Heading: ");
    // Serial.println(compassSensor.getHeading());
    AppData::getInstance().setHeading(compassSensor.getHeading() * 10);

    // Simulate data changes
    AppData::getInstance().setCounter(value++);

    // if (millis() < 5000) {
    //   // ScreenManager::getInstance().switchTo(Screen::LOAD);
    //   cnt++;
    //   // AppData::getInstance().setSelectedIndex(0);
    // } else if (millis() > 10000 && millis() < 15000) {
    //   // ScreenManager::getInstance().switchTo(Screen::MENU);
    //   cnt++;
    //   // AppData::getInstance().setSelectedIndex(1);
    // } else if (millis() > 5000 && millis() < 10000) {
    //   // ScreenManager::getInstance().switchTo(Screen::DEVICES);
    //   cnt++;
    //   // AppData::getInstance().setSelectedIndex(2);
    // } else {
    //   // ScreenManager::getInstance().switchTo(Screen::MAIN);
    //   cnt++;
    // }

    AppData::getInstance().setSelectedIndex(msg_cnt % 5);
    AppData::getInstance().setTank1(msg_cnt % 300);
    AppData::getInstance().setTank2((msg_cnt * 1.2) % 300);
    // ScreenManager::getInstance().switchTo(Screen::MENU);
    ScreenManager::getInstance().switchTo(Screen::MAIN);

    // Allow LVGL to handle tasks
    lv_task_handler();
    delay(1000);

    if (compassSensor.getHeading() > 330) {

      uint8_t msg_data[] = {0xCA, 0xFE, 0, 0, 0, 0, 0, 0};
      memcpy(&msg_data[4], &msg_cnt, sizeof(msg_cnt));

      // Use the singleton instance to send a message
      // CANBus::getInstance().writeMessage(msg_data, sizeof(msg_data));
      // Access the singleton instance
      CANBus& canBus = CANBus::getInstance();

      // Transmit a CAN message
      if (canBus.writeMessage(msg_data, sizeof(msg_data))) {
        Serial.println("Message sent successfully.");
      }
    }

    msg_cnt++;
}
