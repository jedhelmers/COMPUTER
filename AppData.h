#ifndef APPDATA_H
#define APPDATA_H

#include <Arduino.h>
#include <vector>
#include <functional>
#include "config.h"

class AppData {
public:
    static AppData& getInstance() {
        static AppData instance;
        return instance;
    }

    void addListener(std::function<void()> listener) {
        listeners.push_back(listener);
    }

    void notifyListeners() {
        for (auto& listener : listeners) {
            listener();
        }
    }

    void setCounter(int value) {
        if (counter != value) {
            counter = value;
            notifyListeners();
        }
    }

    void setCounter2(int value) {
        if (counter2 != value) {
            counter2 = value;
            notifyListeners();
        }
    }

    void setMessage(const String& value) {
        if (message != value) {
            message = value;
            notifyListeners();
        }
    }

    void setHeading(float value) {
        if (heading != value) {
            heading = value;
            notifyListeners();
        }
    }

    void setSelectedIndex(float value) {
        if (selectedIndex != value) {
            selectedIndex = value;
            notifyListeners();
        }
    }

    void setTank1(float value) {
        if (tank1 != value) {
            tank1 = value;
            notifyListeners();
        }
    }

    void setTank2(float value) {
        if (tank2 != value) {
            tank2 = value;
            notifyListeners();
        }
    }

    void setCurrentScreen(Screen newScreen) {
        if (newScreen != currentScreen) {
            currentScreen = newScreen;
            notifyListeners();
        }
    }

    void setCurrentMenuScreen(MenuScreen newScreen) {
        if (newScreen != currentMenuScreen) {
            currentMenuScreen = newScreen;
            notifyListeners();
        }
    }

    int getCounter() const { return counter; }
    int getCounter2() const { return counter2; }
    int getTank1() const { return tank1; }
    int getTank2() const { return tank2; }
    int getSelectedIndex() const { return selectedIndex; }
    Screen getCurrentScreen() { return currentScreen; }
    MenuScreen getCurrentMenuScreen() { return currentMenuScreen; }
    String getMessage() const { return message; }
    float getHeading() const { return heading; }

private:
    AppData() : counter(0), message("") {}

    int counter;
    int tank1;
    int tank2;
    float heading;
    String message;
    Screen currentScreen;
    MenuScreen currentMenuScreen = MenuScreen::THEMES;
    std::vector<std::function<void()>> listeners;

    // Menu
    int selectedIndex = 0;

    int counter2;
};


#endif
