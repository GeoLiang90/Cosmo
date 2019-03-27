#include <PS4BT.h>
#include <usbhub.h>
#include <math.h>
#include <Adafruit_MotorShield.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
//& Means the address of 
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
Adafruit_MotorShield AFMS = Adafruit_MotorShield();\
//Creating 4 motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

void setup(){
  AFMS.begin();
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
  //Preliminary stuff
  if (PS4.connected()){
    leftSpeed = 0;
    rightSpeed = 0;
    if (PS4.getAnalogHat(LeftHatY)> 128 || PS4.getAnalogHat(LeftHatY) < 128){
       leftSpeed = PS4.getAnalogHat(LeftHatY);
    }
    if (PS4.getAnalogHat(RightHatY)> 128 || PS4.getAnalogHat(RightHatY) < 128){
      rightSpeed = PS4.getAnalogHat(RightHatY);
    }
    tankDrive(leftSpeed,rightSpeed);
    if (leftSpeed > 0 || rightSpeed > 0){
      Serial.print(F("\r\nDriving"));
    }
    else{
      Serial.print(F("\r\nStationary"));
    }
  }
}

int scaleJoystick(int joystickValue){
  double scale = joystickValue/255;
  scale = pow(scale,2);
  return joystickValue * scale;
}

void tankDrive(int leftStickY, int rightStickY){
  //Set default speeds of motor 
  motor1 -> setSpeed(leftStickY);
  motor2 -> setSpeed(leftStickY);
  motor3 -> setSpeed(rightStickY);
  motor4 -> setSpeed(rightStickY);
}
