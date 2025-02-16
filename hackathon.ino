#include <LiquidCrystal.h>
#include <Servo.h>

// Initialize LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo Servo1;

// Sensors & Components
int servoPin = 10;
int sensorPin = A0;       // Flame Sensor (Analog)
int digitalPin = 6;       // Flame Sensor (Digital)
int photoresistorPin = A1; // LDR (Photoresistor) for "Solar Panel Charge"
int redLED = 9;          // Red LED now used for Charging Simulation
const int trigPin = 13;  // Ultrasonic Trig
const int echoPin = 8;   // Ultrasonic Echo
int buzzer = 7;          // Buzzer

// Charge Storage Simulation
float batteryLevel = 0;  // Simulated battery charge (0-100%)
unsigned long lastUpdateTime = 0;  // Store last update time
const int updateInterval = 500; // Charge update every 500ms

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  pinMode(digitalPin, INPUT_PULLUP);
  pinMode(photoresistorPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);
  lcd.print("System Ready!");
  delay(1000);
  lcd.clear();

  Servo1.attach(servoPin);
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Read Flame Sensor
  int fireDetected = digitalRead(digitalPin);  // Read Digital Fire Sensor
  int lightValue = analogRead(photoresistorPin);  // Read Light Level from LDR

  // **Measure Distance using Ultrasonic Sensor**
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Convert LDR reading (0-1023) to a charging rate (0 - 1.5% per cycle)
  float chargeRate = map(lightValue, 0, 1023, 0, 15) / 10.0; // Charge rate 0% to 1.5% per cycle
  float dischargeRate = 0.3; // Slow discharge when no light

  // **Simulated Charging Logic** (Charge every 500ms)
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentMillis; // Update last time

    if (chargeRate > 0.2) { // If light is strong enough
      batteryLevel += chargeRate;  // Slowly charge up
      if (batteryLevel > 100) batteryLevel = 100;  // Max limit
    } else { // If in darkness
      batteryLevel -= dischargeRate;  // Slowly discharge
      if (batteryLevel < 0) batteryLevel = 0;  // Min limit
    }
  }

  // **Fire Detection** - No Red LED for Fire, only buzzer alert
  if (sensorValue < 100) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("🔥 Fire Alert! 🔥");

    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    return; // Skip the rest of the loop
  }

  // **LCD Display Logic**
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Solar Charge");

  lcd.setCursor(0, 1);
  lcd.print("Battery: ");
  lcd.print((int)batteryLevel);
  lcd.print("%");

  if (chargeRate > 0.2) {
    lcd.print(" ⚡"); // Charging symbol
  } else {
    lcd.print(" ⬇"); // Discharging symbol
  }

  int ledBrightness = map(batteryLevel, 0, 100, 1, 255); // Gradual increase
  if (batteryLevel == 0) ledBrightness = 0; // Fully OFF if battery is 0%
  analogWrite(redLED, ledBrightness);

  delay(1000); // Small delay to make display stable

  // **Display Distance on LCD**
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // **Buzzer Alert for Close Object**
  if (distance > 0 && distance < 10) {  // Object detected within 10 cm
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(1000); // Small delay before next loop
}
