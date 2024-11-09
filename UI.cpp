#include "UI.h"
#include "AppData.h"

lv_obj_t* counterLabel;
lv_obj_t* messageLabel;

void updateUI() {
    lv_label_set_text_fmt(counterLabel, "Counter: %d", AppData::getInstance().getCounter());
    lv_label_set_text(messageLabel, AppData::getInstance().getMessage().c_str());
}

void createUI(lv_obj_t* parent) {
    counterLabel = lv_label_create(parent);
    lv_obj_align(counterLabel, LV_ALIGN_TOP_LEFT, 10, 10);

    messageLabel = lv_label_create(parent);
    lv_obj_align(messageLabel, LV_ALIGN_TOP_LEFT, 10, 40);

    AppData::getInstance().addListener(updateUI);
    updateUI();
}


lv_obj_t* counterLabel2;

void updateUI2() {
    lv_label_set_text_fmt(counterLabel2, "Counter: %d", AppData::getInstance().getCounter2());
}

void createDifferentUI(lv_obj_t* parent) {
    counterLabel2 = lv_label_create(parent);
    lv_obj_align(counterLabel2, LV_ALIGN_TOP_LEFT, 10, 70);

    AppData::getInstance().addListener(updateUI2);
    updateUI2();
}