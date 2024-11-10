#include "MainScreen.h"
#include "AppData.h"
#include "styles.h"
#include "config.h"

lv_obj_t *main_screen;
lv_obj_t *obj;
lv_obj_t *tank_1_label;
lv_obj_t *tank_2_label;
lv_obj_t *tank_1_gauge;
lv_obj_t *tank_2_gauge;
lv_obj_t *lat_long_label;
lv_obj_t *red_circle;
lv_obj_t *green_circle;
lv_obj_t *compass_img;
lv_obj_t *arrow_img;
lv_coord_t compass_original_w;
lv_coord_t compass_original_h;
lv_obj_t *menu_obj;

float gf99_value = 20;
float ppo2_value = 20;
char notification_buffer[50];
char buffer[10];
int direction = 40;
int tank_1_value = 40;

void updateMainScreen() {
    if (main_screen) {
        lv_label_set_text_fmt(tank_1_label, "%d", AppData::getInstance().getCounter());
        // lv_bar_set_value(tank_1_gauge, AppData::getInstance().getCounter(), LV_ANIM_ON);
        lv_bar_set_value(tank_1_gauge, (float)AppData::getInstance().getCounter() / TANK_MAX, LV_ANIM_ON);

        // Set angles for visual elements
        lv_img_set_angle(compass_img, AppData::getInstance().getHeading());
        lv_obj_set_style_transform_angle(red_circle, AppData::getInstance().getHeading(), 0);
        lv_obj_set_style_transform_angle(green_circle, AppData::getInstance().getHeading(), 0);
    }
}

