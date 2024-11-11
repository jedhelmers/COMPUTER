#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "lvgl.h"
#include "config.h"

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
