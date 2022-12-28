//vérifier après tests
//motor A : ENA(pwm),IN4(+),IN3(-)
//motor B : ENB(pwm),IN1(+),IN2(-)

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>


class Motor 
{
    public:
        Motor();
        Motor(int pinA,int pinB);
        void command(bool dir);
        void stop();
        int _pinA;
        int _pinB;
};


#endif