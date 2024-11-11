#ifndef MENUSCREENMANAGER_H
#define MENUSCREENMANAGER_H

#include "lvgl.h"
#include "config.h"

class MenuScreenManager {
public:
    static MenuScreenManager& getInstance() {
        static MenuScreenManager instance;
        return instance;
    }

    void switchTo(lv_obj_t* screen, MenuScreen newMenuScreen);

    MenuScreen currentMenuScreen = MenuScreen::DEVICES;

private:
    MenuScreenManager() {}
};

#endif
