#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2
#define LED_HIJAU 3
#define LED_MERAH 4
#define BUZZER 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  sensors.begin();
  
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Termometer");
  lcd.setCursor(0, 1);
  lcd.print("Sistem Alarm...");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  
  if (tempC == DEVICE_DISCONNECTED_C) {
    lcd.print("Error!    ");
  } else {
    lcd.print(tempC, 1);
    lcd.print((char)223);
    lcd.print("C   ");

    // cek batas suhu
    if (tempC >= 20.0 && tempC <= 25.0) {
      // Suhu Rata-rata / Normal
      digitalWrite(LED_HIJAU, HIGH);
      digitalWrite(LED_MERAH, LOW);
      noTone(BUZZER);
      
      lcd.setCursor(0, 1);
      lcd.print("Status: Normal  ");
    } else {
      //fungsi led/ buzzer
      digitalWrite(LED_HIJAU, LOW);
      digitalWrite(LED_MERAH, HIGH);
      tone(BUZZER, 1000);
      
      lcd.setCursor(0, 1);
      if (tempC < 20.0) {
        lcd.print("Status: Dingin! ");
      } else {
        lcd.print("Status: Panas!  ");
      }
    }
  }

  delay(500);
}
