
#include <Arduino.h>
#include "motor.h"
#include "tri_control.h"
#include <WiFi.h>


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

const char* ssid = "robot";
const char* passwd = "robotcities";
String entete;
WiFiServer server(80);

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

    // serveur wifi
    WiFi.begin(ssid,passwd);
    while (WiFi.status()!=WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    
    // control serial
    char cmd = Serial.read();

    if(-1!=cmd)
    {
        if('F' == cmd )
        {
            controller.move(FORWARD);
            digitalWrite(led1,LOW );
            digitalWrite(led2,LOW );            
            digitalWrite(led3,HIGH);
            digitalWrite(led4,HIGH);

        }
        else if('B' == cmd )
        {
            controller.move(!FORWARD);
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);            
            digitalWrite(led3,LOW );
            digitalWrite(led4,LOW );

        }
        else if('L' == cmd )
        {
            controller.rotate(TRIGO);
            digitalWrite(led1,HIGH);
            digitalWrite(led2,LOW );            
            digitalWrite(led3,LOW );
            digitalWrite(led4,HIGH);
        }
        else if('R' == cmd )
        {
            controller.rotate(!TRIGO);
            digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);            
            digitalWrite(led3,HIGH);
            digitalWrite(led4,LOW);
        }
        else if('S' == cmd )
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

    // (WIP) control wifi : https://www.youtube.com/watch?v=22aYpl-6_-E

    WiFiClient client = server.available(); 
    if (client) 
    {
        Serial.println("nouveau client");
        String ligne = ""; 
        while (client.connected())
        {
            Serial.println("client connecté !");
            if (client.available())
            {
                char c = client.read(); 
                Serial.write(c);
                entete += c;
                if (c == '\n') 
                {
                    if (ligne.length() == 0) 
                    {
                        client.println("HTTP/1.1 200 OK"); 
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        if (entete.indexOf("GET /2/allume") >= 0) 
                        {
                            Serial.println("LED verte allumée");
                            etat_LEDV = "allume"; 
                            digitalWrite(LEDV, HIGH);
                        } 
                        else if (entete.indexOf("GET /2/eteint") >= 0) 
                        {
                            Serial.println("LED verte éteinte");
                            etat_LEDV = "eteint";
                            digitalWrite(LEDV, LOW);
                        }
                        else if (entete.indexOf("GET /1/allume") >= 0) 
                        {
                            Serial.println("LED rouge allumée");
                            etat_LEDR = "allume";
                            digitalWrite(LEDR, HIGH);
                        }
                        else if (entete.indexOf("GET /1/eteint") >= 0) 
                        {
                            Serial.println("LED rouge éteinte");
                            etat_LEDR = "eteint";
                            digitalWrite(LEDR, LOW);
                        }

                        client.println("<!DOCTYPE html><html>");
                        client.print("<head><meta name=\"viewport\" content=\"width=device-width, ");
                        client.println("initial-scale=1\">");

                        client.println("<link rel=\"icon\" href=\"data:,\">");

                        client.print("<style>html { font-family: Helvetica; display: inline-block; ");
                        client.println("margin: 0px auto; text-align: center;}");

                        client.print(".button { background-color: #299886; border: none; ");
                        client.println("color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

                        client.print(".button1 { background-color: #d35845; border: none; color: white; ");
                        client.println("padding: 16px 40px;");

                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button3 {background-color: #f2b2a8;}");
                        client.println(".button2 {background-color: #82d9cb;}</style></head>");

                        client.println("<body><h1>Server web ESP32 </h1>");
                        client.println("<p>LED verte - Etat " + etat_LEDV + "</p>");
                        if (etat_LEDV=="eteint") 
                        {
                            client.println("<p><a href=\"/2/allume\"><button class=\"button\">Allumer</button></a></p>");
                        } 
                        else 
                        {
                            client.print("<p><a href=\"/2/eteint\"><button class=\"button button2\">Eteindre");
                            client.println("</button></a></p>");} 
                            client.println("<p>LED rouge - Etat " + etat_LEDR + "</p>");

                        if (etat_LEDR=="eteint") 
                        {
                            client.print("<p><a href=\"/1/allume\"><button class=\"button button1\">Allumer");
                            client.println("</button></a></p>");

                        } 
                        else 
                        {
                            client.print("<p><a href=\"/1/eteint\"><button class=\"button button3\">Eteindre");
                            client.println("</button></a></p>");

                        }

                        client.println("</body></html>");

                        client.println();
                        break;
                    } 
                    else 
                    { 
                        ligne = "";
                    }
                } 
                else if (c != '\r') 
                {  
                    ligne += c;
                }
            }
        }
        entete = "";
        client.stop(); 
        Serial.println("Client déconnecté !");
        Serial.println("");
    }

}


