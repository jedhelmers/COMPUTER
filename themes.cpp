#include <Arduino.h>
#include "AppData.h"
#include "lvgl.h"
#include "config.h"
#include "styles.h"
#include "themes.h"
// #include "menu.h"

// Corresponding names for each MenuState
const std::array<std::string, 6> ThemeStateNames = {
   "DEFAULT", "DARK", "CRT", "OPS", "LIGHT", "DONUT"
};

ThemeState incrementTheme(ThemeState current) {
    // Increment and wrap around using modulus
    return static_cast<ThemeState>((current + 1) % ThemeStateNames.size());
}

ThemeState decrementTheme(ThemeState current) {
    // Decrement and wrap around
    return static_cast<ThemeState>((current - 1 + ThemeStateNames.size()) % ThemeStateNames.size());
}

int getThemeIndex(const char *labelText) {
    const std::array<std::string, 6> ThemeStateNames = {
        "DEFAULT", "DARK", "CRT", "OPS", "LIGHT", "DONUT"
    };

    // Loop through ThemeStateNames to find the matching index
    for (int i = 0; i < ThemeStateNames.size(); i++) {
        if (ThemeStateNames[i] == labelText) {
            return i;  // Return the index if it matches
        }
    }

    return -1;  // Return -1 if no match is found
}

lv_obj_t * theme_menu_items[6];


lv_obj_t * getThemes(lv_obj_t * parent) {
    // AppData& data = getAppData();

    lv_obj_t * themes_main = lv_label_create(parent);
    lv_obj_align(themes_main, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text(themes_main, "");
    lv_obj_add_style(themes_main, label_style, LV_PART_MAIN);
    lv_obj_set_size(themes_main, lv_pct(100), lv_pct(100));
    lv_obj_set_pos(themes_main, 0, 40);

    lv_obj_t * theme_menu_items_column = lv_obj_create(themes_main);
    lv_obj_set_size(theme_menu_items_column, 484, lv_pct(100));
    lv_obj_align(theme_menu_items_column, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(theme_menu_items_column, cell_style, LV_PART_MAIN);
    lv_obj_add_style(theme_menu_items_column, label_style, LV_PART_MAIN);
    lv_obj_set_pos(themes_main, 80, 40);
    lv_obj_set_style_pad_all(theme_menu_items_column, 0, 0);
    lv_obj_set_user_data(theme_menu_items_column, (void *)"theme_menu_items_column");

    // Menu items in Column 2 using ThemeStateNames
    for (int i = 0; i < ThemeStateNames.size(); i++) {
        theme_menu_items[i] = lv_label_create(theme_menu_items_column);
        lv_label_set_text(theme_menu_items[i], ThemeStateNames[i].c_str());
        lv_obj_align(theme_menu_items[i], LV_ALIGN_TOP_LEFT, 0, i * 40);
        lv_obj_set_size(theme_menu_items[i], lv_pct(100), 40);
        lv_obj_set_style_pad_all(theme_menu_items[i], 4, LV_PART_MAIN);
        lv_obj_add_style(theme_menu_items[i], row_style, LV_PART_MAIN);

        // Apply zebra striping
        lv_obj_add_style(theme_menu_items[i], i % 2 == 0 ? style_even : style_odd, 0);
        lv_obj_add_style(theme_menu_items[i], style_selected, LV_STATE_CHECKED);
        lv_obj_add_style(theme_menu_items[i], style_sub_selected, LV_STATE_CHECKED);

        // if (data.selectedTheme == i) {
        //     lv_obj_add_style(theme_menu_items[i], style_sub_selected, LV_STATE_CHECKED);
        //     lv_obj_add_state(theme_menu_items[i], LV_STATE_CHECKED);
        // }
    }

    return themes_main;
}
