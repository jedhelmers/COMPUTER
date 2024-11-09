#include "MenuScreen.h"
#include "ScreenManager.h"

void createMenuScreen(lv_obj_t* parent) {
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, "Menu Screen");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, 10);

    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t* btnLabel = lv_label_create(btn);
    lv_label_set_text(btnLabel, "Go to Devices");

    lv_obj_add_event_cb(btn, [](lv_event_t* e) {
        ScreenManager::getInstance().switchTo(Screen::DEVICES);
    }, LV_EVENT_CLICKED, nullptr);
}
