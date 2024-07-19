#define trigPin A3
#define echoPin A2
#define in1 9 
#define in2 8
#define in3 7 
#define in4 6 
#define enA 10
#define enB 5
#define servo A5
char t;
int distance_F,distance_L,distance_R,Set=15;;
long int tl,tr;
void setup() {
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(3, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
analogWrite(enA, 135);
analogWrite(enB, 135);
Serial.begin(9600);
}

void forward(void) {
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
digitalWrite(in3, LOW); 
digitalWrite(in4, HIGH);
}

void backward(void) {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void turnRight(void) {
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW); 
}

void turnLeft(void) {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void Stop(void) {
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
digitalWrite(3,HIGH);
}

long Ultrasonic_read() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echoPin, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
  if((distance_L <=30) && (distance_R<=30)){
    backward();
    return 0;
  }
  
  else if(distance_L >= distance_R){
  turnLeft();
  delay(1000);
  return 0;
  } 

  else if(distance_R >= distance_L){
  turnRight();
  delay(1000);
  return 0;
   }
}

void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50);
}

void loop() {
delay(10);
servoPulse(servo,70);
distance_F = Ultrasonic_read();
forward();
Serial.println(distance_F);
if(distance_F <= Set){
  if(distance_F <= Set){
  Check_side();
  }
  else{
    forward();
  }
}
delay(10);
}

void Check_side(){
    Stop();
    delay(100);
 for (int angle = 70; angle <= 180; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
  for (int angle = 180; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}
