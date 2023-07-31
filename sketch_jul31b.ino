#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int doorSensorPin = 27; // Definisikan nomor pin GPIO yang terhubung ke Sensor Pintu MC38

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display
int previousDoorStatus = HIGH; // Variabel untuk menyimpan status pintu sebelumnya, diatur sebagai HIGH untuk memulai
unsigned long lastChangeTime = 0; // Waktu terakhir terjadi perubahan status pintu

void setup()
{
  Wire.begin(14, 13);
  lcd.begin(20, 4);   // initialize the lcd with 20 chars and 4 lines

  pinMode(doorSensorPin, INPUT_PULLUP); // Set pin sensor pintu sebagai INPUT_PULLUP untuk mengaktifkan resistor pull-up internal.
}

void loop()
{
  // Baca status sensor pintu (HIGH = pintu tertutup, LOW = pintu terbuka)
  int doorStatus = digitalRead(doorSensorPin);

  // Cek apakah status pintu berubah
  if (doorStatus != previousDoorStatus) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("STATUS :");
    lcd.setCursor(0, 1);
    if (doorStatus == HIGH)
    {
      lcd.print("PINTU TERBUKA");
    }
    else
    {
      lcd.print("PINTU TERTUTUP");
    }

    // Hidupkan lampu latar LCD
    lcd.backlight();

    // Simpan waktu terakhir perubahan status pintu
    lastChangeTime = millis();

    // Simpan status pintu saat ini sebagai status pintu sebelumnya untuk iterasi berikutnya
    previousDoorStatus = doorStatus;
  }

  // Periksa apakah sudah 10 detik sejak perubahan status terakhir
  if (millis() - lastChangeTime >= 10000) {
    // Matikan lampu latar LCD setelah 10 detik
    lcd.noBacklight();
  }

  // Tunda eksekusi loop selama 500 milidetik (0,5 detik)
  delay(500);
}