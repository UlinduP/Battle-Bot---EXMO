#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

struct package
{
    int X = 512;
    int Y = 512;
    int hammer_weapon_input = 0;
    int roller_weapon_switch_state = 0;
};
typedef struct package Package;
Package dataToSend;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


const int x_axis_pin = A0;    //Joystick x_axis input pin
const int y_axis_pin = A1;    //Joystick y_axis input pin


const int hammer_weapon_button = 3;       //Instantaneous Digital input from push button

const int roller_weapon_switch = 4;       //Continuous Digital input from toggle switch





void setup() 
{

    /*Communication*/
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();

    /*PinMode declaration for 2 switches*/
    pinMode(hammer_weapon_button, INPUT_PULLUP);
    pinMode(roller_weapon_switch, INPUT_PULLUP);

    /*PinMode declaration for Joystick pins*/
    pinMode(x_axis_pin,INPUT);
    pinMode(y_axis_pin,INPUT);

}


void loop() 
{

    /*Getting Inputs*/
    dataToSend.X = analogRead(x_axis_pin);
    dataToSend.Y = analogRead(y_axis_pin);
    dataToSend.roller_weapon_switch_state = digitalRead(roller_weapon_switch);
    dataToSend.hammer_weapon_input = digitalRead(hammer_weapon_button); 

    /*Send the entire struct as a binary packet*/
    radio.write(&dataToSend, sizeof(dataToSend)); 

    delay(20);


    /*Display Transmitted Values for testing purposes*/
    Serial.print("X: ");
    Serial.print(dataToSend.X);
    Serial.print("  Y: ");
    Serial.print(dataToSend.Y);
    Serial.print("  Hammer Weapon Input: ");
    Serial.print(dataToSend.hammer_weapon_input);
    Serial.print("  Roller Weapon Switch State: ");
    Serial.println(dataToSend.roller_weapon_switch_state);

}

