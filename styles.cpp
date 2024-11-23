#include <Arduino.h>
#include "styles.h"
#include "config.h"
#include "AppData.h"
#include <stdlib.h>

lv_style_t * menu_style;
lv_style_t * cell_style;
lv_style_t * row_style;
lv_style_t * notification_style;
lv_style_t * no_border_style;
lv_style_t * no_borders_style;
lv_style_t * compass_obj_style;
lv_style_t * screen_style;
lv_style_t * button_style;
lv_style_t * label_style;
lv_style_t * label_style_dark;
lv_style_t * style_even;
lv_style_t * style_odd;
lv_style_t * style_selected;
lv_style_t * style_sub_selected;
lv_style_t * style_gradient;

// Update color settings based on the selected theme
// Set theme colors based on the selected theme
void setThemeColors() {
    // AppData& data = getAppData();

    // Use selectedTheme to update style properties
    // switch (data.selectedTheme) {
    //     case DEFAULT:
    //         lv_style_set_bg_color(menu_style, lv_color_make(15, 37, 76));
    //         lv_style_set_bg_color(cell_style, lv_color_make(255, 255, 255));
    //         lv_style_set_text_color(label_style, lv_color_make(255, 255, 255));
    //         lv_style_set_text_color(label_style, lv_color_make(255, 255, 255));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0x00FF00));
    //         lv_style_set_bg_color(style_gradient, lv_color_hex(0x2E404F));
    //         lv_style_set_bg_grad_color(style_gradient, lv_color_hex(0x13202B));
    //         break;

    //     case DARK:
    //         lv_style_set_bg_color(menu_style, lv_color_make(10, 10, 10));
    //         lv_style_set_bg_opa(menu_style, 240);
    //         lv_style_set_border_color(menu_style, lv_color_make(255, 255, 255));
    //         lv_style_set_bg_color(cell_style, lv_color_make(40, 40, 40));
    //         lv_style_set_text_color(label_style, lv_color_make(200, 200, 200));
    //         lv_style_set_text_color(label_style_dark, lv_color_make(20, 20, 20));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0x00FF00));
    //         lv_style_set_bg_color(style_even, lv_color_make(30, 30, 30));
    //         lv_style_set_bg_color(style_odd, lv_color_make(45, 45, 45));
    //         lv_style_set_bg_color(style_gradient, lv_color_make(40, 40, 40));
    //         lv_style_set_bg_grad_color(style_gradient, lv_color_make(10, 10, 10));
    //         break;

    //     case CRT:
    //         lv_style_set_bg_color(menu_style, lv_color_hex(0x005500));
    //         lv_style_set_bg_color(cell_style, lv_color_hex(0x002200));
    //         lv_style_set_text_color(label_style, lv_color_hex(0x00FF00));
    //         lv_style_set_text_color(label_style_dark, lv_color_hex(0xFF00FF));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0xFFFFFF));
    //         lv_style_set_bg_color(style_even, lv_color_hex(0x003300));
    //         lv_style_set_bg_color(style_odd, lv_color_hex(0x004400));
    //         break;

    //     case OPS:
    //         lv_style_set_bg_color(menu_style, lv_color_hex(0x2D2D30));
    //         lv_style_set_bg_opa(menu_style, 230);
    //         lv_style_set_border_color(menu_style, lv_color_hex(0x007ACC));
    //         lv_style_set_bg_color(cell_style, lv_color_hex(0x1E1E1E));
    //         lv_style_set_text_color(label_style, lv_color_hex(0xFFFFFF));
    //         lv_style_set_text_color(label_style_dark, lv_color_hex(0x000000));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0x3A3A3A));
    //         lv_style_set_bg_color(style_even, lv_color_hex(0x1A1A1A));
    //         lv_style_set_bg_color(style_odd, lv_color_hex(0x2A2A2A));
    //         break;

    //     case LIGHT:
    //         lv_style_set_bg_color(menu_style, lv_color_hex(0xFFFFFF));
    //         lv_style_set_bg_opa(menu_style, 255);
    //         lv_style_set_border_color(menu_style, lv_color_hex(0xAAAAAA));
    //         lv_style_set_bg_color(cell_style, lv_color_hex(0xF0F0F0));
    //         lv_style_set_text_color(label_style, lv_color_hex(0x000000));
    //         lv_style_set_text_color(label_style_dark, lv_color_hex(0xCCCCCC));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0xDDDDDD));
    //         lv_style_set_bg_color(style_even, lv_color_hex(0xE0E0E0));
    //         lv_style_set_bg_color(style_odd, lv_color_hex(0xF5F5F5));
    //         break;

    //     case DONUT:
    //         lv_style_set_bg_color(menu_style, lv_color_hex(0xFFCCFF));
    //         lv_style_set_bg_opa(menu_style, 220);
    //         lv_style_set_border_color(menu_style, lv_color_hex(0xFF66FF));
    //         lv_style_set_bg_color(cell_style, lv_color_hex(0xFFF0F8));
    //         lv_style_set_bg_opa(cell_style, 120);
    //         lv_style_set_text_color(label_style, lv_color_hex(0x550055));
    //         lv_style_set_text_color(label_style_dark, lv_color_hex(0xaa55aa));
    //         lv_style_set_bg_color(style_selected, lv_color_hex(0xFF99CC));
    //         lv_style_set_bg_color(style_even, lv_color_hex(0xFFDDFF));
    //         lv_style_set_bg_color(style_odd, lv_color_hex(0xFFDDEE));
    //         lv_style_set_bg_color(style_gradient, lv_color_hex(0xFFCCFF));
    //         lv_style_set_bg_grad_color(style_gradient, lv_color_hex(0xAACCFF));
    //         break;

    //     default:
    //         break;
    // }

    // Apply other theme-specific settings as needed.
}

