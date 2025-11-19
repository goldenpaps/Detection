#include <Wire.h>          //Required for I2C Communication
#include <arduino.h>

#define IMU 0x1D //Default accelerometer address
                 //If it doesn't work, try 0x1C

int main()
{
  init();


  bool EleDetected = 0;
  short Xin;
  short Yin;
  short Zin;
  char reg;
  short CurX;
  short CurY;
  short CurZ;
  int bits[6];


  Serial.begin(9600);
  Wire.begin();
  delay(500);

  //
  //Check to make sure you can communicate with the device
  //
    //Request register 0x0D
    Wire.beginTransmission(IMU);
      Wire.write(0x0D);
    Wire.endTransmission(false);

    //Read register
    Wire.requestFrom(IMU, 1);
    while(Wire.available())
    {
      reg = Wire.read();
    }

    //Check to make sure returns 0x2A
    if ( reg != 0x2A)
    {
      Serial.print("No Device     ");
      Serial.println(reg);
      delay(100);
      return (1);
    }
    else
      Serial.println("Device is Talking...");
 
  //
  //Put Device in Standby Mode so registers can be changed
  //
    //Request Ctrl Register 1
    Wire.beginTransmission(IMU);
      Wire.write(0x2A);
    Wire.endTransmission(false);

    //Read Ctrl Register 1
    Wire.requestFrom(IMU, 1);
    while(Wire.available())
    {
      reg = Wire.read();
    }

    //Clear ACTIVE bit (LOW) for STDBY mode
    Wire.beginTransmission(IMU);
      Wire.write(0x2A);
      Wire.write(reg & ~(0x01));
    Wire.endTransmission();

  //
  //Set to +/- 2G Range
  //
    //Request XYZ_DATA_CFG Register
    Wire.beginTransmission(IMU);
      Wire.write(0x0E);
    Wire.endTransmission(false);

    //Read Register  
    Wire.requestFrom(IMU, 1);
    while(Wire.available())
    {
      reg = Wire.read();
    }
   
    //Set FS1:0 to 00 For +/- 2g
    Wire.beginTransmission(IMU);
      Wire.write(0x0E);
      Wire.write(reg & ~(0x03));
    Wire.endTransmission();

  //
  //Put Device in Active Mode so it operates
  //
    //Request Ctrl Register 1
    Wire.beginTransmission(IMU);
      Wire.write(0x2A);
    Wire.endTransmission(false);

    //Read Ctrl Register 1
    Wire.requestFrom(IMU, 1);
    while(Wire.available())
    {
      reg = Wire.read();
    }

    //Set ACTIVE bit (HIGH) to exit STDBY
    Wire.beginTransmission(IMU);
      Wire.write(0x2A);
      Wire.write(reg | (0x01));
    Wire.endTransmission();

 
readReg(IMU, 0x01, 6, bits); //device address, register, number of bytes wanted, array

    Xin = ( (short)(bits[0]<<8) | bits[1] )>>4;
    Yin = ( (short)(bits[2]<<8) | bits[3] )>>4;
    Zin = ( (short)(bits[4]<<8) | bits[5] )>>4;




        Serial.print(Xin);
        Serial.print('\t');
       Serial.print(Yin);
        Serial.print('\t');
       Serial.println(Zin);



  while(1)
  {
     readReg(IMU, 0x01, 6, bits); //device address, register, number of bytes wanted, array

    CurX = ( (short)(bits[0]<<8) | bits[1] )>>4;
    CurY = ( (short)(bits[2]<<8) | bits[3] )>>4;
    CurZ = ( (short)(bits[4]<<8) | bits[5] )>>4;




      //  Serial.print(CurX);
       // Serial.print('\t');
     //  Serial.print(CurY);
     ////   Serial.print('\t');
//Serial.println(CurZ);
    delay(100);
     
      if (abs(CurX - Xin) > 100) {
       EleDetected = 1;
      }
      if (abs(CurY - Yin) > 100) {
       EleDetected = 1;
      }
      if (abs(CurZ - Zin) > 100) {
       EleDetected = 1;
      }
     Serial.println(EleDetected);
     EleDetected = 0;
  }
 
  return 0;


}

void readReg(unsigned char dev, unsigned char reg, unsigned char num, int data[]) {
     int i=0;

    Wire.beginTransmission(dev);
    Wire.write(reg);
    Wire.endTransmission(false);
   
    Wire.requestFrom(dev, num);

    while (Wire.available()) {
      data[i] = Wire.read();
      ++i;
    }
  }
