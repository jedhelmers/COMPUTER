#include <Arduino.h>
#include "Arduino_H7_Video.h"
#include "AppData.h"
#include "ScreenManager.h"


Arduino_H7_Video Display(800, 480, GigaDisplayShield);

void setup() {
    Serial.begin(9600);
    Display.begin();
    lv_init();

    // Initialize the first screen
    ScreenManager::getInstance().switchTo(Screen::MAIN);
}


void loop() {
    static int value = 0;

    // Simulate data changes
    AppData::getInstance().setCounter(value++);
    delay(100);
    // Serial.println("Hi");

    if (millis() > 10000 && millis() < 15000) {
      ScreenManager::getInstance().switchTo(Screen::MENU);
    } else if (millis() > 5000 && millis() < 10000) {
      ScreenManager::getInstance().switchTo(Screen::DEVICES);
    } else {
      ScreenManager::getInstance().switchTo(Screen::MAIN);
    }

    // Allow LVGL to handle tasks
    lv_task_handler();
}
