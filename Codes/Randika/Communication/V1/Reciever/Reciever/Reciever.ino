//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  while (!Serial)
  {
    Serial.begin(9600);
  }

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);     //Transmitter RF Power Setting
                                     //MIN=-18dBm, LOW=-12dBm, HIGH=-6dBm, MAX=0dBm.
  
  radio.setChannel(108);             //above most WiFi frequencies. RF Channel setting 0-125
  radio.setDataRate( RF24_250KBPS ) ;
  radio.openReadingPipe(0, address); //set the address

  radio.startListening();            //Set module as receiver
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
