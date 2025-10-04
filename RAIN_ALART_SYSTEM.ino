#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define rainPin A0
#define redLED 8
#define greenLED 9
#define buzzer 10

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change if your I2C LCD address is different

void setup() {
  pinMode(rainPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Rain Alert System");
  delay(2000);
}

void loop() {
  int rainValue = analogRead(rainPin);
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  lcd.clear();

  if (rainValue > 800) {  // No Rain
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Status: No Rain");
    delay(1000);  // Hold the display
  }
  else if (rainValue > 400 && rainValue <= 800) {  // Light Rain
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Status: Light ");
    lcd.setCursor(1, 1);
    lcd.print(" Rain ");
    
    // Blink red and green alternately
    digitalWrite(redLED, HIGH);
    delay(250);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    delay(250);
    digitalWrite(greenLED, LOW);
  }
  else {  // Heavy Rain
    lcd.setCursor(0, 0);
    lcd.print("Status:  Heavy ");
    lcd.setCursor(1, 1);
    lcd.print("  Rain ");

    // Blink red LED and buzzer
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    delay(300);

    digitalWrite(greenLED, LOW);
  }
}
