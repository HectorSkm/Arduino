#include <Wire.h>

#include <LiquidCrystal_SR.h>

// Defining LCD and Pins for interfacing.

LiquidCrystal_SR lcd(6,5,9); // Pin 6 - Data Enable/ SER, Pin 5 - Clock/SCL, Pin 9 -SCK

void setup()

{

  lcd.begin(16, 2); // Initializing LCD

  lcd.home(); // Setting Cursor at Home i.e. 0,0

}

void loop()

{

  lcd.print("FRANCISCO"); // Print Something on LCD

  delay(2000); // Waiting for a while

  lcd.clear(); // Clearing LCD

  lcd.print("PUES UN MARICON");

  delay(2000);

  lcd.clear();

}
