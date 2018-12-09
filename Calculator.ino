
#include <Wire.h> //for I2C lcd
#include <LiquidCrystal_I2C.h> // for I2C LCD
#include <Keypad.h> // for 4x4 keypad
LiquidCrystal_I2C lcd(0x27, 16, 2); // sets the LCD address
const byte ROWS = 4; // sets vaules for rows in COLS.
const byte COLS = 4;
char keys [ROWS] [COLS] = {
  {'1', '2', '3', '/'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', 'C'}, //sets vaules for keypad keys
  {'*', '0', '=', '+'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //gives inputs for keypad rows, cols.
byte colPins[COLS] = {4, 5, 6, 7};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

boolean presentValue = false;
boolean next = false;
boolean final = false;         //for computations
String num1, num2;
int answer;
char op;

void setup()
{
  lcd.init();  //initializes lcd
  lcd.backlight();  //starts backlight
  lcd.setCursor(2, 0); //sets cursor
  lcd.print ("Henry Jones");
  lcd.setCursor(2, 1);
  lcd.print("Honors STEM");
  delay (2500);
  lcd.clear();
  lcd.setCursor (4, 0);
  lcd.print ("Arduino");
  lcd.setCursor (2, 1);
  lcd.print ("Calculator");
  delay (2500);
  lcd.clear ();
  lcd.setCursor (2,0);
  lcd.print ("Instructions:");
  delay (2500);
  lcd.clear ();
  lcd.setCursor (2, 0);
  lcd.print ("A=/ B=- C=C");
  lcd.setCursor (2, 1);
  lcd.print ("D=+ #== *=*");
  delay (5000);
  lcd.clear ();
}
void loop() {
  char key = myKeypad.getKey();
  
if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'))
  {
    if (presentValue != true)
    {
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0);
      lcd.print(num1);
    }
    else
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      lcd.setCursor(15, 0);
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '=') {
    if (op == '+') {
      answer = num1.toInt() + num2.toInt();
    }
    else if (op == '-') {
      answer = num1.toInt() - num2.toInt();
    }
    else if (op == '*') {
      answer = num1.toInt() * num2.toInt();
    }
    else if (op == '/') {
      answer = num1.toInt() / num2.toInt();
    }
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.autoscroll();
    lcd.print(answer);
    lcd.noAutoscroll();
  }
  else if (key != NO_KEY && key == 'C') {
    lcd.clear();
    presentValue = false;
    final = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
  }

}
