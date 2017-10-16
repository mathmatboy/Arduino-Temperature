#include <VirtualWire.h>
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(A0, DHT11);

float temp;        //Define the temp float variable
char msg[6];

void setup() {
    dht.begin();
    //vw_set_ptt_inverted(true);
    vw_set_tx_pin(12);          // Sets pin D12 as the TX pin
    vw_setup(2000);   

}

void loop() {

    temp = analogRead(dht.readTemperature());
    dtostrf(temp, 6,2,msg);           //convertion float a char
    vw_send((uint8_t *)msg, strlen(msg)); //transmission 
    vw_wait_tx(); // Wait until the whole message is gone

    Serial.println(dht.readTemperature());
    
    delay(200);

}
