#include "ThemeMenuScreen.h"
#include "styles.h"
#include "config.h"
#include "AppData.h"

lv_obj_t * themes_main;
lv_obj_t *themeMenuItems[6];

void updateSelectedThemeItem() {
    Serial.println("SANITY 0");
    if (AppData::getInstance().getCurrentScreen() == Screen::MENU && AppData::getInstance().getCurrentMenuScreen() == MenuScreen::THEMES && themes_main != nullptr) {
        Serial.println("SANITY 1");
        // Reset all select states
        for (int i = 0; i < ThemeStateNames.size(); i++) {
            lv_obj_clear_state(themeMenuItems[i], LV_STATE_CHECKED);
        }
        // // Apply the selected state and style to the current item
        lv_obj_add_state(themeMenuItems[AppData::getInstance().getSelectedTheme()], LV_STATE_CHECKED);

        Serial.println("SANITY 2");
        if (!AppData::getInstance().getSubmenuStatus()) {
            Serial.println("SANITY 3");
            lv_obj_add_style(themeMenuItems[AppData::getInstance().getSelectedTheme()], style_sub_selected, LV_STATE_CHECKED);
        } else {
            Serial.println("SANITY 4");
            lv_obj_remove_style(themeMenuItems[AppData::getInstance().getSelectedTheme()], style_sub_selected, LV_STATE_CHECKED);
        }
    }
}


void createThemeMenuScreen(lv_obj_t* parent) {
    themes_main = lv_label_create(parent);
    lv_obj_align(themes_main, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text(themes_main, "");
    lv_obj_add_style(themes_main, label_style, LV_PART_MAIN);
    lv_obj_set_size(themes_main, lv_pct(100), lv_pct(100));
    lv_obj_set_pos(themes_main, 0, 40);

    lv_obj_t * themeMenuItemsColumn = lv_obj_create(themes_main);
    lv_obj_set_size(themeMenuItemsColumn, 476, lv_pct(100));
    lv_obj_align(themeMenuItemsColumn, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(themeMenuItemsColumn, cell_style, LV_PART_MAIN);
    lv_obj_add_style(themeMenuItemsColumn, label_style, LV_PART_MAIN);
    lv_obj_set_pos(themes_main, 80, 40);
    lv_obj_set_style_pad_all(themeMenuItemsColumn, 0, 0);
    lv_obj_set_user_data(themeMenuItemsColumn, (void *)"themeMenuItemsColumn");

    // Menu items in Column 2 using ThemeStateNames
    for (int i = 0; i < ThemeStateNames.size(); i++) {
        themeMenuItems[i] = lv_label_create(themeMenuItemsColumn);
        lv_label_set_text(themeMenuItems[i], ThemeStateNames[i].c_str());
        lv_obj_align(themeMenuItems[i], LV_ALIGN_TOP_LEFT, 0, i * 40);
        lv_obj_set_size(themeMenuItems[i], lv_pct(100), 40);
        lv_obj_set_style_pad_all(themeMenuItems[i], 4, LV_PART_MAIN);
        lv_obj_add_style(themeMenuItems[i], row_style, LV_PART_MAIN);

        // Apply zebra striping
        lv_obj_add_style(themeMenuItems[i], i % 2 == 0 ? style_even : style_odd, 0);
        lv_obj_add_style(themeMenuItems[i], style_selected, LV_STATE_CHECKED);

        // if (data.selectedTheme == i) {
        //     lv_obj_add_style(themeMenuItems[i], style_sub_selected, LV_STATE_CHECKED);
        //     lv_obj_add_state(themeMenuItems[i], LV_STATE_CHECKED);
        // }
    }

    AppData::getInstance().addListener(updateSelectedThemeItem);
    updateSelectedThemeItem();
}


void themeSelectionHandler() {
    if (digitalRead(UP_BUTTON) == HIGH) {
        AppData::getInstance().setSelectedTheme(
            (AppData::getInstance().getSelectedTheme() + 1) % 4
        );
        Serial.println("UP Button Pressed");
        delay(200);
    }

    if (digitalRead(DOWN_BUTTON) == HIGH) {
        int _temp = (AppData::getInstance().getSelectedTheme() - 1) % 4;
        if (_temp < 0) _temp = 4;
        AppData::getInstance().setSelectedTheme(_temp);
        Serial.println("DOWN Button Pressed");
        delay(200);
    }
}