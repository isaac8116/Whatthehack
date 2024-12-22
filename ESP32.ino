// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

DHT dht(DHTPIN, DHTTYPE);


// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

int sensorPin = 11; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 
//LiquidCrystal lcd(9, 9, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {

  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  float temperature = analogRead(34) * 0.1;  // Example for temp sensor

  //sensorValue = analogRead(sensorPin); // read the value from the sensor
  float i = (analogRead(sensorPin)-1300);
  i = i / (4095-1300);
  i = i * 100;

  Serial.print(F("Light intensity Index"));
  Serial.print(i); //prints the values coming from the sensor on the screen
  Serial.print(F("%"));
  Serial.print(F("  Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);


  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print(" H:");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("LI:");
  lcd.print(i);


}