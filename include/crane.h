#ifndef CRANE_H
#define CRANE_H


class Crane_position{
    int Z_angle;//deg
    int R_position;//mm
    bool down;
    
    Crane_position();
};

class Crane_movement{
    bool done;

    

    Crane_movement();

    void execute();
};
// functions
void craneSetupZAxisF();
void craneSetupRAxisF();
void craneSetupYAxisF();

bool craneMoveZF(int deg);
bool craneMoveRF(int mm);
bool craneMoveYF(int mm);

void craneArmTest();

#endif // CRANE_H