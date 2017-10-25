#include <VirtualWire.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int Sensor1Data;
char Sensor1CharMsg[4];

void setup() {

    Serial.begin(9600);
    
    dht.begin();
    vw_set_ptt_inverted(true);
    vw_set_tx_pin(12);          // Sets pin as the TX pin
    vw_setup(2000); 

}

void loop() {

  Sensor1Data = dht.readTemperature();
  itoa(Sensor1Data,Sensor1CharMsg,10);
  vw_send((uint8_t *)Sensor1CharMsg, strlen(Sensor1CharMsg));
  vw_wait_tx();

    Serial.print("Temperature (oC): ");
    Serial.println(dht.readTemperature());
    
    delay(2000);

}
