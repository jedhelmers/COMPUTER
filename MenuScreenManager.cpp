#include "MenuScreenManager.h"
#include "ThemeMenuScreen.h"
#include "DisplayMenuScreen.h"
#include "AppData.h"
#include <Arduino.h>

void MenuScreenManager::switchTo(lv_obj_t* screen, MenuScreen newScreen) {
    if (newScreen != currentMenuScreen) {
        Serial.println("Switching screen...");

        switch (newScreen) {
            case MenuScreen::THEMES:
                currentMenuScreen = MenuScreen::THEMES;
                Serial.println("Loading MENU THEMES screen...");
                lv_obj_clean(screen);
                createThemeMenuScreen(screen);
                break;
            case MenuScreen::DISPLAY_MENU:
                currentMenuScreen = MenuScreen::DISPLAY_MENU;
                Serial.println("Loading MENU DISPLAY screen...");
                lv_obj_clean(screen);
                createDisplayMenuScreen(screen);
                break;
            default:
                lv_obj_clean(screen);
                Serial.println("DEFAULT");
        }

        AppData::getInstance().setCurrentMenuScreen(currentMenuScreen);
        
        Serial.println("Screen switch complete.");
    }
}
