#include "HttpClient.h"

int  ack_button   = D0;
int  help_button  = D1;
int  standby     = D2;
int  ready       = D3;
int  go          = D4;
int  help        = D5;
int  onboard_led = D7;
bool emergency   = false;
int  current     = 1;
int  curr     = 2;

int i;
String resp = "";

HttpClient http;

http_header_t headers[] = {
    { "Content-Type", "application/json" },
    { "Accept" , "application/json" },
    //{ "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup()
{
    Serial.begin(9600); //debugging
    bool emergency   = false;
    int  current     = 1;
    // Initialize input pins
    pinMode(ack_button, INPUT);
    pinMode(help_button, INPUT);
    // Initialize output pins
    pinMode(standby, OUTPUT);
    pinMode(ready, OUTPUT);
    pinMode(go, OUTPUT);
    pinMode(help, OUTPUT);
    pinMode(onboard_led, OUTPUT);
    String resp = "";

}

void loop()
{
    request.hostname = "ec2-54-148-236-91.us-west-2.compute.amazonaws.com";
//    request.hostname = "www.google.com";
    request.port = 80;
    request.path = "/index.json";
    
    http.get(request, response, headers);
    
    //Serial.print("Application>\tResponse status: ");
    //Serial.println(response.status);
    //Serial.print("Application>\tHTTP Response Body: ");
    //Serial.println(response.body);
    resp = response.body;
    //Serial.println(resp);
    for( i = 0; i < (sizeof(resp) - 1) ; i++) {
        int resp_char = resp[i];
        if (isDigit(resp_char)) {
            current = resp_char - '0';
        }
    }

    if (digitalRead(help_button) == HIGH) {
        emergency = true;
    }
    if (digitalRead(ack_button) == HIGH) {
        digitalWrite(help, LOW);
        emergency = false;
    }
    
    if (emergency == true) {
        digitalWrite(help, HIGH);
        delay(1000);
    } else {
        switch(current) {
            case 1:
                digitalWrite(standby, HIGH);
                delay(1000);
                digitalWrite(standby, LOW);
                //current = 2;
                break;
            case 2:
                digitalWrite(ready, HIGH);
                delay(1000);
                digitalWrite(ready, LOW);
                //current = 3;
                break;
            case 3:
                digitalWrite(go, HIGH);
                delay(1000);
                digitalWrite(go, LOW);
                //current = 1;
                break;
        } //switch
    } //else
}
