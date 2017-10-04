#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(A0, DHT11);

RF24 transmit (2,3);
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct package
  {
    float temperature = 0;
    float humidity = 0;
    float rainfall = 0; 
  };

typedef struct package Package;
Package data;

void setup() {
  dht.begin();
  transmit.begin();
  transmit.openWritingPipe(pipe);
  transmit.setPALevel(RF24_PA_MAX);
  transmit.setDataRate(RF24_250KBPS);
  transmit.setChannel(100);
  transmit.stopListening();
  }

void loop() {
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();
  transmit.write(&data,sizeof(data));
  delay(1000);                                 
}
