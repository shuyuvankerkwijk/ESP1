#include <Arduino.h>
#include "ws.h"
// #include "crane.h"
// #include "oled.h"
#include "bluepill_uart.h"
// #include "esp_comm.h"
// #include "cups.h"
// #include "vacuum.h"
// #include "pinout.h"
// #include "driver/ledc.h"
// #include "driver/ledc.h"

// BLUEPILL UART MODE
void setup() {
  Serial.begin(115200);
  // bluepillUartSetup();
  // wsSetup();
}

void loop() {
  Serial.println("Looping");
  delay(1000);
  // String msg = bluepillUartReceive();
  // if(msg != ""){
  //   // wsSend(String(msg));
  //   Serial.println(String(msg));
  // } else {
  //   // wsSend("No message");
  //   Serial.println("No message");
  // }
  // delay(100);
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