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

    int getCounter() const { return counter; }
    String getMessage() const { return message; }

    int getCounter2() const { return counter2; }

private:
    AppData() : counter(0), message("") {}

    int counter;
    String message;
    std::vector<std::function<void()>> listeners;

    int counter2;
};


#endif
