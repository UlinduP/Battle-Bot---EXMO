#include <SPI.h>        
#include "RF24.h"    
#include "Wire.h"  

RF24 radio(7, 8);       //CE=7, CSN=8. Can use any other digital pin as well.
const uint64_t pipe = 0xE8E8F0F0E1LL;       //Pipe address


struct package          //Make a struct to store x-y values and weapon states together
{
    int X=512;
    int Y=512;
    int hammer_weapon_input;
    int roller_weapon_switch_state;
};
typedef struct package Package;
Package dataToSend;


const int x_axis_pin = A0;    //Joystick x_axis input
const int y_axis_pin = A1;    //Joystick y_axis input


const int hammer_weapon_button = 3;       //Instantaneous Digital input from push button

const int roller_weapon_switch = 4;       //Continuous Digital input from toggle switch





void setup() 
{
    Serial.begin(9600);
    radio.begin();                  
    radio.openWritingPipe(pipe);                 //Set the address of the receiver to which the program will send data.
    /*
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();                       //To set controller as transmitter
    */

    pinMode(roller_weapon_switch, INPUT_PULLUP);

}


void loop() 
{

    dataToSend.X = analogRead(x_axis_pin);     //Read Joystick X-axis
    dataToSend.Y = analogRead(y_axis_pin);     //Read Joystick Y-axis

    dataToSend.roller_weapon_switch_state = digitalRead(roller_weapon_switch);        //Read state of roller_weapon_switch

    dataToSend.hammer_weapon_input = digitalRead(hammer_weapon_button);        //Read input from hammer_weapon_button

    // For Testing Purposes
    Serial.print("X:");
    Serial.print(dataToSend.X);
    Serial.print("  Y");
    Serial.print(dataToSend.Y);
    Serial.print("  Hammer Weapon Input");
    Serial.print(dataToSend.hammer_weapon_input);
    Serial.print("  Roller_weapon_switch_state");
    Serial.println(dataToSend.roller_weapon_switch_state);

    // Send data to the receiver as a single packet
    radio.write(&dataToSend, sizeof(dataToSend));
    delay(200);

}

