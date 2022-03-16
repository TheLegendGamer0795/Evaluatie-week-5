#include <Blynk.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6 
#define led 3
#define pot 0    
#define DHTTYPE DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE);
#define BLYNK_TEMPLATE_ID "TMPL4nXDFsrL"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "TG93lUFEAES0t4zvCZ7OATtaOVzycuM_"


float temphulp =0;
float val = 0;


void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  lcd.begin();
  lcd.clear();
  lcd.setBacklight(HIGH);
  pinMode(pot,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 31);
  lcd.setCursor(0,0);
  lcd.print("Gew.");
  lcd.setCursor(5,0);
  lcd.print(val);
   
  
   // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    if(event.temperature > temphulp){
     temphulp = event.temperature;  
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    lcd.setCursor(0,1);
    lcd.print("Temp.");
    lcd.setCursor(5,1);
    lcd.print(event.temperature);
  
  }
  }
  
  if(event.temperature > val)
  {
    digitalWrite(led, LOW);
    lcd.setCursor(11,0);
    lcd.print("POMP");
    lcd.setCursor(11,1);
    lcd.print("UIT");
    
  }
    if(event.temperature < val)
  {
     digitalWrite(led, HIGH);
     lcd.setCursor(11,0);
     lcd.print("POMP");
     lcd.setCursor(11,1);
     lcd.print("AAN");
  }
   
}
