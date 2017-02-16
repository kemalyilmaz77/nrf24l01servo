#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"  

 byte data[3];
int Pitch, Roll;
const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 radio(9,10);   
 
void setup(){
  Serial.begin(9600);

 radio.begin();    

 radio.openWritingPipe(pipe);
  radio.enableDynamicPayloads();
  radio.setAutoAck(true);
  radio.powerUp();
}
 
void loop()
{

 
  int ServoRoll = map(analogRead(1), 0, 1024, 0, 179);
  int ServoPitch = map(analogRead(2), 0, 1024, 179, 0);
 
  data[0] = 0x01; 
  data[1] = ServoPitch; 
  data[2] = ServoRoll; 
 radio.write(&data, sizeof(data));

 /*
  Serial.print("Pitch: "); Serial.print(data[1]);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(data[2]);
  Serial.print("\n");

*/
 
}
 

