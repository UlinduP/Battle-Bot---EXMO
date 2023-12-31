#include <SPI.h>      
#include "RF24.h" 
#include "Wire.h"

RF24 radio(7, 8);     //CE=7, CSN=8. Can use any other digital pin as well.
const uint64_t pipe = 0xE8E8F0F0E1LL;             //Pipe Address


struct package        //Make a struct to store x-y values together
{
    int X=1;
    int Y=1;
};
typedef struct package Package;
Package pos;


int hammer_weapon_input;    
int hammer_weapon_control_signal = 2;   //Servo Motor Control Signal Pin

//DEFINE PINS FOR MOTION-MOTOR DRIVER HERE

int roller_weapon_switch_state;

//DEFINE PINS FOR ROLLER WEAPON-MOTOR DRIVER HERE




void setup()
{
    Serial.begin(9600);
    radio.begin();                      //Start the nRF24 communicate
    radio.openReadingPipe(1, pipe);     //Sets the address of the transmitter to which the program will receive data.
    /*
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    */
    radio.startListening();


    /*
    DEFINE PINMODES HERE FOR,
        MOTION - MOTOR DRIVER CONTROL SIGNALS
        ROLLER WEAPON - MOTOR DRIVER CONTROL SIGNALS
    */


    delay(400);
}



void loop()
{

    /*----------------------------  Getting Radio Inputs  -------------------------------*/
    
    if (radio.available()) 
    {
        radio.read(&pos, sizeof(pos));
        radio.read(&hammer_weapon_input, sizeof(hammer_weapon_input));
        Serial.print("X:");
        Serial.print(pos.X);
        Serial.print("      Y");
        Serial.print(pos.Y);
        Serial.print("      hammer_weapon_input");
        Serial.println(hammer_weapon_input);
    }

    int xAxis = pos.X;
    int yAxis = pos.Y;

    //For analog input, 600-1023: Forward, 0-400: Backward, 400-600: Do nothing
    int forward = map(yAxis, 600, 1023, 0, 255);  
    int backward = map(yAxis, 400, 0, 0, 255);

    //For analog input,   600-1023: Right,     0-400: Left, 400-600: Do nothing
    int right = map(xAxis, 600, 1023, 0, 255);
    int left = map(xAxis, 400, 0, 0, 255);



    /*------------------------------------  Motion Control  -----------------------------------------*/

    if (yAxis > 600) 
    {   
        move_forward();   //DEFINE
    } 
    else if (yAxis < 400) 
    {                     
        move_backwards(); //DEFINE
    } 
    else if (xAxis > 600) 
    {                    
        turn_right();     //DEFINE
    } 
    else if (xAxis < 400) 
    {                     
        turn_left();      //DEFINE
    } 
    else  
    {     
        stop_moving();    //DEFINE
    }



    /*----------------------------------  Hammer Weapon Control  -------------------------------------*/

    //Assuming that 1(HIGH) is read as hammer_weapon_input when the push button is pressed.
    if (hammer_weapon_input == 1 )   
    {
        bring_hammer_down_and_return_up();   //DEFINE
    }




    /*-----------------------------------  Roller Weapon Control  ------------------------------------*/

    if (roller_weapon_switch_state == true) 
    {
        roller_weapon_ON();     //DEFINE
    } 
    else 
    {
        roller_weapon_OFF();    //DEFINE   
    }


}


