#ifndef APPDATA_H
#define APPDATA_H

#include <Arduino.h>
#include <vector>
#include <functional>

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

    int getCounter() const { return counter; }
    int getCounter2() const { return counter2; }
    String getMessage() const { return message; }
    float getHeading() const { return heading; }

private:
    AppData() : counter(0), message("") {}

    int counter;
    float heading;
    String message;
    std::vector<std::function<void()>> listeners;

    int counter2;
};


#endif
