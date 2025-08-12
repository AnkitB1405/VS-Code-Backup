#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22      
#define RELAY_PIN 3
#define HUMIDITY_THRESHOLD 30

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  delay(2000); // DHT22: minimum 2 seconds between readings

  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Error reading sensor!");
    return;
  }

  if (humidity < HUMIDITY_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.print("HUMIDITY LOW: ");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    if (humidity > 60) {
      Serial.print("WARNING! HIGH HUMIDITY: ");
    }
  }

  Serial.print(humidity);
  Serial.println("%;");
}
