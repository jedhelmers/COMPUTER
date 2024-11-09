#ifndef CONFIG_H
#define CONFIG_H

#define ROW_HEIGHT 68
#define BUTTON_WIDTH 40
#define TANK_MAX 300
#define AZ_MAX 1900
#define AZ_DIRECTION 1
#define MENU_BUTTON 4
#define UP_BUTTON 5
#define SELECT_BUTTON 6
#define DOWN_BUTTON 7
#define MESSAGE_BUTTON 8
#define TANK_1_BUTTON A0
#define TANK_2_BUTTON A1

enum MenuState { DISTRESS, STUFF, DEVICES, DISPLAY_MENU, THEMES };
enum ThemeState { DEFAULT, DARK, CRT, OPS, LIGHT, DONUT };
enum ScreenState { LOAD, MAIN, MENU };

#endif
