#ifndef STYLES_H
#define STYLES_H

#include "lvgl.h"

// Declare style variables
extern lv_style_t * menu_style;
extern lv_style_t * cell_style;
extern lv_style_t * row_style;
extern lv_style_t * notification_style;
extern lv_style_t * no_border_style;
extern lv_style_t * no_borders_style;
extern lv_style_t * compass_obj_style;
extern lv_style_t * button_style;
extern lv_style_t * label_style;
extern lv_style_t * label_style_dark;
extern lv_style_t * screen_style;
extern lv_style_t * style_even;
extern lv_style_t * style_odd;
extern lv_style_t * style_selected;
extern lv_style_t * style_sub_selected;
extern lv_style_t * style_gradient;

// Function to initialize styles
void init_styles();

void setThemeColors();

#endif // STYLES_H
