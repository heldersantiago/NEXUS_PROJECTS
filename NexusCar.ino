#include <NewPing.h>
#include <SoftwareSerial.h>


#define FORWARD  '1'
#define BACKWARD '2'
#define LEFT_DELAY     '3'
#define RIGHT_DELAY    '4'
#define LEFT '8'
#define RIGHT '9'
#define STOP     '5'
#define SMODE    '6'
#define BTSTATE  12
#define SONARFLAG 7

#define btRx 2
#define btTx 3
#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_OBST_DISTANCE 15

SoftwareSerial bt_Pins(btRx,btTx);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //Ultrasom object instance 

const int  MOTOR_1 = 11;
const int  MOTOR_2 = 10;
const int  MOTOR_3 = 9;
const int  MOTOR_4 = 8;

int MODE = 2;
int sMode = 1;
int state = 5;

class NexusCar{
  public:
    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void _stop();
    int DELAY = 400;

    NexusCar(int motor_1, int motor_2, int motor_3, int motor_4)
    {
       MOTOR_1 = motor_1;
       MOTOR_2 = motor_2;
       MOTOR_3 = motor_3;
       MOTOR_4 = motor_4;   
    }
  
  private:
    int MOTOR_1;
    int MOTOR_2;
    int MOTOR_3;
    int MOTOR_4;
};

void NexusCar::forward()
{ 
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, LOW);
  digitalWrite(MOTOR_3, HIGH);
  digitalWrite(MOTOR_4, LOW);
}

void NexusCar::backward(){
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, HIGH);
  digitalWrite(MOTOR_3, LOW);
  digitalWrite(MOTOR_4, HIGH);
}

void NexusCar::turnLeft(){
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, LOW);
  digitalWrite(MOTOR_3, LOW);
  digitalWrite(MOTOR_4, HIGH);
}

void NexusCar::turnRight(){
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, HIGH);
  digitalWrite(MOTOR_3, HIGH);
  digitalWrite(MOTOR_4, LOW);
}

void NexusCar::_stop(){
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, LOW);
  digitalWrite(MOTOR_3, LOW);
  digitalWrite(MOTOR_4, LOW);
}

NexusCar Car(MOTOR_1, MOTOR_2, MOTOR_3, MOTOR_4);

void setup() {
  Serial.begin(9600);
  bt_Pins.flush();
  bt_Pins.begin(9600);
  pinMode(BTSTATE,INPUT);
  pinMode(SONARFLAG,OUTPUT);
  pinMode(MOTOR_1,OUTPUT);
  pinMode(MOTOR_2,OUTPUT);
  pinMode(MOTOR_3,OUTPUT);
  pinMode(MOTOR_4,OUTPUT);
  digitalWrite(SONARFLAG, HIGH);

}

void loop() {
  
  while(digitalRead(BTSTATE))
  { 
      if(sMode){
        long measuredDistance = sonar.ping_cm();
        if(state == 1 && measuredDistance <= MAX_OBST_DISTANCE)
            Car._stop();
      }
      
      if(bt_Pins.available() > 0)
      {   
        char v = bt_Pins.read();
        
        if(v == FORWARD) { state = 1; }
        if(v == BACKWARD){ state = 2; }
        if(v == LEFT)    { state = 3; }
        if(v == RIGHT)   { state = 4; }
        if(v == STOP)    { state = 5; }
        if(v == LEFT_DELAY) { state = 8; }
        if(v == RIGHT_DELAY) { state = 9; }
        if(v == SMODE){
 
        if(sMode == 0)
             state = 6;
          else
             state = 7;
        }
        
        switch(state)
        {
          case 1:
            Car.forward();
            break;
          case 2:
            Car.backward();
            break;
          case 3:
            Car.turnLeft();
            delay(Car.DELAY);
            Car._stop();
            break;
          case 4:
            Car.turnRight();
            delay(Car.DELAY);
            Car._stop();
            break;
          case 5:
            Car._stop();
            break;
          case 6:
            sMode = 1;
            digitalWrite(SONARFLAG, HIGH);
            break;
          case 7:
            sMode = 0;
            digitalWrite(SONARFLAG, LOW);
            break;
          case 8:
            Car.turnLeft();
            break;
          case 9:
          Car.turnRight();
          break;
          
        }
      }
    }
    Car._stop();
    bt_Pins.flush();
}
