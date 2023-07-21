#include <SPI.h>      
#include "RF24.h" 
#include "Wire.h"

RF24 radio(7, 8);     //CE=7, CSN=8. Can use any other digital pin as well.
const uint64_t pipe = 0xE8E8F0F0E1LL;             //Pipe Address


struct package        //Make a struct to store x-y values and weapon states together
{
    int X = 512;
    int Y = 512;
    int hammer_weapon_input = 0;
    int roller_weapon_switch_state = 0;
};
typedef struct package Package;
Package dataReceived;


int hammer_weapon_control_signal = somedigitalpinwithpwm; // Servo Motor Control Signal Pin

// Dangaya Driver - Wheels
#define IN_Speed_Left 3   // to control the speed of the motor  (110 - 255)
#define INA_left 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_left 
#define IN_Speed_Right 6    
#define INA_right 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_right   

//Dangaya Driver - Weapons
#define IN_Speed_Weapon_Front 3   // to control the speed of the motor  (110 - 255)
#define INA_Weapon_Front 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_Weapon_Front 
#define IN_Speed_Weapon_Back 6   
#define INA_Weapon_Back 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_Weapon_Back 

int LMotorSpeed = 85;
int RMotorSpeed = 105; 


void forward();
void backward();
void turn_left();
void turn_right();
void stop();
void motor_speed();
void bring_hammer_down_and_return_up(); 
void roller_weapon_ON(); 
void roller_weapon_OFF();   




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

  pinMode(IN_Speed_Left, OUTPUT);
  pinMode(INA_left, OUTPUT);
  pinMode(INB_left, OUTPUT);

  pinMode(IN_Speed_Right, OUTPUT);
  pinMode(INA_Right, OUTPUT);
  pinMode(INB_Right, OUTPUT);

  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INA_right, HIGH);

  analogWrite(IN_Speed_Left, 255);
  analogWrite(IN_Speed_Right, 255);

  pinMode(IN_Speed_Weapon_Front, OUTPUT);
  pinMode(INA_Weapon_Front, OUTPUT);
  pinMode(INB_Weapon_Front, OUTPUT);

  pinMode(IN_Speed_Weapon_Back, OUTPUT);
  pinMode(INA_Weapon_Back, OUTPUT);
  pinMode(INB_Weapon_Back, OUTPUT);

  ////////////////////
  digitalWrite(INA_Weapon_Front, HIGH);   // Roller rolls at all times
  digitalWrite(INB_Weapon_Front, LOW);
  analogWrite(IN_Speed_Weapon_Front, 255);
  ///////////////////

  digitalWrite(INA_Weapon_Back, HIGH);
  digitalWrite(INB_Weapon_Back, HIGH);

  analogWrite(IN_Speed_Weapon_Back, 255);

  ////////////////////////////////////////////


  delay(400);
}



void loop()
{

    /*----------------------------  Getting Radio Inputs  -------------------------------*/
    
    if (radio.available()) 
    {
        radio.read(&dataReceived, sizeof(dataReceived));

        Serial.print("X:");
        Serial.print(dataReceived.X);
        Serial.print("  Y");
        Serial.print(dataReceived.Y);
        Serial.print("  hammer_weapon_input");
        Serial.print(dataReceived.hammer_weapon_input);
        Serial.print("  Roller_weapon_switch_state");
        Serial.println(dataReceived.roller_weapon_switch_state);
    }

    int xAxis = dataReceived.X;
    int yAxis = dataReceived.Y;

    //For analog input, 600-1023: Forward, 0-400: Backward, 400-600: Do nothing
    int forward = map(yAxis, 600, 1023, 0, 255);  
    int backward = map(yAxis, 400, 0, 0, 255);

    //For analog input,   600-1023: Right,     0-400: Left, 400-600: Do nothing
    int right = map(xAxis, 600, 1023, 0, 255);
    int left = map(xAxis, 400, 0, 0, 255);



    /*------------------------------------  Motion Control  -----------------------------------------*/

    if (yAxis > 600) 
    {   
        forward();   
    } 
    else if (yAxis < 400) 
    {                     
        backward(); 
    } 
    else if (xAxis > 600) 
    {                    
        turn_right();     
    } 
    else if (xAxis < 400) 
    {                     
        turn_left();     
    } 
    else  
    {     
        stop();   
    }



    /*----------------------------------  Hammer Weapon Control  -------------------------------------*/

    //Assuming that 1(HIGH) is read as hammer_weapon_input when the push button is pressed.
    if (hammer_weapon_input == 1 )   
    {
        bring_hammer_down_and_return_up();   
        delay(200);
    }




    /*-----------------------------------  Roller Weapon Control  ------------------------------------*/

    if (roller_weapon_switch_state == true) 
    {
        roller_weapon_ON();     
    } 
    else 
    {
        roller_weapon_OFF();     
    }

}



void forward()
{
  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, LOW);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INB_right, LOW);
  motor_speed();
}

void backward()
{
  digitalWrite(INA_left, LOW);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, LOW);
  digitalWrite(INB_right, HIGH);
  motor_speed();
}

void turn_left()
{
  digitalWrite(INA_left, LOW);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INB_right, LOW);
  motor_speed();
}

void turn_right()
{
  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, LOW);
  digitalWrite(INA_right, LOW);
  digitalWrite(INB_right, HIGH);
  motor_speed();
}

void stop()
{
  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INB_right, HIGH);
}

void motor_speed()
{   
    analogWrite(EN_Speed_Left, LMotorSpeed);
    analogWrite(EN_Speed_Right7, RMotorSpeed);
}

void bring_hammer_down_and_return_up()
{

}

void roller_weapon_ON()
{

}

void roller_weapon_OFF()
{
  
}

