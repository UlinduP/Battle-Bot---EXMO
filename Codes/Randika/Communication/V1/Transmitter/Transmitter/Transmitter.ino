//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//create an RF24 object 
RF24 radio(7, 8); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);   //Transmitter RF Power Setting
                                   //MIN=-18dBm, LOW=-12dBm, HIGH=-6dBm, MAX=0dBm.
                                   //above most WiFi frequencies. RF Channel setting 0-125
  radio.setDataRate( RF24_250KBPS );
  //set the address
  radio.openWritingPipe(address);

  //Set module as transmitter
  radio.stopListening();
}

void loop()
{
  //Send message to receiver
  const char text[] = "Welcome to Handson Tech";
  radio.write(&text, sizeof(text));

  delay(500);
  
}
