#ifndef TRI_CONTROL_H
#define TRI_CONTROL_H

#include "motor.h"


class Controll
{
    public:
        Controll(Motor mot_A, Motor mot_B);
        void move(bool dir);
        void rotate(bool hdg);
        void stop();
        Motor _mot_A;
        Motor _mot_B;

};

#endif



