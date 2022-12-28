
#include <Arduino.h>
#include "motor.h"
#include "tri_control.h"


int motor_1_A  = 13;
int motor_1_B  = 12;
int motor_2_A  = 27;
int motor_2_B  = 14;

int SERVO_PIN = 23;

bool FORWARD = true;
bool TRIGO = true;  

Motor motor_1(motor_1_A,motor_1_B);
Motor motor_2(motor_2_A,motor_2_B);

Controll controller(motor_1,motor_2,SERVO_PIN);

void setup()
{
    Serial.begin(9600); 
}

void loop()
{
    char cmd = Serial.read();

    if(-1!=cmd)
    {
        if('F' == cmd ){controller.move(FORWARD);}
        else if('B' == cmd ){controller.move(!FORWARD);}
        else if('L' == cmd ){controller.rotate(TRIGO);}
        else if('R' == cmd ){controller.rotate(!TRIGO);}
        else if('S' == cmd ){controller.stop();}
        //Serial.println("Executed");

    }
    else {controller.stop();}
    
}


