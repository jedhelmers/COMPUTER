#include "MainScreen.h"
#include "AppData.h"

lv_obj_t* mainLabel = nullptr;

void updateMainScreen() {
    if (mainLabel) {
        lv_label_set_text_fmt(mainLabel, "Counter: %d", AppData::getInstance().getCounter());
    }
}

void createMainScreen(lv_obj_t* parent) {
    if (!parent) {
        Serial.println("Parent screen is nullptr!");
        return;
    }

    Serial.println("Creating Main Screen...");
    mainLabel = lv_label_create(parent);
    lv_label_set_text(mainLabel, "Main Screen");
    lv_obj_align(mainLabel, LV_ALIGN_TOP_LEFT, 10, 10);

    AppData::getInstance().addListener(updateMainScreen);
    updateMainScreen();
}
