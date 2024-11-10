#include "SensorManager.h"

SensorManager& SensorManager::getInstance() {
    static SensorManager instance;
    return instance;
}

void SensorManager::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
}

void SensorManager::initializeSensors() {
    for (auto sensor : sensors) {
        sensor->initialize();
    }
}

void SensorManager::pollSensors() {
    for (auto sensor : sensors) {
        sensor->poll();
    }
}
