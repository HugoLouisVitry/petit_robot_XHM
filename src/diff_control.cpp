
#include "diff_control.h"


Controll::Controll(Motor mot_A, Motor mot_B)
{
    _mot_A_pin = mot_A._pwm_pin;
    _mot_B_pin = mot_B._pwm_pin;
}

void Controll::move(float cmd_move_speed) // les moteurs tournent dans le même sens
{
    _pwm_move_value = cmd_move_speed; // convertion -> (pwm €[0;255])
    analogWrite(_mot_A_pin,_pwm_move_value);
    analogWrite(_mot_B_pin,_pwm_move_value);

}

void Controll::rotate(float cmd_rot_speed) // les moteurs tournent en sens opposé
{
    _pwm_rot_value = cmd_rot_speed; // conversion
    analogWrite(_mot_A_pin,_pwm_rot_value);
    analogWrite(_mot_B_pin,-_pwm_rot_value);

}

void Controll::stop()
{
    analogWrite(_mot_A_pin,ZERO_SPEED);
    analogWrite(_mot_B_pin,ZERO_SPEED);
}
