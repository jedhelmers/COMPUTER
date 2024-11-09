#ifndef THEMES_H
#define THEMES_H

#include <array>
#include <string>
#include "lvgl.h"


extern const std::array<std::string, 6> ThemeStateNames;

extern lv_obj_t * theme_menu_items[6];

lv_obj_t * getThemes(lv_obj_t * parent);

int getThemeIndex(const char *labelText);

ThemeState incrementTheme(ThemeState current);

ThemeState decrementTheme(ThemeState current);



#endif
