#include "ScreenManager.h"
#include "MainScreen.h"
#include "MenuScreen.h"
#include "DevicesScreen.h"
#include <Arduino.h>

void ScreenManager::switchTo(Screen newScreen) {
    if (newScreen != currentScreen) {
        Serial.println("Switching screen...");

        switch (newScreen) {
            case Screen::MAIN:
                currentScreen = Screen::MAIN;
                Serial.println("Loading MAIN screen...");
                lv_obj_clean(screen);
                createMainScreen(screen);
                break;
            case Screen::MENU:
                currentScreen = Screen::MENU;
                Serial.println("Loading MENU screen...");
                lv_obj_clean(screen);
                createMenuScreen(screen);
                break;
            case Screen::DEVICES:
                currentScreen = Screen::DEVICES;
                Serial.println("Loading DEVICES screen...");
                lv_obj_clean(screen);
                createDevicesScreen(screen);
                break;
            default:
                Serial.println("DEFAULT");
        }
        
        Serial.println("Screen switch complete.");
    }
}
