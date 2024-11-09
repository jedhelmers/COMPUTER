#include "LoadScreen.h"
#include "AppData.h"
#include "styles.h"


void createLoadScreen(lv_obj_t* screen) {
  lv_obj_t * load_screen = lv_obj_create(screen);
  lv_obj_set_size(load_screen, lv_pct(100), lv_pct(100));
  lv_obj_add_style(load_screen, style_gradient, LV_PART_MAIN);
  lv_obj_add_style(load_screen, no_border_style, LV_PART_MAIN);
  lv_obj_set_style_radius(load_screen, 0, 0);

  // Compass image
  LV_IMG_DECLARE(skull);
  lv_obj_t *skull_img = lv_img_create(load_screen);
  lv_img_set_src(skull_img, &skull);
  lv_obj_align(skull_img, LV_ALIGN_CENTER, 0, 0);
}
