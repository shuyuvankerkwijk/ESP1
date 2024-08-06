#include <Arduino.h>
// #include "ws.h"
// #include "crane.h"
// #include "oled.h"
#include "bluepill_uart.h"
// #include "esp_comm.h"
// #include "cups.h"
// #include "vacuum.h"
// #include "pinout.h"
// #include "driver/ledc.h"
// #include "driver/ledc.h"

// // DEFAULT HIGH: 20, 0, 39, 2? ( might just be rx rn ), 1 (might just be tx rn), rx, tx, 
bool run = true;
//21,47,48,0

// 21 = front arm counterclockwise, 47 = front arm clockwise

int angle = 0;

void zencoding(){
  angle++;
}

// BLUEPILL UART MODE
void setup() {
  Serial.begin(115200);
  //bluepillUartSetup();
  // These pins default high, so start by setting them low
  pinMode(14, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(39, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(20, LOW);
  digitalWrite(0, LOW);
  digitalWrite(39, LOW);  

  // wsSetup();

  pinMode(40, INPUT);
  attachInterrupt(digitalPinToInterrupt(40), zencoding, RISING);

  pinMode(21, OUTPUT); // back arm counterclockwise
  pinMode(47, OUTPUT); // back arm clockwise
  pinMode(48, OUTPUT); // front arm clockwise
  // pinMode(0, OUTPUT); // front arm counterclockwise

  // analogWrite(21, 255);
  // analogWrite(47, 255);
  // analogWrite(48, 255);
  // analogWrite(0, 255);

  // pinMode(13, OUTPUT); // back arm down
  // pinMode(12, OUTPUT); // back arm up

  // pinMode(11, OUTPUT); // back arm backwards
  // pinMode(10, OUTPUT); // back arm forwards

  // pinMode(14, OUTPUT); // back arm vacuum?


  // analogWrite(14, 255);

  // delay(2000);

  // analogWrite(14, 100);

  // delay(5000);

  // analogWrite(14, 0);

}
// int reps = 0;
void loop() {
  // String msg = bluepillUartReceive();
  // if(msg != ""&&run){
  //   wsSend(String(msg));
  // } 
  // delay(10);

  Serial.println("Angle: " + String(angle));
  // wsSend("Angle"+ String(angle));
  // delay(5);
  // }else{
  //   analogWrite(47, 0);
  //   wsSend("Done");
  //   delay(50);
  // }
}

// // TESTING CRANE R MODE
// void setup() {
//   craneSetupRAxis();
//   wsSetup();
//   delay(1000);
// }

// void loop() {
//   bool doneR = craneMoveR(50);
//   if (doneR) {
//     wsSend("Done moving R");
//     delay(10000);
//   }
// }

// // TESTING DOWN + VACUUM MODE
// void setup() {
//   craneSetupYAxis();
//   vacuumSetup();
//   wsSetup();
//   delay(1000);
// }

// void loop() {
//   bool doneY = craneMoveY(1);
//   if (doneY) {
//     vacuumOn(128);
//     bool doneY2 = craneMoveY(-1);
//     if (doneY2) {
//       vacuumOff();
//       wsSend("Done moving Y");
//       delay(10000);
//     }
//   }
// }


// enum RobotState {
//   WAITING_TO_START_COURSE,
//   DRIVE_TO_CHEESE,
//   PICKUP_CHEESE_ATTACK,
//   PICKUP_CHEESE_RETREAT,
//   DEPOSIT_CHEESE,
//   DRIVE_TO_PLATE,
//   GRAB_PLATE,
//   VACUUM_PLATE,
//   DRIVE_TO_SERVING,
//   DROP_PLATE,
//   DROP_CHEESE
// };

// enum BluepillState {
//   WAITING,
//   MOVING,
//   DONE
// };

// RobotState robot_state = WAITING_TO_START_COURSE;
// BluepillState bp_state = WAITING;

// void setup() {
//   Serial.begin(9600);
//   oledSetup();
//   bluepillUartSetup();
//   wsSetup();
//   vacuumSetup();
//   craneSetupRAxis();
//   craneSetupYAxis();
//   craneSetupZAxis();

//   Serial.println("Done setup");
// }

// void loop() {
//   bool doneZ = false;
//   bool doneR = false;
//   bool doneY = false;

//   switch (robot_state) {
//     case WAITING_TO_START_COURSE:
//       if (digitalRead(START_SWITCH_PIN)) {
//         robot_state = DRIVE_TO_CHEESE;
//       }
//       break;

//     case DRIVE_TO_CHEESE:
//       if (bp_state == WAITING) {
//         bluepillUartSend("Cheese");
//         bp_state = MOVING;
//       }
//       doneZ = craneMoveZ(25); // Move arm to the 25 (?) click position around z-axis
//       doneR = craneMoveR(50); // Move arm to the 50 (?) click position outwards
//       if (doneZ && doneR && bp_state == DONE) {
//         bp_state = WAITING;
//         robot_state = PICKUP_CHEESE_ATTACK;
//       }
//       break;
    
//     case PICKUP_CHEESE_ATTACK:
//       doneR = craneMoveR(70); // Move arm to the 70 (?) click position outwards
//       doneY = craneMoveY(1); // Extend arm down
//       if (doneR && doneY) {
//         vacuumOn(128);
//         robot_state = PICKUP_CHEESE_RETREAT;
//       }
//       break;
  
//     case PICKUP_CHEESE_RETREAT:
//       doneR = craneMoveR(50); // Move arm to the 50 (?) click position outwards
//       doneY = craneMoveY(-1); // Retract arm up
//       if (doneR && doneY) {
//         robot_state = DEPOSIT_CHEESE;
//       }
//       break;
    
//     case DEPOSIT_CHEESE:
//       doneZ = craneMoveZ(-20); // Move arm to the -25 (?) click position around z-axis
//       doneR = craneMoveR(-20); // Move arm to the 20 (?) click position inwards
//       if (doneZ && doneR) {
//         vacuumOff();
//         robot_state = DRIVE_TO_PLATE;
//       }
//       break;
    
//     case DRIVE_TO_PLATE:
//       //
//       break;
    
//     case GRAB_PLATE:
//       //
//       break;
    
//     case VACUUM_PLATE:
//       //
//       break;
    
//     case DRIVE_TO_SERVING:
//       //
//       break;

//     default:
//       break;
//   }
// }















// // void loop() {
// //   // String msg = bluepillUartReceive();
// //   // if (msg != "") {
// //   //   // wsSend(msg);
// //   //   Serial.println(msg);
// //   // }
// //   // delay(100);
// //   if (Serial1.available() > 0) {
// //     // Read the incoming data until a newline character is encountered
// //     String incomingData = Serial1.readStringUntil('\n');
    
// //     // Print the incoming data to Serial0 (USB to Serial)
// //     Serial.println(incomingData);
// //   }
// //   wsSend("message:"+String(i));
// //   delay(1000);
// //   i++;
// // }

// // const int gpioPins[] = {
// //   4,5,6,7,15,16,17,18,8,3,46,9,10,11,12,13,14,19,20,21,47,48,45,0,35,36,37,38,39,40,41,42,2,1
// // }; 

// // const int ledcChannel = 0;
// // const int pwmFrequency = 1000;  // 1 kHz
// // const int pwmResolution = 8;    // 8-bit resolution
// // const int pwmDutyCycle = 128;   // 50% duty cycle

// // void setup() {
//   // Serial.begin(115200);

//   // delay(5000);
//   // for (int i = 0; i < sizeof(gpioPins) / sizeof(gpioPins[0]); ++i) {
    
//   //   pinMode(gpioPins[i], OUTPUT);

//   //   // Configure and attach the PWM channel to the current pin
//   //   ledcSetup(ledcChannel, pwmFrequency, pwmResolution);
//   //   ledcAttachPin(gpioPins[i], ledcChannel);
//   //   ledcWrite(ledcChannel, pwmDutyCycle);

//   //   // Display the current GPIO pin being set
//   //   String message = "GPIO " + String(gpioPins[i]) + " set to HIGH (PWM)";
//   //   // oledDisplay(message);
//   //   Serial.println(message);

//   //   delay(100);  // Delay to observe the state change
//   // }
// // }