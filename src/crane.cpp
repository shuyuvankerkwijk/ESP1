#include <Arduino.h>
#include "driver/ledc.h"
#include "crane.h"
#include "oled.h"
#include "pinout.h"
#include "ws.h"

int CranePWMFreq = 100;  // PWM frequency in Hz 
int CranePWMResolution = 8;  // PWM resolution in bits

int craneZChannelCW = 0;
int craneZChannelCCW = 1;
int craneRChannelForward = 2;  // PWM channel (0-15)
int craneRChannelBackward = 3;  // PWM channel (0-15)
int craneYChannelUpward = 4; // PWM channel (0-15)
int craneYChannelDownward = 5; // PWM channel (0-15)

float distPerClickR = 126/44; // Distance the rack moves in mm per click
float degPerClickZ = 90/1; //TODO: measure

volatile int encoderPosZ = 0;
volatile int directionZ = 0; // 0 is nothing, 1 is clockwise, -1 is counter-clockwise

volatile int encoderPosR = 0;
volatile int directionR = 0; // 0 is nothing, 1 is forward, -1 is backward

volatile int posY = -1; // -1 is up (retracted), 1 is down (extended)


void handleZEncoder();
void handleREncoder();
void handleYExtendSwitch();
void handleYRetractSwitch();

void craneSetupZAxis() {
    // CRANE Z MOTOR
    pinMode(ZMOTOR_FRONT_CW_PIN, OUTPUT);
    pinMode(ZMOTOR_FRONT_CCW_PIN, OUTPUT);

    ledcSetup(craneZChannelCW, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(ZMOTOR_FRONT_CW_PIN, craneZChannelCW); // Attach the PWM channel to the specified pin
    ledcWrite(craneZChannelCW, 0); // Set duty cycle to 0% (127/255)

    ledcSetup(craneZChannelCCW, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(ZMOTOR_FRONT_CCW_PIN, craneZChannelCCW); // Attach the PWM channel to the specified pin
    ledcWrite(craneZChannelCCW, 0); // Set duty cycle to 0% (127/255)

    // ENCODER FOR Z MOTOR
    pinMode(ZMOTOR_FRONT_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZMOTOR_FRONT_ENCODER_PIN), handleZEncoder, CHANGE); // on both rising and falling edges

    oledDisplay("Done Crane Z-Axis setup");
}

void craneSetupRAxis() {
    // CRANE R MOTOR
    pinMode(RMOTOR_FRONT_FORWARD_PIN, OUTPUT);
    pinMode(RMOTOR_FRONT_BACKWARD_PIN, OUTPUT);

    ledcSetup(craneRChannelForward, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(RMOTOR_FRONT_FORWARD_PIN, craneRChannelForward); // Attach the PWM channel to the specified pin
    ledcWrite(craneRChannelForward, 0); // Set duty cycle to 0% (127/255)

    ledcSetup(craneRChannelBackward, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(RMOTOR_FRONT_BACKWARD_PIN, craneRChannelBackward); // Attach the PWM channel to the specified pin
    ledcWrite(craneRChannelBackward, 0); // Set duty cycle to 0% (127/255)

    // ENCODER FOR R MOTOR
    pinMode(RMOTOR_FRONT_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RMOTOR_FRONT_ENCODER_PIN), handleREncoder, CHANGE); // on both rising and falling edges
    oledDisplay("Done Crane R-Axis setup");
}


void craneSetupYAxis() {
    // CRANE Y MOTOR
    pinMode(YMOTOR_FRONT_UP_PIN, OUTPUT);
    pinMode(YMOTOR_FRONT_DOWN_PIN, OUTPUT);
    
    ledcSetup(craneYChannelUpward, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(YMOTOR_FRONT_UP_PIN, craneYChannelUpward); // Attach the PWM channel to the specified pin
    ledcWrite(craneYChannelUpward, 0); // Set duty cycle to 0% (127/255)
    ledcSetup(craneYChannelDownward, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalitites
    ledcAttachPin(YMOTOR_FRONT_DOWN_PIN, craneYChannelDownward); // Attach the PWM channel to the specified pin
    ledcWrite(craneYChannelDownward, 0); // Set duty cycle to 0% (127/255)

    // LIMIT SWITCHES FOR Y MOTOR
    pinMode(YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN), handleYExtendSwitch, FALLING); // on both rising and falling edges
    attachInterrupt(digitalPinToInterrupt(YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN), handleYRetractSwitch, FALLING); // on both rising and falling edges

    oledDisplay("Done Crane Y-Axis setup");
}

void handleZEncoder() {
  // Check the direction of rotation 
    if (directionZ == -1) {
        encoderPosZ--; // counter-clockwise
    } else if (directionZ == 1) {
        encoderPosZ++; // clockwise
    } else {
      // Check line B?
    }
}

void handleREncoder() {
    // Check the direction of rotation
    if (directionR == -1) {
        encoderPosR--; // backward
    } else if (directionR == 1) {
        encoderPosR++; // forward
    } else {
      // Check line B?
    }
}

void handleYExtendSwitch() {
  posY = 1;
}

void handleYRetractSwitch() {
  posY = -1;
}

bool craneMoveZ(int final_pos) {
  // Rotate either clockwise or counterclockwise (given by sign of final_pos) to final_pos position (in clicks)
  if (final_pos > 0) { // clockwise
    if (encoderPosZ >= final_pos) { // reached position, stop crane
      ledcWrite(craneZChannelCW, 0);
      return true;
    } else { // have not reached position, start/keep rotating
      ledcWrite(craneZChannelCW, (255/255));
      return false;
    }
  } else { // counter-clockwise
    if (encoderPosZ <= abs(final_pos)) { // reached position, stop crane
      ledcWrite(craneZChannelCCW, 0);
      return true;
    } else { // have not reached position, start/keep rotating
      ledcWrite(craneZChannelCCW, (255/255));
      return false;
    }
  }
}

bool craneMoveR(int final_pos) {
  if (final_pos > 0) { // forward
    if (encoderPosR >= final_pos) {
      ledcWrite(craneRChannelForward, 0);
      wsSend("Done"); // TEMPORARY
      return true;
    } else {
      ledcWrite(craneRChannelForward, (255/255));
      wsSend("Epos:" + String(encoderPosR)); // TEMPORARY
      return false;
    }
  } else { // backward
    if (encoderPosR <= abs(final_pos)) {
      ledcWrite(craneRChannelBackward, 0);
      return true;
    } else {
      ledcWrite(craneRChannelBackward, (255/255));
      return false;
    }
  }
}

bool craneMoveY(int final_pos) {
  if (final_pos == -1) { // Retract
    if (posY == -1) {
      ledcWrite(craneYChannelUpward, 0);
      return true;
    } else {
      ledcWrite(craneYChannelUpward, (200/255)); // Set duty cycle to 66%
      return false;
    }
  } else { // Extend
    if (posY == 1) {
      ledcWrite(craneYChannelDownward, 0);
      return true;
    } else {
      ledcWrite(craneYChannelDownward, (200/255)); // Set duty cycle to 66%
      return false;
    }
  }
}

void craneArmTest() {
  ledcWrite(craneRChannelForward, 255);
  delay(1000);
  ledcWrite(craneRChannelForward, 0);
  delay(1000);
  ledcWrite(craneRChannelBackward, 255);
  delay(1000);
  ledcWrite(craneRChannelBackward, 0);
}



