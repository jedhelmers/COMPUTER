#include "LoadScreen.h"
#include "AppData.h"

lv_obj_t* loadScreenLabel = nullptr;

void createLoadScreen(lv_obj_t* parent) {
    loadScreenLabel = lv_label_create(parent);
    lv_label_set_text(loadScreenLabel, "Load Screen");
    lv_obj_align(loadScreenLabel, LV_ALIGN_TOP_LEFT, 10, 10);
}
