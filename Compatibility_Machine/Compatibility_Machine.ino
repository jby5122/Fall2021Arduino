
int blueLed = 2;
int greenLed = 3;
int redLed = 4;

int sensor1 = A7;
int sensor2 = A6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (blueLed, OUTPUT);
  pinMode (greenLed, OUTPUT);
  pinMode (redLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue1 = analogRead (sensor1);
  int sensorValue2 = analogRead (sensor2);
//  Serial.println ((String)"s1=" + sensorValue1);
//  Serial.println ((String)"s2=" + sensorValue2);
//  delay(1000);

  if (sensorValue1 > 15 && sensorValue2 > 15) { //before two people starting the test
    analogWrite(blueLed, random(0, 255));
    analogWrite(greenLed, random(0, 255));
    analogWrite(redLed, random(0, 255));
    delay(20);

    analogWrite(blueLed, 0);
    analogWrite(greenLed, 0);
    analogWrite(redLed, 0);
    delay (20);
  }
  
  if (sensorValue1 <15 && sensorValue2 <15) { //during the test
    analogWrite(blueLed, 0);
    analogWrite(greenLed, 0);
    analogWrite(redLed, 0);

    //color generation
    int color = random(0, 3); //3 colors
    if (color == 0) {
      analogWrite(blueLed, 150);
    } else if (color == 1) {
      analogWrite(greenLed, 150);
    } else if (color ==2) {
      analogWrite(redLed, 150);
    }
    Serial.println(color);
    exit(0);

//    //reload the loop if they loose fingers
//    for (int i=0; i<255; i++) {
//      if (sensorValue1 >15 && sensorValue2 >15) {
//        break;
//      }
//    }
  }
}
