#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "lvgl.h"

enum class Screen {
    LOAD,
    MAIN,
    MENU,
    DEVICES
};

class ScreenManager {
public:
    static ScreenManager& getInstance() {
        static ScreenManager instance;
        return instance;
    }

    void switchTo(Screen newScreen);

    lv_obj_t * screen = lv_scr_act();
    Screen currentScreen = Screen::DEVICES;

private:
    ScreenManager() {}
};

#endif
