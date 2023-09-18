// Libraries used in this example
#include <Servo.h>

#define TIMEOUT (5000)     // Timeout time in ms, disable this option with values less than 1000ms


// Variable related to the control loop frequency
long previousMillis = 0; // will store last time LED was updated
unsigned long currentMillis = 0;

// Creation of the Servo Library Objects
Servo CH1_motor;
Servo CH2_motor;

// Variables for the PINs
int CH1_pin = 3;
int CH2_pin = 5;

// Variables to store the speed values that will be sent for each motors
int motorCH1speed = 1500; // Fwd 
int motorCH2speed = 1500; // Turn

// Keyboard Command
char keyboardVal;


void setup()
{
    // Buffer between USB & ATmega for LSS-2IO
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);

    // Pin mode for the 4 motor outputs
    pinMode(CH1_pin, OUTPUT);
    pinMode(CH2_pin, OUTPUT);

    // Creation of the "servo" motors
    CH1_motor.attach(CH1_pin);
    CH2_motor.attach(CH2_pin);

    Serial.begin(115200);
}

void loop()
{      
    if(keyboardCapture() || checkTimeOut())
        MOTORupdate();
}

// Stops the motors if no command is received after the "TIMEOUT" time.
// If the "TIMEOUT" value is less than one second this function is disabled.
bool checkTimeOut(){
    if(TIMEOUT < 1000) return false;

    currentMillis = millis();

    if (currentMillis - previousMillis >= TIMEOUT){
        motorCH1speed = 1500;   // stop
        motorCH2speed = 1500;   // stop
        previousMillis = millils();
        return true;
    }
    return false;
}

bool keyboardCapture()
{
    if (Serial.available() > 0)
    {
        keyboardVal = Serial.read();
        updateSpeed(keyboardVal);
        previousMillis = millils();
        return true;
    } // Wait until a character is received
    return false;
    
}

void updateSpeed(char keyboardVal)
{
    switch (keyboardVal)
    {
    case 'w': // Move Forward
    case 'W':
        motorCH1speed = 2000;
        break;
    case 's': // Move Backwards
    case 'S': 
        motorCH1speed = 1000;
        break;
    case 'a': // Turn Left
    case 'A': 
        motorCH2speed = 1000;
        break;
    case 'd': // Turn Right
    case 'D':
        motorCH2speed = 2000;
        break;
    default: // Anything else Stop
        motorCH1speed = 1500;
        motorCH2speed = 1500;
        break;
    }
}

void MOTORupdate()
{
    CH1_motor.writeMicroseconds(motorCH1speed);
    CH2_motor.writeMicroseconds(motorCH2speed);
}
