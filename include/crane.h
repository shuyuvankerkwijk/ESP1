#ifndef CRANE_H
#define CRANE_H

// functions
void craneSetupZAxis();
void craneSetupRAxis();
void craneSetupYAxis();

bool craneMoveZ(int deg);
bool craneMoveR(int mm);
bool craneMoveY(int mm);

void craneArmTest();

#endif // CRANE_H