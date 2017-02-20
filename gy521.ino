#include <SPI.h>
#include <Wire.h>
#include "nRF24L01.h"
#include "RF24.h"  


#define MPU 0x68
 byte data[10];
double AcX,AcY,AcZ;
int Pitch, Roll;
const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 nrf(9,10);   
 
void setup(){
  Serial.begin(9600);
  init_MPU(); // Inizializzazione MPU6050
 nrf.begin();    
 nrf.openWritingPipe(pipe);
}
 
void loop()
{
  FunctionsMPU(); // Acquisisco assi AcX, AcY, AcZ.
    
  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);   //Calcolo angolo Roll
  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  //Calcolo angolo Pitch
 
  int ServoRoll = map(Roll, -90, 90, 0, 179);
  int ServoPitch = map(Pitch, -90, 90, 179, 0);
 
 
 // ServoX.write(ServoRoll);
  //ServoY.write(ServoPitch);
  data[0] = ServoPitch; 
  data[1] = ServoRoll; 
 nrf.write(&data, sizeof(data));
 
  Serial.print("Pitch: "); Serial.print(ServoPitch);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(ServoRoll);
  Serial.print("\n");
 
}
 
void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
  delay(1000);
}
 

double FunctionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;
  
  return (int)Value;
}
 
void FunctionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}
