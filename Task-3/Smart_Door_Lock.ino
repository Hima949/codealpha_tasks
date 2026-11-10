#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo lockServo;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys),
rowPins, colPins, ROWS, COLS);

String password = "1234";
String enteredPassword = "";

void setup() {
  lcd.begin(16, 2);
  lockServo.attach(10);
  lockServo.write(0);

  lcd.print("Smart Door Lock");
  delay(2000);
  lcd.clear();
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      lcd.clear();

      if (enteredPassword == password) {
        lcd.print("Access Granted");
        lockServo.write(90);
        delay(4000);
        lockServo.write(0);
      } else {
        lcd.print("Wrong Password");
        delay(2000);
      }

      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key == '*') {
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (enteredPassword.length() < 4) {
      enteredPassword += key;
      lcd.setCursor(0, 1);
      lcd.print("****");
    }
  }
}
