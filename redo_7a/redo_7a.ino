
int sensorPin = A0;
int motorPin = 3;
int sensorValue = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead (sensorPin);
  
  int value = map (sensorValue, 630, 300, 255, 0);
  Serial.println (value);
//  analogWrite(motorPin, value);

  if (value >150) { //when it is dark, increase speed as darker
    analogWrite(motorPin, value);
  } else { //when it is bright, stop the motor
    analogWrite(motorPin, 0);
  }
}
