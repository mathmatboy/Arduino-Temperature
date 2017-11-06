#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal lcd(12,11,5,4,3,2);

int i;    //and integer used to count

#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/*
 * Icon pour le thermomètre
 */
byte thermemetre[8] = 
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
/*
 * Icon pour la petite maison
 */
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
/*
 * Icon soleil
 */
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
/*
 * Icon Degré Celcius
 */
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

  dht.begin();
  
  Serial.begin(9600);
     sensor_t sensor;
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");


  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Receiving...");
  delay(1000);
  lcd.clear();
  
    vw_set_rx_pin(A0);       //Sets pin as the RX Pin
    vw_setup(2000);       // Bits per sec
    vw_rx_start();           // Start the receiver PLL running

  /*
   * Initialise les Icons
   */
    lcd.createChar(1, thermemetre);
    lcd.createChar(2, maison);
    lcd.createChar(3, soleil);
    lcd.createChar(4, point);

    /*
     * LED ROUGE TRANSMISSION
     */
     pinMode(7, OUTPUT);

}

void loop() {

  /*
   * Console DHT11
   */
    Serial.println("\n");
    Serial.print("Temperature (oC): ");
    Serial.println(dht.readTemperature());

  /*
   * Température dans la maison
   */
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.write(2);
  lcd.print(":");
  lcd.print(dht.readTemperature());
  lcd.write(4);
  lcd.print("C");
  delay(2000);

  /*
   * Temparature dehors 
   */
  
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
   
   if( vw_get_message(buf, &buflen) )
      {
        lcd.setCursor(0,1);
        lcd.write(1);
        lcd.write(3);
        lcd.print(":");  

          digitalWrite(7, HIGH);
        
       for (i = 0; i < buflen; i++)
         { 
           lcd.write(buf[i]); 
                    
         }
           lcd.write(4);
           lcd.print("C");

           delay(1000);
           digitalWrite(7, LOW);

      }

}
