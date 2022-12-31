#include "web_page.h"


void custom_serv_init()
{
    WiFi.begin(ssid,passwd);
    while (WiFi.status()!=WL_CONNECTED)
    {
        delay(500);
        Serial.print("Connecting...");
    }
    Serial.println("Connected to the WiFi network");


    Serial.println(WiFi.localIP()); // IP de la page web
    Serial.println("/");

    
    _server.on("/",handleRoot);
    _server.on("/forward",handle_forward);
    _server.on("/backwad",handle_backward);
    _server.on("/turnLeft",handle_turnLeft);
    _server.on("/turnRight",handle_turnRight);
    _server.on("/Stop",handle_Stop);
    _server.onNotFound(handleNotFound);
    _server.begin();
    Serial.println("Server started");
}


void handleNotFound()
{
    _server.send(404, "text/plain", "404: Not found !");
}

void handleRoot()
{
    String page = "<!DOCTYPE html>";

    page += "<html>";
    page += "<head>";
    page += "<style>";
    page += "html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;} ";
    page += "</style>";
    page += "</head>";
    
    page += "<body>";
    page += "<h1>Server web ESP32 du mini robot</h1>";

    page += "<a href='/backward'>";
    page += "    <button type=\"button\"> Backward    </button>";
    page += "</a>";

    page += "<a href='/turnLeft'>";
    page += "    <button type=\"button\"> Turn Left   </button>";
    page += "</a>";

    page += "<a href='turnRight'>";
    page += "    <button type=\"button\"> Turn Right  </button>";
    page += "</a>";

    page += "<a href='https://www.youtube.com/watch?v=GBIIQ0kP15E'>";
    page += "    <button type=\"button\"> Turbo       </button>";
    page += "</a>";

    
    page += "</body>";
    page += "</html>";

    _server.setContentLength(page.length());
    _server.send(200,"text/html",page);
}

void handle_forward()
{
    CMD = 'F';
    _server.sendHeader("Location","/");
    _server.send(303);
}

void handle_backward()
{
    CMD = 'B';
    _server.sendHeader("Location","/");
    _server.send(303);
}

void handle_turnLeft()
{
    CMD = 'L';
    _server.sendHeader("Location","/");
    _server.send(303);
}

void handle_turnRight()
{
    CMD = 'R';
    _server.sendHeader("Location","/");
    _server.send(303);
}

void handle_Stop()
{
    CMD = 'S';
    _server.sendHeader("Location","/");
    _server.send(303);
}
