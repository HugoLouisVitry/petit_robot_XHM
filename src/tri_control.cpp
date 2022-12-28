
#include "tri_control.h"


Controll::Controll(Motor mot_A, Motor mot_B)
{
    _mot_A = mot_A;
    _mot_B = mot_B;
}

void Controll::move(bool dir) // les moteurs tournent dans le même sens
{
    _mot_A.command(dir);
    _mot_B.command(dir);
}

void Controll::rotate(bool hdg) // les moteurs tournent en sens opposé
{
    _mot_A.command(hdg);
    _mot_B.command(!hdg);

}

void Controll::stop()
{
    _mot_A.stop();
    _mot_B.stop();
}
