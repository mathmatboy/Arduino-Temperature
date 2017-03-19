#include <LiquidCrystal.h>

float temp;
int tempPin = A0;

LiquidCrystal lcd(12,11,5,4,3,2);

byte thermemetre[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte maison[8] = {
  B00100,
  B01110,
  B11111,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000
};

byte soleil[8] = {
  B00000,
  B10101,
  B01110,
  B11011,
  B01110,
  B10101,
  B00000,
  B00000
};

byte point[8] = {
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
              
void setup() {
  lcd.begin(16,2);// veux dire que mon lcd possede 16 carac 1e ligne 16 carac 2e ligne
    lcd.createChar(1, thermemetre);
    lcd.createChar(2, maison);
    lcd.createChar(3, soleil);
    lcd.createChar(4, point);

}

void loop() {
  temp = analogRead(tempPin);

  float voltage = (temp/1024.0) * 5.0;
  float temperature = (voltage - .5) * 100;

  /*
   * Temperature dans la maison
   */
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.write(2);
  lcd.print(":");
  lcd.print(temperature);
  lcd.write(4);
  lcd.print("C");
  delay(5000); // 1seconde = 1000 miliseconde

  /*
   * Temperature dehors !(Pas terminer)!
   */
  lcd.setCursor(0,1);
  lcd.write(1);
  lcd.write(3);
  lcd.print(":");
  lcd.print("NON DISPO");
  lcd.write(4);
  lcd.print("C");
  delay(5000);

}
