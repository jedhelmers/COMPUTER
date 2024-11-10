#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <vector>

class Sensor {
public:
    virtual void initialize() = 0;  // Sensor-specific initialization
    virtual void poll() = 0;        // Poll the sensor for data
    virtual ~Sensor() = default;
};

class SensorManager {
public:
    static SensorManager& getInstance();  // Singleton instance

    void addSensor(Sensor* sensor);
    void initializeSensors();
    void pollSensors();

private:
    SensorManager() = default;             // Private constructor
    std::vector<Sensor*> sensors;
};

#endif
