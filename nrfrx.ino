#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"           //Modül ile ilgili kütüphaneleri ekliyoruz
#include <Servo.h>
byte data[10];
RF24 nrf(9,10);// nrf pinleri
const uint64_t pipe = 0xE8E8F0F0E1LL;
Servo ServoX,ServoY;
void setup(void){
 Serial.begin(9600);
 ServoX.attach(7);// servo pinleri
 ServoY.attach(8);// servo pinleri
 nrf.begin();
 nrf.openReadingPipe(1,pipe);
 nrf.startListening();

 }

void loop(void){
 if (nrf.available())
 {
   bool done = false;    
   while (!done)
   {
     done = nrf.read(data, sizeof(data));

  Serial.print("Pitch: "); Serial.print(data[0]);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(data[1]);
  Serial.print("\n");

  ServoX.write(data[0]);
 ServoY.write(data[1]);
     delay(10);
   }
 }
 }
