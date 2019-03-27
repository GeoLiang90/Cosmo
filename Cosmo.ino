#include <PS4BT.h>
#include <usbhub.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//& Means the address of 
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
//Instance of PS4BT
PS4BT PS4(&Btd, PAIR);

void setup(){
  setup_drivebase();
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop(){
  Usb.Task();
  if (PS4.connected()){
    int left_speed = 0;
    int right_speed = 0;
    if (PS4.getAnalogHat(LeftHatY)> 128 || PS4.getAnalogHat(LeftHatY) < 128){
       left_speed = scale_joystick(PS4.getAnalogHat(LeftHatY));
    }
    if (PS4.getAnalogHat(RightHatY)> 128 || PS4.getAnalogHat(RightHatY) < 128){
      right_speed = scale_joystick(PS4.getAnalogHat(RightHatY));
    }
    tank_drive(left_speed,right_speed);
    if (left_speed > 0 || right_speed > 0){
      Serial.print(F("\r\nDriving"));
    }
    else{
      Serial.print(F("\r\nStationary"));
    }
  }
}
