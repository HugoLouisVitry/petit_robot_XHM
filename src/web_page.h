#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <WiFi.h>
#include <WebServer.h>

WebServer _server(80);

const char* ssid = "robot";
const char* passwd = "robotcities";

char CMD;

void custom_serv_init();
void handleNotFound();
void handleRoot();
void handle_forward();
void handle_backward();
void handle_turnLeft();
void handle_turnRight();
void handle_Stop();


#endif