#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>

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

// CAN Config
const uint8_t CAN_PIN_CS = 10;
const uint8_t CAN_PIN_INT = 2;

// SPI
#define PIN_SPI_MISO  (89u)
#define PIN_SPI_MOSI  (90u)
#define PIN_SPI_SCK   (91u)
// Same as SPI1 for backwards compatibility
#define PIN_SPI_SS    (10u)

#define PIN_SPI_MISO1  (12u)
#define PIN_SPI_MOSI1  (11u)
#define PIN_SPI_SCK1   (13u)
#define PIN_SPI_SS1    (10u)


enum MenuState { DISTRESS, STUFF, DEVICES, DISPLAY_MENU, THEMES };
enum ThemeState { DEFAULT, DARK, CRT, OPS, LIGHT, DONUT };
enum ScreenState { LOAD, MAIN, MENU };
enum class Screen {
    LOAD,
    MAIN,
    MENU,
    DEVICES
};
enum class MenuScreen {
    DISTRESS,
    STUFF,
    DEVICES,
    DISPLAY_MENU,
    THEMES
};

const std::array<std::string, 5> MenuStateNames = {
    "Distress", "Stuff", "Devices", "Display", "Themes"
};

#endif