void init_styles() {
//   AppData& data = getAppData();
  menu_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(menu_style);
  lv_style_set_bg_color(menu_style, lv_color_make(15, 37, 76));
  lv_style_set_bg_opa(menu_style, 240);
  lv_style_set_border_width(menu_style, 3);
  lv_style_set_border_color(menu_style, lv_color_make(0, 0, 0));
  lv_style_set_border_opa(menu_style, 54);
  lv_style_set_radius(menu_style, 0);
  lv_style_set_text_font(menu_style, &lv_font_montserrat_22);

  // Cell styles
  cell_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(cell_style);
  lv_style_set_bg_color(cell_style, lv_color_make(255, 255, 255));
  lv_style_set_bg_opa(cell_style, 20);
  lv_style_set_border_width(cell_style, 3);
  lv_style_set_border_color(cell_style, lv_color_make(0, 0, 0));
  lv_style_set_border_opa(cell_style, 100);
  lv_style_set_radius(cell_style, 2);

  // Notification obj style
  notification_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(notification_style);
  lv_style_set_bg_color(notification_style, lv_color_make(0, 255, 0));
  lv_style_set_bg_opa(notification_style, 240);
  lv_style_set_border_width(notification_style, 3);
  lv_style_set_border_color(notification_style, lv_color_make(0, 0, 0));
  lv_style_set_border_opa(notification_style, 54);
  lv_style_set_radius(notification_style, 0);
  lv_style_set_width(notification_style, lv_pct(100));
  lv_style_set_height(notification_style, 60);
  lv_style_set_text_font(notification_style, &lv_font_montserrat_22);

  // No Border style
  no_border_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(no_border_style);
  lv_style_set_bg_opa(no_border_style, 0);
  lv_style_set_border_width(no_border_style, 0);
  lv_style_set_border_opa(no_border_style, 0);

  no_borders_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(no_border_style);
  lv_style_set_border_width(no_border_style, 0);
  lv_style_set_border_opa(no_border_style, 0);

  // Compass obj style
  compass_obj_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(compass_obj_style);
  lv_style_set_bg_color(compass_obj_style, lv_color_make(0, 0, 0));
  lv_style_set_bg_opa(compass_obj_style, 120);
  lv_style_set_border_width(compass_obj_style, 0);
  lv_style_set_border_opa(compass_obj_style, 0);
  lv_style_set_radius(compass_obj_style, 0);

  // Screen style
  screen_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(screen_style);
  lv_style_set_bg_color(screen_style, lv_color_make(46, 64, 79));

  // Button styles
  button_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(button_style);
  lv_style_set_bg_color(button_style, lv_color_make(255, 255, 255));
  lv_style_set_radius(button_style, 0);

  // Label style
  label_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(label_style);
  lv_style_set_text_font(label_style, &lv_font_montserrat_22);
  lv_style_set_text_color(label_style, lv_color_make(255, 255, 255));
  lv_style_set_text_opa(label_style, 200);
  lv_style_set_pad_all(label_style, 6);
  // (label_style, 2, 0);

  label_style_dark = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(label_style_dark);
  lv_style_set_text_font(label_style_dark, &lv_font_montserrat_22);
  lv_style_set_text_color(label_style_dark, lv_color_make(0, 0, 0));
  lv_style_set_text_opa(label_style_dark, 200);
  lv_style_set_pad_all(label_style_dark, 6);

  // Styles for zebra striping and selected state
  style_even = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style_even);
  lv_style_set_size(style_even, lv_pct(100), 30);
  // lv_style_set_bg_color(style_even, lv_color_hex(0xFFFFFF));
  lv_style_set_bg_color(style_even, lv_color_make(255, 255, 255));
  lv_style_set_bg_opa(style_even, 40);
  lv_style_set_pad_all(style_even, 6);

  style_odd = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style_odd);
  lv_style_set_size(style_odd, lv_pct(100), 30);
  lv_style_set_bg_color(style_odd, lv_color_hex(0xF0F0F0));
  lv_style_set_pad_all(style_odd, 6);

  style_selected = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style_selected);
  lv_style_set_size(style_selected, lv_pct(100), 30);
  lv_style_set_bg_color(style_selected, lv_color_hex(0x00FF00));
  lv_style_set_bg_opa(style_selected, LV_OPA_80);
  lv_style_set_text_font(style_selected, &lv_font_montserrat_22);
  lv_style_set_text_color(style_selected, lv_color_make(0, 0, 0));
  lv_style_set_text_opa(style_selected, 200);

  style_sub_selected = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style_sub_selected);
  lv_style_set_size(style_sub_selected, lv_pct(100), 30);
  lv_style_set_bg_color(style_sub_selected, lv_color_hex(0x00FF00));
  lv_style_set_bg_opa(style_sub_selected, LV_OPA_30);
  lv_style_set_text_font(style_sub_selected, &lv_font_montserrat_22);
  lv_style_set_text_color(style_sub_selected, lv_color_make(0, 0, 0));
  lv_style_set_text_opa(style_sub_selected, 200);

  row_style = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(row_style);
  lv_style_set_border_width(row_style, 3);
  lv_style_set_border_color(row_style, lv_color_make(0, 0, 0));
  lv_style_set_border_opa(row_style, 54);
  lv_style_set_border_side(row_style, LV_BORDER_SIDE_BOTTOM);

  style_gradient = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style_gradient);
  lv_style_set_bg_grad_dir(style_gradient, LV_GRAD_DIR_VER);
  lv_style_set_bg_color(style_gradient, lv_color_hex(0x2E404F));
  lv_style_set_bg_grad_color(style_gradient, lv_color_hex(0x13202B));
}
