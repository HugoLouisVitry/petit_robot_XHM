#ifndef TRI_CONTROL_H
#define TRI_CONTROL_H

#include "motor.h"

#define PWM_STRAIGHT_ANGLE 100 // à chercher
#define PWM_TURN_ANGLE 50 // à chercher

class Controll
{
    public:
        Controll(Motor mot_A,Motor mot_B,int servo_pin);
        void move(bool dir);
        void rotate(bool hdg);
        void stop();
        Motor _mot_A;
        Motor _mot_B;
        int _servo_pin;

};

#endif



