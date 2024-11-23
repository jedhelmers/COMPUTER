#include "notification.h"
#include "styles.h"
#include "AppData.h"
#include "lvgl.h"


lv_obj_t * notification_obj;
lv_obj_t * notification_label;

void updateMessage() {
    if (AppData::getInstance().getMessage() != "") {
        lv_label_set_text_fmt(notification_label, AppData::getInstance().getMessage().c_str());
        lv_obj_clear_flag(notification_obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(notification_obj, LV_OBJ_FLAG_HIDDEN);
    }
}

void displayMessage(lv_obj_t* parent) {
    notification_obj = lv_obj_create(parent);
    lv_obj_set_pos(notification_obj, 0, 0);
    lv_obj_add_style(notification_obj, notification_style, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(notification_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_move_foreground(notification_obj);

    notification_label = lv_label_create(notification_obj);
    lv_obj_set_style_text_align(notification_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_pos(notification_label, 0, -6);
    lv_obj_add_style(notification_label, label_style_dark, LV_PART_MAIN);

    AppData::getInstance().addListener(updateMessage);
    updateMessage();
}
