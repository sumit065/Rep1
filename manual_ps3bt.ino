/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>


// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


#include <Sabertooth.h>


USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

//bool printTemperature, printAngle;

Sabertooth ST(128, Serial3); // RX on no pin (unused), TX on pin 11 (to S1).
 

void setup() {
   Serial3.begin(9600);
  
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected){
  int v = 0 , wl = 0, wr = 0 ;
  int w = wl + wr ;
  
  
  int Vin = PS3.getAnalogHat(LeftHatY);
  int WLin  = PS3.getAnalogButton(L2);
  int WRin    = PS3.getAnalogButton(R2);
  
  int Win = WLin - WRin ;
  int power1;
  int power2 ;
  
  //if(Vin < 15 )Vin = 15;
  //else if (Vin > 117 && Vin < 137)Vin = 127 ;
  //else if(Vin > 250)Vin = 250;
  
  
  if(Vin <= 127){
      
      if(Vin < 10)Vin = 10;
      else if(Vin > 117)Vin = 117;
      
      Vin = map(Vin, 10 , 117 , -127 , 0);
  
  }
  
  else if(Vin > 127){
      
    if(Vin < 137) Vin = 137;
    else if (Vin > 245)Vin = 245;
    
    Vin = map(Vin , 137 , 245 , 1 , 127);
  
  }
  if(Win != 0){
  if(Win < -245 ) Win = -245;
  else if (Win > 245) Win = 245;
  
  Win = map(Win , -245 , 245 , -127 , 127);
  
  if( Vin - v < -5 || Vin- v > 5)v = Vin ;
  if( Win - w < -5 || Win- w > 5)w = Win ;
  
  power1 = map(v - w, -254 , 254 , -127 , 127) ;
  power2 = map(v + w, -254 , 254 , -127 , 127) ;
  }
  else{
  power1 = Vin;
  power2 = Vin;
  
  }
  
 


  
  //Serial.println(Win);
 Serial.println(power1);
 Serial.println(power2);
 delay(30);
  
  ST.motor(1 , power1);
  ST.motor(2 , power2);
  
  
  }}
  
 
  

  
 
