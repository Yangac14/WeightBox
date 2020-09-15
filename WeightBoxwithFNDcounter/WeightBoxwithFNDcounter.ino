#include<Servo.h>
#define FND_A 2
#define FND_DP 9
long timer = 43200000;
int trigPin = 13;
int echoPin = 11;
long duration;
long distance;
int servoPin = 12;
Servo servo1;

void setup() {
  servo1.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for(int i = FND_A; i<=10; i++){
    pinMode(i, OUTPUT); // pin2-10 output
  }
  Serial.begin(9600);
}
long mstc(long time){
  return time * 0.034/2;
}
boolean digit[10][8] = {
  {1,1,1,1,1,1,0,0}, //0
  {0,1,1,0,0,0,0,0}, //1
  {1,1,0,1,1,0,1,0}, //2
  {1,1,1,1,0,0,1,0}, //3
  {0,1,1,0,0,1,1,0}, //4
  {1,0,1,1,0,1,1,0}, //5
  {1,0,1,1,1,1,1,0}, //6
  {1,1,1,0,0,0,0,1}, //7
  {1,1,1,1,1,1,1,1}, //8
  {1,1,1,0,0,1,1,0}, //9
};
int j = 9;
bool count = false;

void loop() {
  servo1.write(120);
  for(j=9; j>=0; j--){
    count = false;
    for(int i=FND_A; i<= FND_DP; i++){
      digitalWrite(i, digit[j][i-2]);
    }
    while(count != true){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = mstc(duration);
      Serial.print("The distance to the target is: ");
      Serial.print(distance);
      Serial.print(" Centimeters. ");
      if(distance >= 0 && distance <= 5){
        for(int anglle = 120; anglle >= 40; anglle--){
          servo1.write(anglle);
          delay(20);
        }
        count = true;
      }
    }
    delay(5000);
    for(int angle = 40; angle <= 120; angle++){
      servo1.write(angle);
      delay(20);
    }
  }
  delay(timer);  //Delays for half a day when count = true
}
