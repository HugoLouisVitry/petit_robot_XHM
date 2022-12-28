#include "motor.h"

Motor::Motor(){}
Motor::Motor(int pinA,int pinB)
{
    _pinA = pinA;
    _pinB = pinB;
    pinMode(_pinA,OUTPUT);
    pinMode(_pinB,OUTPUT); 
}

void Motor::command(bool dir)
{
    if(dir)
    {
        digitalWrite(_pinA,HIGH);
        digitalWrite(_pinA,LOW);
    }
    else
    {
        digitalWrite(_pinA,LOW);
        digitalWrite(_pinA,HIGH);
    }
}

void Motor::stop()
{
    digitalWrite(_pinA,LOW);
    digitalWrite(_pinA,LOW); 
}