// for local compiles remove the HttpClient/ section of the include
#include "HttpClient/HttpClient.h"

int  ack_button   = D0;
int  help_button  = D1;
int  standby     = D2;
int  ready       = D3;
int  go          = D4;
int  help        = D5;
int  onboard_led = D7;
bool emergency   = false;
int  current     = 1;

void setup()
{
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

}

void loop()
{
    if (digitalRead(help_button) == HIGH) {
        emergency = true;
    }
    if (digitalRead(ack_button) == HIGH) {
        digitalWrite(help, LOW);
        emergency = false;
    }
    
    if (emergency == true) {
        digitalWrite(help, HIGH);
        delay(250);
    } else {
        switch(current) {
            case 1:
                digitalWrite(standby, HIGH);
                delay(250);
                digitalWrite(standby, LOW);
                delay(250);
                current = 2;
                break;
            case 2:
                digitalWrite(ready, HIGH);
                delay(250);
                digitalWrite(ready, LOW);
                delay(250);
                current = 3;
                break;
            case 3:
                digitalWrite(go, HIGH);
                delay(250);
                digitalWrite(go, LOW);
                delay(250);
                current = 1;
                break;
        } //switch
    } //else
}
