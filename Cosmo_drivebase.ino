#include <math.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();\
//Creating 4 motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(3);
Adafruit_DCMotor *motor3 = AFMS.getMotor(2);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

void setup_drivebase(){
  AFMS.begin();
  //Set default speed as 0
  motor1 -> setSpeed(0);
  motor2 -> setSpeed(0);
  motor3 -> setSpeed(0);
  motor4 -> setSpeed(0);
  motor1 -> run(RELEASE);
  motor2 -> run(RELEASE);
  motor3 -> run(RELEASE);
  motor4 -> run(RELEASE);
  
}
int invert_value(int motor_speed, int stationary_value){
  int inverted_value = 0;
  if (motor_speed > stationary_value){
    inverted_value = stationary_value - (motor_speed % stationary_value);
  }
  else if (motor_speed < stationary_value){ 
    inverted_value = stationary_value + (motor_speed % stationary_value);
  }
  return inverted_value;
}

int in_deadband(int current_joystick,int lower_bound,int upper_bound){
  if (current_joystick > lower_bound && current_joystick < upper_bound){
    return true;
  }
  return false;
}

int ramp_motor(int start_speed, int target_speed){
  //Currently ramping speed by .01 seconds or 10 milliseconds per unit
  //Increase delay_time for a slower ramp
  double delay_time = 0.1;
  //If iterations is positive ramp up, otherwise ramp down
  int iterations = (target_speed - start_speed)/0.1;
  if (iterations > 0){
    
  }
  else if (iterations < 0){
    
  }
  return 0;
}

int scale_joystick(int joystick_value){
  double scaler = joystick_value/255;
  scaler = pow(scaler,2);
  return int(255 * scaler);
}


void tank_drive(int left_speed, int right_speed){
  int left_d = 128;
  int right_d = 125;
  //Set default speeds of motor
    //Serial.print(F("Running left"));
    int adjusted_val_left = abs(left_d - left_speed) * 2 - 1;
    motor1 -> setSpeed(adjusted_val_left);
    motor2 -> setSpeed(adjusted_val_left);
    if((left_speed < left_d) && !(in_deadband(left_speed,(left_d - 4),(left_d + 4)))){
    motor1 -> run(FORWARD);
    motor2 -> run(BACKWARD);
    }
    else if ((left_speed > left_d) && !(in_deadband(left_speed,(left_d - 4),(left_d + 4)))){
      motor1 -> run(BACKWARD);
      motor2 -> run(FORWARD);
    }
    else{
      motor1 -> run(RELEASE);
      motor2 -> run(RELEASE);
    }
 
   int adjusted_val_right = abs(right_d - right_speed) * 2 - 5;
   motor3 -> setSpeed(adjusted_val_right);
   motor4 -> setSpeed(adjusted_val_right);
   if((right_speed < right_d) && !(in_deadband(right_speed,(right_d - 5),(right_d + 5)))){
    motor3 -> run(FORWARD);
    motor4 -> run(BACKWARD);
    }
    else if ((right_speed > right_d) && !(in_deadband(right_speed,(right_d - 5),(right_d + 5)))){
      motor3 -> run(BACKWARD);
      motor4 -> run(FORWARD);
    }
    else{
      motor3 -> run(RELEASE);
      motor4 -> run(RELEASE);
    }
}
