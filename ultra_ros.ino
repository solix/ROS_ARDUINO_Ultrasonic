/* 
 * rosserial::std_msgs::Float64 Test
 * Receives a Float64 input, subtracts 1.0, and publishes it
 */

#include <ros.h>
#include <std_msgs/Int16.h>


ros::NodeHandle nh;

float x; 

// defines pins numbers for sensor 1 US
const int trigPin = A5;
const int echoPin = A4;
int distance =0;

float Distance_test(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(2);
  long duration= pulseIn(echoPin, HIGH);
  int Fdistance = duration*0.034/2;
  
  return Fdistance;
  
}

void messageCb( const std_msgs::Int16& msg){
  x = msg.data - 1.0;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

std_msgs::Int16 test;
ros::Subscriber<std_msgs::Int16> s("arduino_sub", &messageCb);
ros::Publisher p("arduino_pub", &test);

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(echoPin, INPUT);    
  pinMode(trigPin, OUTPUT);  
  nh.initNode();
  nh.advertise(p);
  nh.subscribe(s);
}

void loop()
{
  distance = Distance_test();
  test.data = distance;
  p.publish( &test );
  nh.spinOnce();
  delay(10);
}
