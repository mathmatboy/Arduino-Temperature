#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <LiquidCrystal.h>

RF24 receive (2,3);                         
const uint64_t pipe = 0xE8E8F0F0E1LL;               
LiquidCrystal lcd(8,9,4,5,6,7);

int output_pin10 = 10;
int contrast = 75;

struct package
  {
    float temperature = 0;
    float humidity = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Now Receiving...");
  pinMode(output_pin10, OUTPUT);
  analogWrite(output_pin10, contrast);
  receive.begin();
  receive.openReadingPipe(0,pipe);      
  receive.setPALevel(RF24_PA_MIN);        
  receive.setDataRate(RF24_250KBPS);      
  receive.setChannel(100);                
  receive.startListening();                
  }

void loop() {


  if (receive.available())
  {
    receive.read(&data, sizeof(data));
    lcd.setCursor(0,1);
    lcd.print(data.temperature);
    lcd.print("C ");
    lcd.print(data.humidity);
    lcd.print("H ");
    
  }
}
