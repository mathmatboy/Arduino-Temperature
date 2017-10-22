#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

int i;    //and integer used to count

void setup() {
  
  Serial.begin(9600);
  //Type lcd
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Receiving...");
  delay(1000);
  lcd.clear();
  
    vw_set_rx_pin(A0);       //Sets pin as the RX Pin
    vw_setup(2000);       // Bits per sec
    vw_rx_start();           // Start the receiver PLL running

}

void loop() {
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
   
   if( vw_get_message(buf, &buflen) )
      {
        lcd.setCursor(0,1);
        lcd.print("Temp: ");    
        
       for (i = 0; i < buflen; i++)
         { 
           lcd.write(buf[i]); 
                    
         }
           lcd.print("C");

      }

}
