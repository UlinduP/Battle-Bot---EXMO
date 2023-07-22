#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis;

void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, addresses);
  //radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  if (radio.available()) {   // If the NRF240L01 module received data
    radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
    xAxis = atoi(&receivedData); // Convert the data from the character array (received X value) into integer
    Serial.print("X : ");
    Serial.print(xAxis);
    delay(10);
    radio.read(&receivedData, sizeof(receivedData));
    yAxis = atoi(&receivedData[0]);
    Serial.print("   Y : ");
    Serial.println(yAxis);
    delay(10);
  }
}
