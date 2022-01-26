//Used the code from lecture and modified it to using a photocell

int sensorPin = A0; //photocell
int sensorValue;
int motorSpeed;
int enable = 9;  // PWM pin
int motorPinA = 7;
int motorPinB = 8;

void setup() {
  Serial.begin(9600);
  pinMode(enable, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay (500);
  Serial.println(sensorValue);

  //if the room is bright, sensor value is larger than 20, motor spins forward.
  //because I am using 12V external power supply for the motor and I don't want it to spin so  fast,
  //so I set the highest speed to 60.
  if (sensorValue > 300 && sensorValue < 400) {
    motorSpeed = map(sensorValue, 300, 400, 0, 200);
    forward(motorSpeed);
    
  }

  //if the room is dimmed, sensor value is smaller than 10, motor spins backward.
  if (sensorValue > 500) {
    motorSpeed = map(sensorValue, 500, 700, 0, 200);
    reverse(motorSpeed);
  }
  //if the room is in between, sensor value between 10 and 20, motor stops.
  if (sensorValue  > 400 && sensorValue < 500) {
    brake();
  }

}

void forward(int s) {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  analogWrite(enable, s);

}


void reverse(int s) {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
  analogWrite(enable, s);

}

void brake() {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  digitalWrite(enable, HIGH);

}
