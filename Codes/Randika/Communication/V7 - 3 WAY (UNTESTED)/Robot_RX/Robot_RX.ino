#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

struct package
{
    int X = 512;
    int Y = 512;
    int hammer_weapon_input = 0;
    int roller_weapon_switch_state = 0;
    int ManualOverride = 0;
};
typedef struct package Package;
Package dataReceived;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.startListening();
}

void loop() 
{
    if (radio.available()) 
    {
        radio.read(&dataReceived, sizeof(dataReceived)); // Read the entire struct as a binary packet

        // Display the received values
        Serial.print("X: ");
        Serial.print(dataReceived.X);
        Serial.print(", Y: ");
        Serial.print(dataReceived.Y);
        Serial.print(", Roller: ");
        Serial.print(dataReceived.roller_weapon_switch_state);
        Serial.print(", Hammer: ");
        Serial.print(dataReceived.hammer_weapon_input);
        Serial.print(", MO: ");
        Serial.println(dataReceived.ManualOverride);

        delay(10);
    }

    if (dataReceived.ManualOverride==2000)
    {
        radio.stopListening();
    }
    
}
