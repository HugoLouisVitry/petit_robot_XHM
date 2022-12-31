
#include "tri_control.h"


Controll::Controll(Motor mot_A,Motor mot_B,int servo_pin)
{
    _mot_A = mot_A;
    _mot_B = mot_B;
    _roue_avant.attach(servo_pin);
}

void Controll::move(bool dir) // les moteurs tournent dans le même sens
{
    _mot_A.command(dir);
    _mot_B.command(dir);
    _roue_avant.write(PWM_STRAIGHT_ANGLE);
}

void Controll::rotate(bool hdg) // les moteurs tournent en sens opposé
{
    _mot_A.command(hdg);
    _mot_B.command(!hdg);
    if(hdg) {_roue_avant.write( PWM_TURN_ANGLE);}
    else    {_roue_avant.write(-PWM_TURN_ANGLE);}
    
}

void Controll::stop()
{
    _mot_A.stop();
    _mot_B.stop();
}