void createMainScreen(lv_obj_t* screen) {
    if (!screen) {
        Serial.println("Parent screen is nullptr!");
        return;
    }

    main_screen = lv_obj_create(screen);
    // Outer grid (g_1): 2 columns, 1 row
    static lv_coord_t g_1_col_dsc[] = { 420 - BUTTON_WIDTH, 420 - BUTTON_WIDTH, BUTTON_WIDTH, LV_GRID_TEMPLATE_LAST };  // 2 columns
    static lv_coord_t g_1_row_dsc[] = { lv_pct(100), LV_GRID_TEMPLATE_LAST };  // 1 row
    lv_obj_set_grid_dsc_array(main_screen, g_1_col_dsc, g_1_row_dsc);
    lv_obj_set_size(main_screen, lv_pct(100), lv_pct(100));


    // Nested grid 1 (g_1_c_1): 1 column, 6 rows
    static lv_coord_t g_1_c_1_col_dsc[] = { LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };  // 1 column
    static lv_coord_t g_1_c_1_row_dsc[] = { ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, LV_GRID_TEMPLATE_LAST };  // 6 rows
    lv_obj_t* g_1_c_1 = lv_obj_create(main_screen);  // Attach to the first column of g_1
    lv_obj_set_grid_dsc_array(g_1_c_1, g_1_c_1_col_dsc, g_1_c_1_row_dsc);
    lv_obj_set_grid_cell(g_1_c_1, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);  // First column of g_1

    // Nested grid 2 (g_1_c_2): 2 columns, 6 rows
    static lv_coord_t g_1_c_2_col_dsc[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };  // 2 columns
    static lv_coord_t g_1_c_2_row_dsc[] = { ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, LV_GRID_TEMPLATE_LAST };  // 6 rows
    lv_obj_t* g_1_c_2 = lv_obj_create(main_screen);  // Attach to the second column of g_1
    lv_obj_set_grid_dsc_array(g_1_c_2, g_1_c_2_col_dsc, g_1_c_2_row_dsc);
    lv_obj_set_grid_cell(g_1_c_2, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);  // Second column of g_1


    // Buttons Nested grid 2 (g_1_c_3): 2 columns, 6 rows
    static lv_coord_t g_1_c_3_col_dsc[] = { BUTTON_WIDTH, LV_GRID_TEMPLATE_LAST };  // 2 columns
    static lv_coord_t g_1_c_3_row_dsc[] = { ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, ROW_HEIGHT, LV_GRID_TEMPLATE_LAST };  // 6 rows
    lv_obj_t* g_1_c_3 = lv_obj_create(main_screen);  // Attach to the second column of g_1
    lv_obj_set_grid_dsc_array(g_1_c_3, g_1_c_3_col_dsc, g_1_c_3_row_dsc);
    lv_obj_set_grid_cell(g_1_c_3, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 0, 1);  // Second column of g_1


    // Cells
    obj = lv_obj_create(g_1_c_1);  // Create a cell in g_1_c_1
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 4);

    lv_obj_t* obj2 = lv_obj_create(g_1_c_1);  // Create a cell in g_1_c_1
    lv_obj_set_grid_cell(obj2, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 4, 1);

    lv_obj_t* obj3 = lv_obj_create(g_1_c_1);
    lv_obj_set_grid_cell(obj3, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 5, 1);

    lv_obj_t* obj4 = lv_obj_create(g_1_c_2);
    lv_obj_set_grid_cell(obj4, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 0, 1);

    lv_obj_t* obj5 = lv_obj_create(g_1_c_2);
    lv_obj_set_grid_cell(obj5, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 4);

    lv_obj_t* obj6 = lv_obj_create(g_1_c_2);
    lv_obj_set_grid_cell(obj6, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 4);

    lv_obj_t* obj7 = lv_obj_create(g_1_c_2);
    lv_obj_set_grid_cell(obj7, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 5, 1);

    lv_obj_t* obj8 = lv_obj_create(g_1_c_2);
    lv_obj_set_grid_cell(obj8, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 5, 1);

    menu_obj = lv_obj_create(NULL);

    // Notification
    //   notification_obj = lv_obj_create(obj);
        // displayNotification(obj);


    // Buttons
    lv_obj_t* button_1 = lv_obj_create(g_1_c_3);
    lv_obj_set_grid_cell(button_1, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    lv_obj_t* button_2 = lv_obj_create(g_1_c_3);
    lv_obj_set_grid_cell(button_2, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 3, 1);

    lv_obj_t* button_3 = lv_obj_create(g_1_c_3);
    lv_obj_set_grid_cell(button_3, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 4, 1);

    lv_obj_t* button_4 = lv_obj_create(g_1_c_3);
    lv_obj_set_grid_cell(button_4, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 5, 1);

    //   lv_obj_set_pos(notification_obj, -14, -14);

    // Menu style
    lv_obj_set_pos(menu_obj, -14, -8);

    lv_obj_add_style(obj, compass_obj_style, LV_PART_MAIN);
    lv_obj_add_style(obj2, cell_style, LV_PART_MAIN);
    lv_obj_add_style(obj3, cell_style, LV_PART_MAIN);
    lv_obj_add_style(obj4, cell_style, LV_PART_MAIN);
    lv_obj_add_style(obj5, compass_obj_style, LV_PART_MAIN);
    lv_obj_add_style(obj6, compass_obj_style, LV_PART_MAIN);
    lv_obj_add_style(obj7, cell_style, LV_PART_MAIN);
    lv_obj_add_style(obj8, cell_style, LV_PART_MAIN);
    //   lv_obj_add_style(notification_obj, notification_style, LV_PART_MAIN);
    lv_obj_add_style(menu_obj, menu_style, LV_PART_MAIN);
    

    // Screen style
    lv_obj_add_style(screen, screen_style, LV_PART_MAIN);
    lv_obj_add_style(screen, style_gradient, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(main_screen, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_1_c_1, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_1_c_2, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_1_c_3, 0, LV_PART_MAIN);


    // Button styles
    lv_obj_add_style(button_1, button_style, LV_PART_MAIN);
    lv_obj_add_style(button_2, button_style, LV_PART_MAIN);
    lv_obj_add_style(button_3, button_style, LV_PART_MAIN);
    lv_obj_add_style(button_4, button_style, LV_PART_MAIN);


    // Labels
    lv_obj_t* depth_label = lv_label_create(obj2);
    lv_label_set_text_fmt(depth_label, "Depth: %d", 2);
    lv_obj_add_style(depth_label, label_style, LV_PART_MAIN);

    lv_obj_t* time_label_1 = lv_label_create(obj2);
    lv_label_set_text_fmt(time_label_1, "Time: %d", 2);
    lv_obj_add_style(time_label_1, label_style, LV_PART_MAIN);
    lv_obj_set_pos(time_label_1, 220, 0);

    lv_obj_t* stop_label = lv_label_create(obj3);
    lv_label_set_text_fmt(stop_label, "Stop: %d", 3);
    lv_obj_add_style(stop_label, label_style, LV_PART_MAIN);

    lv_obj_t* time_label_2 = lv_label_create(obj3);
    lv_label_set_text_fmt(time_label_2, "Time: %d", 3);
    lv_obj_add_style(time_label_2, label_style, LV_PART_MAIN);
    lv_obj_set_pos(time_label_2, 220, 0);

    lv_obj_t* O2_He = lv_label_create(obj4);
    lv_label_set_text_fmt(O2_He, "O2/HE: %d", 3);
    lv_obj_add_style(O2_He, label_style, LV_PART_MAIN);

    lv_obj_t* O2_He_value = lv_label_create(obj4);
    snprintf(buffer, sizeof(buffer), "OC %d/%d", 19, 49);
    lv_label_set_text_fmt(O2_He_value, buffer);
    lv_obj_add_style(O2_He_value, label_style, LV_PART_MAIN);
    lv_obj_set_pos(O2_He_value, 220, 0);

    lv_obj_t* ppo2 = lv_label_create(obj7);
    snprintf(buffer, sizeof(buffer), "PPO2: %.2f", ppo2_value);
    lv_label_set_text_fmt(ppo2, buffer);
    lv_obj_add_style(ppo2, label_style, LV_PART_MAIN);

    lv_obj_t* gf99 = lv_label_create(obj8);
    snprintf(buffer, sizeof(buffer), "GF99: %.2f", gf99_value);
    lv_label_set_text_fmt(gf99, buffer);
    lv_obj_add_style(gf99, label_style, LV_PART_MAIN);

    lv_obj_t* tank_label_1 = lv_label_create(obj5);
    lv_label_set_text_fmt(tank_label_1, "Tank %d", 1);
    lv_obj_set_pos(tank_label_1, tank_1_value, 0);
    lv_obj_add_style(tank_label_1, label_style, LV_PART_MAIN);
    lv_obj_set_style_text_align(tank_label_1, LV_TEXT_ALIGN_CENTER, 0);

    lv_obj_t* tank_label_2 = lv_label_create(obj6);
    lv_label_set_text_fmt(tank_label_2, "Tank %d", 2);
    lv_obj_set_pos(tank_label_2, 40, 0);
    lv_obj_add_style(tank_label_2, label_style, LV_PART_MAIN);
    lv_obj_set_style_text_align(tank_label_2, LV_TEXT_ALIGN_CENTER, 0);

    //   notification_label = lv_label_create(notification_obj);
    //   lv_obj_set_style_text_align(notification_label, LV_TEXT_ALIGN_LEFT, 0);
    //   lv_obj_set_pos(notification_label, 0, -6);
    //   lv_obj_add_style(notification_label, label_style_dark, LV_PART_MAIN);


    // Red Dot
    red_circle = lv_obj_create(obj);
    lv_obj_set_size(red_circle, 20, 20);
    lv_obj_align(red_circle, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(red_circle, LV_RADIUS_CIRCLE, 0); // LV_RADIUS_CIRCLE
    lv_obj_set_style_bg_color(red_circle, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(red_circle, LV_OPA_COVER, 0);
    lv_obj_set_pos(red_circle, 40, 10);
    lv_obj_add_style(red_circle, no_border_style, LV_PART_MAIN);


    green_circle = lv_obj_create(obj);
    lv_obj_set_size(green_circle, 20, 20);
    lv_obj_align(green_circle, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(green_circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(green_circle, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_bg_opa(green_circle, LV_OPA_COVER, 0);
    lv_obj_set_pos(green_circle, 10, -10);
    lv_obj_add_style(green_circle, no_border_style, LV_PART_MAIN);

    // Add label styles
    lv_obj_add_style(depth_label, label_style, LV_PART_MAIN);
    lv_obj_add_style(time_label_1, label_style, LV_PART_MAIN);
    lv_obj_add_style(time_label_2, label_style, LV_PART_MAIN);
    lv_obj_add_style(stop_label, label_style, LV_PART_MAIN);

    // Grid styles
    lv_obj_set_style_pad_all(main_screen, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_all(main_screen, 0, LV_PART_MAIN);

    lv_obj_set_style_pad_all(g_1_c_1, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_right(g_1_c_1, 0, LV_PART_MAIN);

    lv_obj_set_style_pad_all(g_1_c_2, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_left(g_1_c_2, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(g_1_c_2, 0, LV_PART_MAIN);

    lv_obj_set_style_pad_all(g_1_c_3, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(g_1_c_3, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_right(g_1_c_3, 0, LV_PART_MAIN);

    lv_obj_set_style_border_width(g_1_c_1, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(g_1_c_2, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(g_1_c_3, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(main_screen, 0, LV_PART_MAIN);
    // lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    
    // Remove scrollbars
    lv_obj_set_scrollbar_mode(main_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(g_1_c_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(g_1_c_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(g_1_c_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(obj8, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(red_circle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(green_circle, LV_SCROLLBAR_MODE_OFF);
    //   lv_obj_set_scrollbar_mode(notification_obj, LV_SCROLLBAR_MODE_OFF);


    // Tank Gauge
    tank_1_gauge = lv_bar_create(obj5); 
    lv_obj_set_size(tank_1_gauge, 46, 144); // Width of 40 for a "fatter" bar and height of 200 for vertical
    lv_obj_align(tank_1_gauge, LV_ALIGN_CENTER, 0, 0); 
    lv_obj_set_style_radius(tank_1_gauge, 0, LV_PART_MAIN); // No rounding on main part
    lv_obj_set_style_radius(tank_1_gauge, 0, LV_PART_INDICATOR); // No rounding on filled part
    lv_obj_set_style_bg_opa(tank_1_gauge, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tank_1_gauge, lv_color_hex(0x00FF00), LV_PART_INDICATOR); // Green fill
    lv_bar_set_value(tank_1_gauge, 20, LV_ANIM_ON);
    lv_obj_set_pos(tank_1_gauge, 0, 10);


    // Tank Gauge
    tank_2_gauge = lv_bar_create(obj6); 
    lv_obj_set_size(tank_2_gauge, 46, 144); // Width of 40 for a "fatter" bar and height of 200 for vertical
    lv_obj_align(tank_2_gauge, LV_ALIGN_CENTER, 0, 0); 
    lv_obj_set_style_radius(tank_2_gauge, 0, LV_PART_MAIN); // No rounding on main part
    lv_obj_set_style_radius(tank_2_gauge, 0, LV_PART_INDICATOR); // No rounding on filled part
    lv_obj_set_style_bg_opa(tank_2_gauge, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tank_2_gauge, lv_color_hex(0x00FF00), LV_PART_INDICATOR); // Green fill
    lv_bar_set_value(tank_2_gauge, 30, LV_ANIM_ON);
    lv_obj_set_pos(tank_2_gauge, 0, 10);


    // Compass image
    LV_IMG_DECLARE(compass_w);
    compass_img = lv_img_create(obj);
    lv_img_set_src(compass_img, &compass_w);
    lv_obj_align(compass_img, LV_ALIGN_BOTTOM_MID, 0, 220);

    // Arrow image
    LV_IMG_DECLARE(needle);
    arrow_img = lv_img_create(obj);
    lv_img_set_src(arrow_img, &needle);
    lv_obj_align(arrow_img, LV_ALIGN_BOTTOM_MID, 0, 220);
    lv_obj_set_pos(arrow_img, 0, 100);


    // Set dots pos based on compass
    compass_original_h = lv_obj_get_height(compass_img);
    lv_coord_t compass_center_y = compass_original_h / 20;
    lv_obj_set_style_transform_pivot_y(red_circle, 170, 0);
    lv_obj_set_style_transform_pivot_y(green_circle, 170, 0);

    // Lat Long label
    lat_long_label = lv_label_create(obj);
    lv_label_set_text_fmt(lat_long_label, "39.7589° N, 84.1916° W");
    lv_obj_add_style(lat_long_label, label_style, LV_PART_MAIN);
    lv_obj_set_style_text_align(lat_long_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(lat_long_label, 40, 0);


    // Tank images 1
    LV_IMG_DECLARE(tank_top_w);
    lv_obj_t * tank_top_1_img = lv_img_create(obj5);
    lv_img_set_src(tank_top_1_img, &tank_top_w);
    lv_img_set_zoom(tank_top_1_img, 50);
    lv_obj_align(tank_top_1_img, LV_ALIGN_TOP_MID, 0, -49);

    LV_IMG_DECLARE(tank_mid_w);
    for (int i = 0; i < 35; i++) {
        lv_obj_t * tank_mid_1_img = lv_img_create(obj5);
        lv_img_set_src(tank_mid_1_img, &tank_mid_w);
        lv_img_set_zoom(tank_mid_1_img, 50);
        lv_obj_align(tank_mid_1_img, LV_ALIGN_TOP_MID, 0, i * 4 + 68);
    }

    LV_IMG_DECLARE(tank_bottom_w);
    lv_obj_t * tank_bottom_1_img = lv_img_create(obj5);
    lv_img_set_src(tank_bottom_1_img, &tank_bottom_w);
    lv_img_set_zoom(tank_bottom_1_img, 50);
    lv_obj_align(tank_bottom_1_img, LV_ALIGN_BOTTOM_MID, 0, -24);


    // Tank images 2
    lv_obj_t * tank_top_2_img = lv_img_create(obj6);
    lv_img_set_src(tank_top_2_img, &tank_top_w);
    lv_img_set_zoom(tank_top_2_img, 50);
    lv_obj_align(tank_top_2_img, LV_ALIGN_TOP_MID, 0, -49);

    LV_IMG_DECLARE(tank_mid_w);
    for (int i = 0; i < 35; i++) {
        lv_obj_t * tank_mid_2_img = lv_img_create(obj6);
        lv_img_set_src(tank_mid_2_img, &tank_mid_w);
        lv_img_set_zoom(tank_mid_2_img, 50);
        lv_obj_align(tank_mid_2_img, LV_ALIGN_TOP_MID, 0, i * 4 + 68);
    }

    LV_IMG_DECLARE(tank_bottom_w);
    lv_obj_t * tank_bottom_2_img = lv_img_create(obj6);
    lv_img_set_src(tank_bottom_2_img, &tank_bottom_w);
    lv_img_set_zoom(tank_bottom_2_img, 50);
    lv_obj_align(tank_bottom_2_img, LV_ALIGN_BOTTOM_MID, 0, -24);


    // Tank label
    tank_1_label = lv_label_create(obj5);
    lv_label_set_text_fmt(tank_1_label, "%d%", 20);
    lv_obj_add_style(tank_1_label, label_style, LV_PART_MAIN);
    lv_obj_set_pos(tank_1_label, 56, 234);
    lv_obj_set_style_text_align(tank_1_label, LV_TEXT_ALIGN_CENTER, 0);

    tank_2_label = lv_label_create(obj6);
    lv_label_set_text_fmt(tank_2_label, "%d%", 30);
    lv_obj_add_style(tank_2_label, label_style, LV_PART_MAIN);
    lv_obj_set_pos(tank_2_label, 56, 234);
    lv_obj_set_style_text_align(tank_2_label, LV_TEXT_ALIGN_CENTER, 0);


    // Extra
    //   lv_obj_move_foreground(notification_obj);

    // Deletion hook
    // lv_obj_add_event_cb(main_screen, on_main_delete, LV_EVENT_DELETE, NULL);

    AppData::getInstance().addListener(updateMainScreen);
    updateMainScreen();
}
