#include <Arduino.h>
#include "ws.h"
#include "crane.h"
#include "bluepill_uart.h"
#include "esp2_uart.h"
#include "vacuum.h"
#include "pinout.h"
#include "driver/ledc.h"
#include "driver/ledc.h"

// // bool run = true;

// void setup() {
//   Serial.begin(115200);
//   pinMode(14, OUTPUT);
//   pinMode(20, OUTPUT);
//   pinMode(0, OUTPUT);
//   pinMode(39, OUTPUT);
//   digitalWrite(14, LOW);
//   digitalWrite(20, LOW);
//   digitalWrite(0, LOW);
//   digitalWrite(39, LOW); 

//   // bluepillUartSetup();
//   // wsSetup();

//   // craneSetupZAxisB();
//   // craneSetDirectionZB(1); // set clockwise

//   // craneSetupRAxisB();
//   // craneSetDirectionRB(1); // set extend

//   craneSetupYAxisB();
//   craneSetDirectionYB(1); // set extend

//   Serial.println("Done setup");
// }

// bool done = false;

// void loop() {
//   // String msg = bluepillUartReceive();
//   // if (msg != "" && run) {
//   //   wsSend(msg);
//   // }
//   if (done) {
//     Serial.println("Done moving ZB");
//     delay(10000);
//   } else {
//     // done = craneMoveRB(20);
//     done = craneMoveYB(1);
//   }
// }




// TRY

enum RobotState {
  START,
  DRIVE_TO_TOMATO,
  PICKUP_TOMATO_ATTACK,
  PICKUP_TOMATO_RETREAT,
  DEPOSIT_TOMATO,
  EXTEND_CUP
};

RobotState robot_state = START;

