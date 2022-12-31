
#include <Arduino.h>
#include "motor.h"
#include "tri_control.h"
#include "web_page.h"

int led1 = 32;
int led2 = 33;
int led3 = 35;
int led4 = 34;

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
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led4,OUTPUT);
    
    // démo
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led2,HIGH);
    delay(500);
    digitalWrite(led3,HIGH);
    delay(500);
    digitalWrite(led4,HIGH);
    delay(500);
    controller.move(FORWARD);
    delay(1000);
    controller.move(!FORWARD);
    delay(1000);
    controller.rotate(TRIGO);
    delay(1000);
    controller.rotate(!TRIGO);
    delay(1000);
    controller.stop();
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);            
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);


    custom_serv_init();


}




void loop()
{
    

    if(-1!=CMD)
    {
        if('F' == CMD )
        {
            controller.move(FORWARD);
            digitalWrite(led1,LOW );
            digitalWrite(led2,LOW );            
            digitalWrite(led3,HIGH);
            digitalWrite(led4,HIGH);

        }
        else if('B' == CMD )
        {
            controller.move(!FORWARD);
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);            
            digitalWrite(led3,LOW );
            digitalWrite(led4,LOW );

        }
        else if('L' == CMD )
        {
            controller.rotate(TRIGO);
            digitalWrite(led1,HIGH);
            digitalWrite(led2,LOW );            
            digitalWrite(led3,LOW );
            digitalWrite(led4,HIGH);
        }
        else if('R' == CMD )
        {
            controller.rotate(!TRIGO);
            digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);            
            digitalWrite(led3,HIGH);
            digitalWrite(led4,LOW);
        }
        else if('S' == CMD )
        {
            controller.stop();
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);            
            digitalWrite(led3,HIGH);
            digitalWrite(led4,HIGH);
        }

    }
    else 
    {
        controller.stop();
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);            
        digitalWrite(led3,LOW);
        digitalWrite(led4,LOW);
    }

    // wifi control

    _server.handleClient();

}


