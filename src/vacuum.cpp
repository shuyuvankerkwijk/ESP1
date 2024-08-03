#include <Arduino.h>
#include "vacuum.h"
#include "main.h"
#include "oled.h"
#include "pinout.h"

int vacuum_freq = 100;
int resolution = 8;
int vacuumInChannel = 8;  // PWM channel for vacuum in

void vacuumSetup() {
    // Configure vacuum control pin as output
    pinMode(VACUUM_FRONT_MOTOR_PIN, OUTPUT);

    // Configure PWM channel
    ledcSetup(vacuumInChannel, vacuum_freq, resolution);

    // Attach PWM channel to the specified GPIO pin
    ledcAttachPin(VACUUM_FRONT_MOTOR_PIN, vacuumInChannel);

    // Initialize duty cycle to 0% (vacuum off)
    ledcWrite(vacuumInChannel, 0);

    oledDisplay("Vacuum setup");
}

void vacuumOn(int power) {
    ledcWrite(vacuumInChannel, power);  // Set vacuum to int power
}

void vacuumOff() {
    ledcWrite(vacuumInChannel, 0);  // Turn vacuum off
}

