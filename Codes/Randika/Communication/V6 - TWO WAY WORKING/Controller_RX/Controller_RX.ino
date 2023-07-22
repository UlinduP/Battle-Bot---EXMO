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

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();
}

void loop() {
    dataToSend.X = 100;
    dataToSend.Y = 200;
    dataToSend.roller_weapon_switch_state = 1;
    dataToSend.hammer_weapon_input = 0;

    radio.write(&dataToSend, sizeof(dataToSend)); // Send the entire struct as a binary packet

    delay(20);
}
