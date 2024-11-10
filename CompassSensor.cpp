#include "CompassSensor.h"
#include <math.h>
#include <Arduino.h>

CompassSensor::CompassSensor() {
    // Constructor (empty for now, but you can initialize variables if needed)
}

void CompassSensor::initialize() {
    Wire.begin();
    qmc.init();
    Serial.println("CompassSensor initialized");
    // Optional: Configure specific modes if needed
    // qmc.setMode(Mode_Continuous, ODR_200Hz, RNG_2G, OSR_256);
}

void CompassSensor::poll() {
    qmc.read(&x, &y, &z);  // Read data from the sensor

    // Debug output for testing
    // Serial.print("Compass Data - X: ");
    // Serial.print(x);
    // Serial.print(" Y: ");
    // Serial.print(y);
    // Serial.print(" Z: ");
    // Serial.println(z);
}

int CompassSensor::getX() const {
    return x;
}

int CompassSensor::getY() const {
    return y;
}

int CompassSensor::getZ() const {
    return z;
}

float CompassSensor::getHeading() const {
    // Calculate heading in radians
    float heading = atan2((float)y, (float)x);

    // Declination angle adjustment (example for 2° 8')
    float declinationAngle = (2.0 + (8.0 / 60.0)) * (M_PI / 180.0);
    heading += declinationAngle;

    // Normalize heading to the range 0-2π
    if (heading < 0) {
        heading += 2 * M_PI;
    } else if (heading > 2 * M_PI) {
        heading -= 2 * M_PI;
    }

    // Convert to degrees
    float headingDegrees = heading * 180.0 / M_PI;

    // Account for sensor orientation (if mounted upside down)
    headingDegrees = 360.0 - headingDegrees;

    // Normalize to 0-360° range
    if (headingDegrees < 0) {
        headingDegrees += 360.0;
    }

    return headingDegrees;
}
