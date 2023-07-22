//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object 
RF24 radio(9, 8); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00002";

void setup()
{
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);   //Transmitter RF Power Setting
                                    //MIN=-18dBm, LOW=-12dBm, HIGH=-6dBm, MAX=0dBm.
                                    //above most WiFi frequencies. RF Channel setting 0-125
  radio.setDataRate( RF24_250KBPS );
  radio.openWritingPipe(address);   //set the address

  radio.stopListening();            //Set module as transmitter     
}

void loop()
{
  //Send message to receiver
  const char text[] = "I am the second transmitter";
  radio.write(&text, sizeof(text));

  delay(500);
}
