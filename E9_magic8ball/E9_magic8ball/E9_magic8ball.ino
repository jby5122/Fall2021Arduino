#include <SPI.h>
// include the library code:
#include <LiquidCrystal.h>


/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This code works with the 74HC595 Shift Register
  and the Adafruit LCD screen (sans LCD backpack)

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit wiring:

  LCD pin 1 : ground
  LCD pin 2 : positive voltage
  LCD pin 3 : middle pin of 10K potentiometer
  LCD pin 4 : Shift Register pin 1
  LCD pin 5 : Ground
  LCD pin 6 : Shift Register pin 3
  LCD pin 7 - 10 : no connection
  LCD pin 11 : Shift Register pin 4
  LCD pin 12 : Shift Register pin 5
  LCD pin 13 : Shift Register pin 6
  LCD pin 14 : Shift Register pin 7
  LCD pin 15 : positive voltage
  LCD pin 16 : ground

  Shift Register pin 2 : No connection
  Shift Register pin 9 : No connection
  Shift Register pin 10 : positive voltage
  Shift Register pin 11 : Arduino pin 13   
  Shift Register pin 12 : Arduino pin 9    
  Shift Register pin 13 : ground
  Shift Register pin 14 : Arduino pin 11   
  Shift Register pin 15 : no connection
  Shift Register pin 16 : positive voltage
  
  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 12 Feb 2012
  by Juan Hernandez

  modified 13 November 2021
  by LadyK

  modified 21 November 2021
  by Jiyun Yao
  
  This example code is in the public domain.

 https://playground.arduino.cc/Main/LiquidCrystal/
*/



int sensor = A0;
int sensorValue = 0;
char *categories[] = { "number", "color", "food", "big_decisions"};
char *colors[] = {"White", "Yellow", "Blue", "Red", "Green", "Black", "Brown", "Azure", "Ivory", "Teal", "Silver", "Purple", "Navy blue", "Pea green", "Gray", "Orange", "Maroon", "Charcoal", "Aquamarine", "Coral", "Fuchsia", "Wheat", "Lime", "Crimson", "Khaki", "Hot pink", "Magenta", "Olden", "Plum", "Olive", "Cyan"};
char *foods[] = {"Cheese", "Egg", "Butter", "Margarine", "Yogurt", "Ice cream", "Cream", "Sandwich", "Sausage", "Hamburger", "Hot dog", "Bread", "Pizza", "Steak", "Fish", "Seafood", "Ham", "Kebab", "Bacon", "Sour cream"};
// initialize the library with the number of the sspin
//(or the latch pin of the 74HC595)
LiquidCrystal lcd(9);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
//  lcd.print("hello, world!");
  Serial.begin(9600);

  //heart
  byte Heart[8] = {0b00000,0b01010,0b11111,0b11111,0b01110,0b00100,0b00000,0b00000};
  lcd.createChar(0, Heart);
}

void loop() {
  sensorValue = analogRead (sensor);
  if (sensorValue < 750) { //if user tickle the switch, generate a fortune
    fortune_telling();
  } 
}


void fortune_telling () {
  lcd.clear();
  String sentence = "Your";
  String cate_name = getCategory();
  
  if (cate_name == categories [0]){ //number
     generateNumber();
  }else if (cate_name == categories [1]) { //color
     generateColor();
  }else if (cate_name == categories [2]) { //food
    generateFood();
  }else if (cate_name == categories [3]) { //big decision
    generateDecision();
  }
  Serial.println (cate_name);
}

String getCategory() {
  int probability = random (0, 10);
  if (probability <3) {
    return categories [0];
  }else if (probability >=3 && probability <6) {
    return categories [1];
  }else if (probability >=6 && probability <9) {
    return categories [2];
  }else {
    return categories [3];
  }
}

void generateNumber(){ //generate a fortune with number
  int number = random (0,100);
  String sentence1 = "Lucky number";
  String sentence2 = String("is ") + String(number);
  print_sentence(sentence1, sentence2, 0);
}

void generateColor(){ //generate a fortune with color
  String color = colors[random (0, 31)];
  String sentence1 = "Your lucky color";
  String sentence2 = String("is ") + String(color);
  print_sentence(sentence1, sentence2, 0);
}

void generateFood(){ //generate a fortune with food
  String food = foods[random (0, 20)];
  String sentence1 = "You should eat";
  String sentence2 = String(food) + String(" today");
  print_sentence(sentence1, sentence2, 0);
}

void generateDecision(){ //generate a "Let's go!!!!" decision
  String sentence1 = "Tell your crush";
  String sentence2 = "your feeling!";
  print_sentence(sentence1, sentence2, 1);
}

//Print sentence function
void print_sentence (String sentence1, String sentence2, int emoji) {
  lcd.setCursor(0, 0);
  lcd.print(sentence1);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(sentence2);

  if (emoji == 1) {
    lcd.setCursor(sentence2.length()+1, 1);
    lcd.write(byte(0));
  }
}
