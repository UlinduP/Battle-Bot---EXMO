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
Package dataReceived;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";




//DEFINE PINS FOR MOTION-MOTOR DRIVER HERE

//DEFINE PINS FOR ROLLER WEAPON-MOTOR DRIVER HERE

//DEFINE PIN FOR SERVO MOTOR CONTROL HERE




void setup()
{

    /*Communication*/
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.startListening();


    /*
    DEFINE PINMODES HERE FOR,
        MOTION-MOTOR DRIVER PINS
        ROLLER WEAPON-MOTOR DRIVER PINS
        SERVO MOTOR CONTROL PIN
    */


    delay(500);

}




void loop()
{




    /*------------------------------  Getting Radio Inputs  ----------------------------------*/

    if (radio.available()) 
    {
        /*Read the entire struct as a binary packet*/
        radio.read(&dataReceived, sizeof(dataReceived)); 

        /*Display the received values for verification*/
        Serial.print("X: ");
        Serial.print(dataReceived.X);
        Serial.print(", Y: ");
        Serial.print(dataReceived.Y);
        Serial.print(", Roller: ");
        Serial.print(dataReceived.roller_weapon_switch_state);
        Serial.print(", Hammer: ");
        Serial.println(dataReceived.hammer_weapon_input);

        delay(10);
    }




    /*-------------  Mapping Joystick Values to Motion-Motor Driver PWM Values  --------------*/

    int yAxis = dataReceived.Y;
    int xAxis = dataReceived.X;

    /*          Analog Input Range: 0-1023      ,       Analog Output Range: 0-255        */

    //Map analog inputs as follows:- 600-1023: Forward, 0-400: Backward, 400-600: Do nothing (Controller Deadzone)
    int speed_forward   = map(yAxis, 600, 1023, 0, 255);  
    int speed_backwards = map(yAxis, 400, 0, 0, 255);

    //Map analog inputs as follows:- 600-1023: Right  , 0-400: Left    , 400-600: Do nothing (Controller Deadzone)
    int speed_right     = map(xAxis, 600, 1023, 0, 255);
    int speed_left      = map(xAxis, 400, 0, 0, 255);




    /*-------------------------------  Motion Control  --------------------------------------*/

    if (yAxis > 600) 
    {   
        move_forward();     //DEFINE : Use speed_forward value
    } 
    else if (yAxis < 400) 
    {                     
        move_backwards();   //DEFINE : Use speed_backwards value
    } 
    else if (xAxis > 600) 
    {                    
        turn_right();       //DEFINE : Use speed_right value
    } 
    else if (xAxis < 400) 
    {                     
        turn_left();        //DEFINE : Use speed_left value
    } 
    else  
    {     
        stop_moving();      //DEFINE : Give zero velocity to all motion motors
    }




    /*-----------------------------  Hammer Weapon Control  -------------------------------*/

    //Assuming that 1(HIGH) is read as hammer_weapon_input when the push button is pressed.
    if (hammer_weapon_input == 1 )   
    {
        /*
        Since we are using a instantaneous push button here, it might get detected as multiple 
        key presses and not as a single key press. This might be an issue.
        We might need to use some code here to detect only 1 key press and not repeated key presses.
        */
        
        bring_hammer_down_and_return_up();   //DEFINE THIS FUNCTION
        
    }




    /*-----------------------------  Roller Weapon Control  -------------------------------*/

    if (roller_weapon_switch_state == true) 
    {
        roller_weapon_ON();     //DEFINE THIS FUNCTION
    } 
    else 
    {
        roller_weapon_OFF();    //DEFINE THIS FUNCTION
    }




}

