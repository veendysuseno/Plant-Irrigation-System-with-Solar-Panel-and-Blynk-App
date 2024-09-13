#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCD 1 alamat 0x27, default dari modul I2C LCD
//jenis LCD 16x2
LiquidCrystal_I2C lcd1(0x27, 16, 2);
//LCD 1 alamat 0x21, default dari modul I2C LCD
//A2+A1 dijumper, A0 dibiarkan saja.
//jenis LCD 16x2
LiquidCrystal_I2C lcd2(0x21, 16, 2);

void setup() {
  lcd1.begin();
  lcd2.begin();
  //aktifkan backlight LCD 1 dan LCD 2
  lcd1.backlight();
  lcd2.backlight();
  //hapus tampilan LCD 1
  lcd1.clear();
  //tulis di LCD 1 baris ke-1
  lcd1.print("LCD I2C ke-1");
  //set cursor LCD 1 ke baris 2
  lcd1.setCursor(0, 1);
  //tulis di LCD 1 baris ke-2
  lcd1.print("LCD Veenbotroonik");

  //hapus tampilan LCD 2
  lcd2.clear();
  //tulis di LCD 2 baris ke-1
  lcd2.print("LCD I2C ke-2");
  //set cursor LCD 2 ke baris 2
  lcd2.setCursor(0, 1);
  //tulis di LCD 2 baris ke-2
  lcd2.print("ArduinoRaspberry");
}


void loop() {
}
