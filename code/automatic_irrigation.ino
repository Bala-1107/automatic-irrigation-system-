#include <LiquidCrystal.h>
#include <DHT.h>

// Pin Definitions
#define DHTPIN 2         // DHT11 data pin
#define DHTTYPE DHT11    // DHT sensor type
#define moisturePin A0   // Soil moisture analog pin
#define relayPin 8       // Relay to control motor
#define buzzerPin 9      // Buzzer for alerts

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(moisturePin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Smart Irrigation");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int moisture = analogRead(moisturePin);

  // Display on Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C  Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  Moisture: ");
  Serial.println(moisture);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(moisture);

  // Adjust threshold as needed
  if (moisture < 400) {
    digitalWrite(relayPin, HIGH);  // Motor ON
    digitalWrite(buzzerPin, HIGH); // Buzzer ON
    lcd.setCursor(10, 1);
    lcd.print("WATER");
  } else {
    digitalWrite(relayPin, LOW);   // Motor OFF
    digitalWrite(buzzerPin, LOW);  // Buzzer OFF
    lcd.setCursor(10, 1);
    lcd.print(" OK  ");
  }

  delay(2000);  // Wait 2 seconds
}
