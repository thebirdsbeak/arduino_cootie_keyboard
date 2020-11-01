/*
 * Arduino Cootie Morse Keyboard
 * 
 * Craig McIntyre
 * Licensed under GPL 3.0
 *
 * Note - Keyboard.h requires Micro / Leonardo or equivalent
 * 
 */

#include <Keyboard.h>

int ditPin = 2;
int dahPin = 3;
int buzzPin = 10;
int led = 9;
int readyLed = 13;
int spaceLimiter = true;  // This controls whether to add a space
String code = "";
unsigned long timer;
int unit = 50; // Default speed, use to set manually
int uvr = 0;
int unitPin = A0;

void setup() {

Serial.begin(9600);
Keyboard.begin();
pinMode(ditPin, INPUT);
pinMode(dahPin, INPUT);
pinMode(led, OUTPUT);
pinMode(readyLed, OUTPUT);   
pinMode(buzzPin, OUTPUT);
                                                                                      
}

void loop() {

  // Remove these two lines if set speed manually
  uvr = analogRead(unitPin);
  unit = map(uvr, 0, 1023, 30, 200);

 timer = millis();
 while ((millis() - timer) < unit*3) {
   while (digitalRead(ditPin) == LOW) {
    tone(buzzPin, 800, unit);
    digitalWrite(readyLed, LOW);
    digitalWrite(led, HIGH);
    delay(unit);
    digitalWrite(led, LOW);
    delay(unit);
    code += "0";
    timer = millis();
    spaceLimiter = false;
  }
  
    while (digitalRead(dahPin) == LOW) {
    digitalWrite(readyLed, LOW);
    tone(buzzPin, 800, unit*3);
    digitalWrite(led, HIGH);
    delay(unit*3);
    digitalWrite(led, LOW);
    delay(unit);
    code += "1";
    timer = millis();
    spaceLimiter = false;
  }
}

digitalWrite(readyLed, LOW);
digitalWrite(led, LOW);

if (code != "") {
decoder(code);
code = "";
digitalWrite(readyLed, HIGH);

}

else if (spaceLimiter == false) {
Keyboard.print(" ");
spaceLimiter = true;
digitalWrite(readyLed, LOW);
}
}

void decoder(String code) {
  
  static String letters[] = {"01", "1000", "1010", "100", "0", "0010", "110",
                             "0000", "00", "0111", "101", "0100", "11", "10",
                             "111", "0110", "1101","010", "000", "1", "001", 
                             "0001", "011", "1001", "1011", "1100", "E"};

  static String numbers[] = {"11111", "01111", "00111", "00011", "00001",
                             "00000", "10000", "11000", "11100", "11110", "E"};
                             
  int i = 0;                          //counter for letters loop
  int j = 0;                          //counter for numbers loop

  if (code == "010101") {             //manual checks for punctuation           
    Keyboard.print(".");
  }
  else if (code == "110011") {
    Keyboard.print(",");
  }
  else if (code == "001100") {
    Keyboard.print("?");
  }
  else if (code == "10010") {
    Keyboard.print("/");
  }
  else if (code == "011010") {
    Keyboard.print("@");
  }
  else if (code == "1111") {
    Keyboard.print(" ");
  }
  else if (code == "111000") {
    Keyboard.print(";");
  }
  else if (code == "10001") {
    Keyboard.print("=");
  }
  else if (code == "100001") {
    Keyboard.print("-");
  }
  else if (code == "00000000") {
    Keyboard.write(KEY_BACKSPACE); // Note use of .write
    Keyboard.write(KEY_BACKSPACE); // Errors are usually accompanied by unwanted space after
    spaceLimiter = true;
  }
  
  else {
    while (letters[i] != "E") {       //loops letter array for match
      if (letters[i] == code) {     
        Keyboard.print(char('A' + i));     //adds index of the array to 'A' to give letter, replace "A" with "a" for lower case typing
        break;
      }
      i++;
    }
    while (numbers[j] != "E") {       //loops number array for match
      if (numbers[j] == code) {
        Keyboard.print(0 + j);             //adds index of the array to 0 to give number
        break;
      }
      j++;
    }
    if (letters[i] == "E" && numbers[j] == "E") { //do nothing if character not found
      Serial.println("Not found");
      spaceLimiter = true;
    }
  }
  code = "";                          //empty code variable for next loop
}
