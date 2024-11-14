#include "MenuScreen.h"
#include "ScreenManager.h"
#include "MenuScreenManager.h"
#include "AppData.h"
#include "styles.h"
#include "config.h"

lv_obj_t *menu;
lv_obj_t *body_content;
lv_obj_t *label_main;
lv_obj_t *menu_items_column;
lv_obj_t *menu_items[5];

void updateSelectedItem() {
    try {
        if (menu != nullptr && AppData::getInstance().getCurrentScreen() == Screen::MENU) {
            // Reset all select states
            for (int i = 0; i < MenuStateNames.size(); i++) {
                lv_obj_clear_state(menu_items[i], LV_STATE_CHECKED);
            }
            // Apply the selected state and style to the current item
            lv_obj_add_state(menu_items[AppData::getInstance().getSelectedIndex()], LV_STATE_CHECKED);
            lv_label_set_text(label_main, MenuStateNames[AppData::getInstance().getSelectedIndex()].c_str());

            // Submenu
            MenuScreenManager::getInstance().switchTo(body_content, static_cast<MenuScreen>(AppData::getInstance().getSelectedIndex()));

            if (AppData::getInstance().getSubmenuStatus()) {
                lv_obj_add_style(menu_items[AppData::getInstance().getSelectedIndex()], style_sub_selected, LV_STATE_CHECKED);
            } else {
                lv_obj_remove_style(menu_items[AppData::getInstance().getSelectedIndex()], style_sub_selected, LV_STATE_CHECKED);
            }

            // // SANITY CHECK
            // if (static_cast<MenuScreen>(AppData::getInstance().getSelectedIndex()) == MenuScreen::THEMES) {
            //     lv_obj_add_style(menu_items[AppData::getInstance().getSelectedIndex()], style_sub_selected, LV_STATE_CHECKED);
            //     AppData::getInstance().setSubmenuStatus(true);
            //     // Serial.println(AppData::getInstance().getSubmenuStatus());
            // }
        }
    } catch (const std::exception& e) {
        Serial.print("MENU Exception: ");
        Serial.println(e.what());
    }
}

void createMenuScreen(lv_obj_t* screen) {
    if (!screen) {
        Serial.println("Parent screen is nullptr!");
        return;
    }

    menu = lv_obj_create(screen);
    lv_obj_set_size(menu, lv_pct(100), lv_pct(100));
    lv_obj_add_style(menu, screen_style, LV_PART_MAIN);

    // Column 1
    lv_obj_t *body_column = lv_obj_create(menu);
    lv_obj_set_size(body_column, lv_pct(100), lv_pct(100));
    lv_obj_align(body_column, LV_ALIGN_TOP_LEFT, 0, 0);
    // lv_obj_add_style(body_column, screen_style, LV_PART_MAIN);
    lv_obj_set_style_pad_all(body_column, 0, LV_PART_MAIN);
    lv_obj_add_style(body_column, cell_style, LV_PART_MAIN);
    // lv_obj_add_style(body_column, compass_obj_style, LV_PART_MAIN);
    // lv_obj_add_style(body_column, no_borders_style, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(body_column, LV_SCROLLBAR_MODE_OFF);

    // Body content container to render submenu items
    body_content = lv_obj_create(body_column);
    lv_obj_set_size(body_content, lv_pct(100), lv_pct(100));
    lv_obj_align(body_content, LV_ALIGN_TOP_LEFT, 0, 0);
    // lv_obj_add_style(body_content, screen_style, LV_PART_MAIN);
    lv_obj_set_style_pad_all(body_content, 0, LV_PART_MAIN);
    lv_obj_add_style(body_content, cell_style, LV_PART_MAIN);
    // lv_obj_add_style(body_content, compass_obj_style, LV_PART_MAIN);
    // lv_obj_add_style(body_content, no_borders_style, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(body_content, LV_SCROLLBAR_MODE_OFF);

    // Column 2 for menu items
    menu_items_column = lv_obj_create(menu);
    lv_obj_set_size(menu_items_column, 200, lv_pct(100));
    lv_obj_align(menu_items_column, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_pad_all(menu_items_column, 0, LV_PART_MAIN);
    lv_obj_add_style(menu_items_column, cell_style, LV_PART_MAIN);
    lv_obj_add_style(menu_items_column, label_style, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(menu_items_column, LV_SCROLLBAR_MODE_OFF);

    // Label for Column 1
    label_main = lv_label_create(body_column);
    lv_label_set_text(label_main, "Select an item...");
    lv_obj_align(label_main, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_style(label_main, label_style, LV_PART_MAIN);
    lv_obj_add_style(label_main, row_style, LV_PART_MAIN);
    lv_obj_set_size(label_main, 562, 49);
    lv_obj_set_style_margin_all(label_main, 6, 0);

    // Menu items in Column 2
    for (int i = 0; i < MenuStateNames.size(); i++) {
        menu_items[i] = lv_label_create(menu_items_column);
        lv_label_set_text(menu_items[i], MenuStateNames[i].c_str());
        lv_obj_align(menu_items[i], LV_ALIGN_TOP_LEFT, 0, i * 40);
        lv_obj_set_style_pad_all(menu_items[i], 4, LV_PART_MAIN);
        lv_obj_add_style(menu_items[i], label_style, LV_PART_MAIN);

        // Apply zebra striping
        lv_obj_add_style(menu_items[i], i % 2 == 0 ? style_even : style_odd, 0);
        lv_obj_add_style(menu_items[i], style_selected, LV_STATE_CHECKED);
    }

    AppData::getInstance().addListener(updateSelectedItem);
    updateSelectedItem();
}

void setMenuActions() {
    if (digitalRead(UP_BUTTON) == HIGH) {
        if (!AppData::getInstance().getSubmenuStatus()) {
            AppData::getInstance().setSelectedIndex(
                (AppData::getInstance().getSelectedIndex() + 1) % 5
            );
        }
        Serial.println("UP Button Pressed");
        delay(200);
    }

    if (digitalRead(DOWN_BUTTON) == HIGH) {
        if (!AppData::getInstance().getSubmenuStatus()) {
            int _temp = (AppData::getInstance().getSelectedIndex() - 1) % 5;
            if (_temp < 0) _temp = 4;

            AppData::getInstance().setSelectedIndex(_temp);
        }
        Serial.println("DOWN Button Pressed");
        delay(200);
    }

    if (digitalRead(SELECT_BUTTON) == HIGH) {
        AppData::getInstance().setSubmenuStatus(!AppData::getInstance().getSubmenuStatus());
        Serial.println("SELECT Button Pressed");
        delay(200);
    }
}