void setup() {
  // These pins default high, so start by setting them low
  pinMode(14, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(39, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(20, LOW);
  digitalWrite(0, LOW);
  digitalWrite(39, LOW); 

  // bluepillUartSetup();
  // esp2UartSetup();
  // wsSetup();
  // vacuumSetupF();
  vacuumSetupB();
  // craneSetupF();
  craneSetupB();

  // wsSend("Setup complete");
}

void loop() {
  bool doneZB = false;
  bool doneRB = false;
  bool doneYB = false;

  switch (robot_state) {

    case START:
      if (true) {
        robot_state = DRIVE_TO_TOMATO;
        craneSetDirectionZB(1); // set clockwise
        
      }
      Serial.println("Start");
      break;

    case DRIVE_TO_TOMATO:
      doneZB = craneMoveZB(48); //set to 72 to move 270 degrees clockwise around z-axis (72 clicks of 3.25 degrees each), rn 180 deg

      if (doneZB) {
        robot_state = PICKUP_TOMATO_ATTACK;
        craneSetDirectionRB(1); // set extend
      }
      Serial.println("Drive to tomato");
      break;
    
    case PICKUP_TOMATO_ATTACK:
      // delay(1000);
      doneRB = craneMoveRB(5); // Move arm to the 70 (?) click position outwards
      doneYB = craneMoveYB(1); // Extend arm down

      if (doneRB && doneYB) {
        vacuumOnB(200);
        craneSetDirectionYB(-1); // set retract
        craneSetDirectionRB(-1); // set retract
        robot_state = PICKUP_TOMATO_RETREAT;
      }
      Serial.println("Pickup tomato attack");
      break;
    
    case PICKUP_TOMATO_RETREAT:
      doneRB = craneMoveRB(-20); // Move arm to the 25 (?) click position inwards
      doneYB = craneMoveYB(-1); // Retract arm up
      if (doneRB && doneYB) {
        vacuumOffB();
        robot_state = DEPOSIT_TOMATO;
      }
      Serial.println("Pickup tomato retreat");
      break;

    case DEPOSIT_TOMATO:
      Serial.println("Deposit tomato");
      delay(1000);
      break;

    default:
      break;
  }
}









// REAL


// enum RobotState {
//   WAITING_TO_START_COURSE,
//   DRIVE_TO_TOMATO,
//   PICKUP_TOMATO_ATTACK,
//   PICKUP_TOMATO_RETREAT,
//   DEPOSIT_TOMATO,
//   DRIVE_TO_LETTUCE,
//   PICKUP_LETTUCE_ATTACK,
//   PICKUP_LETTUCE_RETREAT,
//   DEPOSIT_LETTUCE,
//   DRIVE_TO_PLATE,
//   GRAB_PLATE,
//   VACUUM_PLATE,
//   DRIVE_TO_SERVING,
//   DROP_PLATE,
//   DROP_FOOD
// };

// enum BluepillState {
//   WAITING,
//   MOVING,
//   DONE
// };

// RobotState robot_state = WAITING_TO_START_COURSE;
// BluepillState bp_state = WAITING;

// void setup() {
//   // These pins default high, so start by setting them low
//   pinMode(14, OUTPUT);
//   pinMode(20, OUTPUT);
//   pinMode(0, OUTPUT);
//   pinMode(39, OUTPUT);
//   digitalWrite(14, LOW);
//   digitalWrite(20, LOW);
//   digitalWrite(0, LOW);
//   digitalWrite(39, LOW); 

//   bluepillUartSetup();
//   esp2UartSetup();
//   wsSetup();
//   vacuumSetupF();
//   vacuumSetupB();
//   craneSetupF();
//   craneSetupB();

//   wsSend("Setup complete");
// }

// void loop() {
//   bool doneZF = false;
//   bool doneRF = false;
//   bool doneYF = false;

//   bool doneZB = false;
//   bool doneRB = false;
//   bool doneYB = false;

//   switch (robot_state) {
//     case WAITING_TO_START_COURSE:
//       if (digitalRead(START_SWITCH_PIN)) {
//         robot_state = DRIVE_TO_TOMATO;
//       }
//       break;

//     case DRIVE_TO_TOMATO:
//       if (bp_state == WAITING) {
//         bluepillUartSend("Cheese");
//         bp_state = MOVING;
//       }

//       doneZB = craneMoveZB(72); // move 270 degrees clockwise around z-axis (72 clicks of 3.25 degrees each)

//       if (doneZB && doneRB && bp_state == DONE) {
//         bp_state = WAITING;
//         robot_state = PICKUP_TOMATO_ATTACK;
//       }
//       break;
    
//     case PICKUP_TOMATO_ATTACK:
//       doneRB = craneMoveRB(70); // Move arm to the 70 (?) click position outwards
//       doneYB = craneMoveYB(1); // Extend arm down

//       if (doneRB && doneYB) {
//         vacuumOnB(128);
//         robot_state = PICKUP_TOMATO_RETREAT;
//       }
//       break;
  
//     case PICKUP_TOMATO_RETREAT:
//       doneRB = craneMoveRB(50); // Move arm to the 50 (?) click position outwards
//       doneYB = craneMoveYB(-1); // Retract arm up
//       if (doneRB && doneYB) {
//         robot_state = DEPOSIT_TOMATO;
//       }
//       break;
    
//     case DEPOSIT_TOMATO:
//       doneZB = craneMoveZB(-20); // Move arm to the -25 (?) click position around z-axis
//       doneRB = craneMoveRB(-20); // Move arm to the 20 (?) click position inwards
//       if (doneZB && doneRB) {
//         vacuumOffB();
//         robot_state = DRIVE_TO_LETTUCE;
//       }
//       break;
    
//     case DRIVE_TO_LETTUCE:
//       if (bp_state == WAITING) {
//         bluepillUartSend("Lettuce");
//         bp_state = MOVING;
//       }
//       // 
//       break;
    
//     case PICKUP_LETTUCE_ATTACK:
//       // 
//       break;

//     case PICKUP_LETTUCE_RETREAT:
//       // 
//       break;
    
//     case DEPOSIT_LETTUCE:
//       // 
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

//     case DROP_PLATE:
//       //
//       break;

//     case DROP_FOOD:
//       //
//       break;
    
//     default:
//       break;
//   }

//   String msg = bluepillUartReceive();
//   if(msg == "Done" && bp_state == MOVING){
//     bp_state = DONE;
//   } 

// }
































// // // // DEFAULT HIGH: 20, 0, 39, 2 (rx), 1 (tx), rx, tx, 
// bool run = true;

// // int angle = 0;

// // void zencoding(){
// //   angle++;
// // }

// // BLUEPILL UART MODE
// void setup() {
//   // These pins default high, so start by setting them low
//   pinMode(14, OUTPUT);
//   pinMode(20, OUTPUT);
//   pinMode(0, OUTPUT);
//   pinMode(39, OUTPUT);
//   digitalWrite(14, LOW);
//   digitalWrite(20, LOW);
//   digitalWrite(0, LOW);
//   digitalWrite(39, LOW);  

//   bluepillUartSetup();
//   wsSetup();

//   Serial.begin(115200);
// }

// // int reps = 0;
// void loop() {
//   String msg = bluepillUartReceive();
//   if(msg != ""&&run){
//     wsSend(String(msg));
//   } 
//   // delay(10);

//   // Serial.println("Angle: " + String(angle));
//   // wsSend("Angle"+ String(angle));
//   // delay(5);
//   // }else{
//   //   analogWrite(47, 0);
//   //   wsSend("Done");
//   //   delay(50);
//   // }
// }

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