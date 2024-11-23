#include <Arduino.h>
#include "Arduino_H7_Video.h"
#include "AppData.h"
#include "styles.h"
#include "ScreenManager.h"
#include "SensorManager.h"
#include "CompassSensor.h"
#include "MenuScreen.h"
#include "CANBus.h"


CompassSensor compassSensor;
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

void setup() {
  pinMode(MENU_BUTTON, INPUT_PULLDOWN);
  pinMode(UP_BUTTON, INPUT_PULLDOWN);
  pinMode(SELECT_BUTTON, INPUT_PULLDOWN);
  pinMode(DOWN_BUTTON, INPUT_PULLDOWN);

  Serial.begin(115200);
  // while (!Serial) {}

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
  CANBus& canBus = CANBus::getInstance(0xf7);

  if (!canBus.begin()) {
    Serial.println("CAN bus initializing...");
    while (true) {}  // Halt on initialization failure
  }

  Serial.println("CAN bus initialized.");


  uint8_t msg_data[] = { 0xCA, 0xFE, 0, 0, 0, 0, 0, 0 };

  // Transmit a CAN message
  canBus.writeMessage(0x20, msg_data, sizeof(msg_data));
}

void loop() {
  static int value = 0;
  static uint32_t msg_cnt = 0;

  if (digitalRead(MENU_BUTTON) == HIGH) {
    AppData::getInstance().setSubmenuStatus(false);

    if (AppData::getInstance().getCurrentScreen() != Screen::MENU) {
      ScreenManager::getInstance().switchTo(Screen::MENU);
    } else {
      ScreenManager::getInstance().switchTo(Screen::MAIN);
    }

    delay(200);
  }

  // Define buttons per screen
  switch (AppData::getInstance().getCurrentScreen())
  {
  case Screen::MENU:
    setMenuActions();
    break;
  
  default:
    break;
  }

  // Poll sensors via the SensorManager
  SensorManager& sensorManager = SensorManager::getInstance();
  sensorManager.pollSensors();

  // Example: Access compass data
  // Serial.print("Heading: ");
  // Serial.println(compassSensor.getHeading());
  AppData::getInstance().setHeading(compassSensor.getHeading() * 10);

  // Simulate data changes
  // AppData::getInstance().setCounter(value++);

  if (millis() < 3000) {
    ScreenManager::getInstance().switchTo(Screen::LOAD);
    // AppData::getInstance().setSelectedIndex(0);
  } else if (millis() > 10000 && millis() < 15000) {
    // ScreenManager::getInstance().switchTo(Screen::MENU);
    // AppData::getInstance().setSelectedIndex(1);
  } else if (millis() > 3000 && millis() < 4000) {
    ScreenManager::getInstance().switchTo(Screen::MAIN);
    // AppData::getInstance().setSelectedIndex(2);
  } else {
    // ScreenManager::getInstance().switchTo(Screen::MAIN);
  }

  // AppData::getInstance().setSelectedIndex(msg_cnt % 5);
  // AppData::getInstance().setTank1(msg_cnt % 100);
  // AppData::getInstance().setTank2((msg_cnt / 3) % 100);
  // ScreenManager::getInstance().switchTo(Screen::MENU);
  // ScreenManager::getInstance().switchTo(Screen::MAIN);

  CANBus& canBus = CANBus::getInstance();

  // if (compassSensor.getHeading() > 330) {
  //   Serial.println(compassSensor.getHeading());

  //   uint8_t msg_data[] = { 0xCA, 0xFE, 0, 0, 0, 0, 0, 0 };
  //   memcpy(&msg_data[4], &msg_cnt, sizeof(msg_cnt));

  //   // Use the singleton instance to send a message
  //   // CANBus::getInstance().writeMessage(msg_data, sizeof(msg_data));
  //   // Access the singleton instance

  //   // Transmit a CAN message
  //   // if (canBus.writeMessage(0x200, msg_data, sizeof(msg_data))) {
  //   //   Serial.println("Message sent successfully.");
  //   // }
  // }

  uint32_t messageId;
  uint8_t receivedData[8];  // Maximum CAN frame size is 8 bytes
  size_t dataLength;

  // Attempt to read a message from the CAN bus
  // if (canBus.readMessage(messageId, receivedData, dataLength)) {
  //   // Message received successfully
  //   Serial.print("Message received. ID: 0x");
  //   Serial.print(messageId, HEX);
  //   Serial.print(" Length: ");
  //   Serial.print(dataLength);
  //   Serial.print(" Data: ");
  //   for (size_t i = 0; i < dataLength; i++) {
  //     Serial.print(receivedData[i], HEX);
  //     Serial.print(" ");
  //   }
  //   Serial.println();
  // } else {
  //   // No message available
  //   // Serial.println("No CAN message available.");
  // }

  canBus.receive();

  msg_cnt++;

  // Allow LVGL to handle tasks
  lv_task_handler();
  delay(10);
}
