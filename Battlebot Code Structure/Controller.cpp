#include <SPI.h>        
#include "RF24.h"    
#include "Wire.h"  

RF24 radio(7, 8);       //CE=7, CSN=8. Can use any other digital pin as well.
const uint64_t pipe = 0xE8E8F0F0E1LL;       //Pipe address


struct package          //Make a struct to store x-y values together
{
    int X=1;
    int Y=1;
};
typedef struct package Package;
Package pos;


int x_axis_pin = A0;    //Joystick x_axis input
int y_axis_pin = A1;    //Joystick y_axis input


int hammer_weapon_button = 3;       //Instantaneous Digital input from push button
int hammer_weapon_input;

int roller_weapon_switch = 4;       //Continuous Digital input from toggle switch
int roller_weapon_switch_state;




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

    pinMode(roller_weapon_switch, INPUT);        //Or INPUT_PULLUP if no resistors in controller PCB

}


void loop() 
{

    pos.X = analogRead(x_axis_pin);     //Read Joystick X-axis
    pos.Y = analogRead(y_axis_pin);     //Read Joystick Y-axis

    roller_weapon_switch_state = digitalRead(roller_weapon_switch);        //Read state of roller_weapon_switch

    hammer_weapon_input = digitalRead(hammer_weapon_button);        //Read input from hammer_weapon_button

    //For Testing Purposes
    Serial.print("X:");
    Serial.print(pos.X);
    Serial.print("    Y");
    Serial.print(pos.Y);
    Serial.print("    Hammer Weapon Input");
    Serial.print(hammer_weapon_input);
    Serial.print("    Roller_weapon_switch_state");
    Serial.println(roller_weapon_switch_state);

    //Send data to the reciever
    radio.write(&pos, sizeof(pos));   
    radio.write(&roller_weapon_switch_state, sizeof(roller_switch_button_state));
    radio.write(&hammer_weapon_input, sizeof(hammer_weapon_input));
    delay(200);

}

