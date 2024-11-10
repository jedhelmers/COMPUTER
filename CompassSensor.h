#ifndef COMPASSSENSOR_H
#define COMPASSSENSOR_H

#include <Wire.h>
#include "MechaQMC5883.h"
#include "SensorManager.h"  // Include the base Sensor class

class CompassSensor : public Sensor {
public:
    CompassSensor();              // Constructor
    void initialize() override;   // Sensor initialization
    void poll() override;         // Polling logic
    int getX() const;             // Getter for X-axis
    int getY() const;             // Getter for Y-axis
    int getZ() const;             // Getter for Z-axis
    float getHeading() const;

private:
    MechaQMC5883 qmc;  // Instance of the compass library
    int x = 0, y = 0, z = 0;
};

#endif
