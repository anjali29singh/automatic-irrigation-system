#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define MoistureSensorPin A0 // Soil moisture sensor pin
#define relayPin 9 // Relay control pin
#define buzzer 13

int soilMoistureThreshold = 1000; // Adjust this value based on your sensor and soil type
int pumpDuration = 5000; // Duration for pumping water (in milliseconds)

bool pumpActive = false;

void setup() {
  pinMode(MoistureSensorPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relayPin, OUTPUT);

  lcd.begin(16, 2); // Initialize LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Automatic   ");
  lcd.setCursor(0, 1);
  lcd.print("  Irrigation   ");
  delay(2000); // Display message for 2 seconds
  lcd.clear();
}

void loop() {
  int soilMoisture = analogRead(MoistureSensorPin);
  bool isMoist = (soilMoisture > soilMoistureThreshold);

  if (!isMoist && !pumpActive) {
    digitalWrite(relayPin, HIGH); // Turn on the pump
    pumpActive = true;
    delay(pumpDuration); // Run the pump for a specific duration
    digitalWrite(relayPin, LOW); // Turn off the pump
    pumpActive = false;
  }

  lcd.setCursor(4, 0);
  lcd.print("Soil: ");
  lcd.print(isMoist ? "DRY  " : "MOIST   ");

 
  delay(100); // Delay for stability and responsiveness
}