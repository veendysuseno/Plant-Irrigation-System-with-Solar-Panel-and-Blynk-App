/********************************************************************************************************************************
   Project Penyiram Tanaman dengan Solar Panel dengan aplikasi Blynk
   Board  : ESP32 Dev Module
   Input  : Sensor Soil Moisture, Voltage Sensor, ACS712
   Output : Blynk, LCD, Relay
   Receive: Senin 19 April 2021 (13.00 WIB)
   Proyek IoT - Veenbotronik with ArduinoRasspberry Project
   Ig : Veenbotronik
 *******************************************************************************************************************************/

/************************* Pendefinisian Library *************************/
#define BLYNK_PRINT Serial  //Pendefinisian Serial pada Blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //Library LCD Hardware

/************************* Pin Definition *************************/
#define ktpin1 14   // GPIO Pin 27 SoilMoisture Sensor ke-1
#define ktpin2 33   // GPIO Pin 35 SoilMoisture Sensor ke-2
#define ktpin3 32   // GPIO Pin 34 SoilMoisture Sensor ke-3
#define voltpin1 36 // GPIO Pin 15 Voltage Sensor max 25V ke-1
#define voltpin2 39 // GPIO Pin 0 Voltage Sensor max 25V ke-2
#define aruspin1 34 // GPIO Pin 4 Voltage Sensor max 20A ke-1
#define aruspin2 35 // GPIO Pin 2 Voltage Sensor max 20A ke-1
#define relay1 25    // GPIO Pin 5 Relay Channel ke-1
#define relay2 26   // GPIO Pin 18 Relay Channel ke-2
#define relay3 4   // GPIO Pin 19 Relay Channel ke-3
#define relay4 2   // GPIO Pin 23 Relay Channel ke-4
/*===============================================================*/

/******************* Setting Koneksi IoT Blynk *******************/
char auth[] = "M726dsXSQdwoVgLlZ9P8DYeE8X_NEObt"; //Ganti dengan Token Blynk anda
char ssid[] = "veendy"; // Ganti dengan nama SSID WiFi anda
char pass[] = "t4ny4v33ndy"; // Ganti dengan nama Password WiFi Anda
/*===============================================================*/

/*================== Setting Nilai Kalibrasinya dan samakan nilai dengan Multitester ( BOLEH DIRUBAH SESUAIKAN )==============*/
int kalibrasi1 = 3218; //(Sensor ACS1) Kalibrasi bergantung nilai vacs dan beban
int kalibrasi2 = 3218; //(Sensor ACS1) Kalibrasi bergantung nilai vacs dan beban
//=====================================================================

/******************* Nilai Konstan Sensor ACS712 dan Sensor Voltage (Jangan dirubah) *******************/
float R1 = 30000.00; // nilai resistor1 dalam ohm --> Voltage sensor
float R2 = 7500.00; // nilai resistor2 dalam ohm --> Voltage Sensor
const byte maxvolt = 5;  // tegangan dalam V
const int voltin = 5000; //tegangan dalam mV
const int mVperAmp = 100; // Nilai output sensitivitas 100 mV/A untuk ACS712 max current 20A
//=====================================================================

/******************* Variabel Bebas Penampung Nilai *******************/
int adc1, adc2, soil1, soil2, soil3;
float adc3, adc4, vin1, vin2, vin3, vin4;
float voltage1, voltage2, current1, current2;
//=====================================================================

/******************* Pendeklarasian Variabel Widget LCD Blynk dan LCD Hardware *******************/
WidgetLCD lcd1(V3);  //Widget LCD pada Blynk Aki 1
WidgetLCD lcd2(V4);  //Widget LCD pada Blynk Aki 2
LiquidCrystal_I2C lcdhw1(0x27, 16, 2); //LCD 1 alamat 0x27, default dari modul I2C LCD
LiquidCrystal_I2C lcdhw2(0x21, 16, 2); //LCD 1 alamat 0x21, default dari modul I2C LCD
//A2+A1 dijumper, A0 dibiarkan saja.
//===============================================================================================//

void getSoil1() {
  soil1 = analogRead(ktpin1);
  soil1 = map(soil1, 4095, 0, 0, 1023);
  Blynk.virtualWrite(V0, soil1);//virtual input V0 di Blynk (kelembaban tanah)
  Serial.print("KT1 = ");
  Serial.print(soil1);
  Serial.print("bit | ");
  //Serial.println("");
  if (soil1 <= 300) {
    digitalWrite(relay2, LOW); //selenoid1 ON
  }
  else  {
    digitalWrite(relay2, HIGH); //selenoid1 OFF
  }
}
//=====================================================================

void getSoil2() {
  soil2 = analogRead(ktpin2);
  soil2 = map(soil2, 4095, 0, 0, 1023);
  Blynk.virtualWrite(V1, soil2);//virtual input V1 di Blynk (kelembaban tanah)
  Serial.print("KT2 = ");
  Serial.print(soil2);
  Serial.print("bit | ");
  //Serial.println("");
  if (soil2 <= 300) {
    digitalWrite(relay4, LOW); //selenoid2 ON
  }
  else  {
    digitalWrite(relay4, HIGH); //selenoid2 ON
  }
}
//=====================================================================

void getSoil3() {
  soil3 = analogRead(ktpin3);
  soil3 = map(soil3, 4095, 0, 0, 1023);
  Blynk.virtualWrite(V2, soil3);//virtual input V2 di Blynk (kelembaban tanah)
  Serial.print("KT3 = ");
  Serial.print(soil3);
  Serial.print("bit | ");
  //Serial.println("");
  if (soil3 <= 300) {
    digitalWrite(relay3, LOW); //selenoid3 ON
  }
  else  {
    digitalWrite(relay3, HIGH); //selenoid3 OFF
  }
}
//=====================================================================

void getSoil4() {
  if (soil1 <= 300 || soil2 <= 300 || soil3 <= 300) {
    digitalWrite(relay1, LOW);//pompa ON
  }
  else {
    digitalWrite(relay1, HIGH); //pompa OFF
  }
}
//=====================================================================

void getvolt1() {
  adc1 = analogRead(voltpin1);
  vin1 = (adc1 * maxvolt * 4 / 1024.0);
  voltage1 = ((R2 / (R1 + R2) * maxvolt));
  if (voltage1 <= 1.00) {
    voltage1 = 0.00;
  }
  else {
    voltage1 = ((R2 / (R1 + R2) * maxvolt)); //+1
  }
  Serial.print("Vol1 = ");
  Serial.print(voltage1, 2);
  Serial.print("V |");
  //Serial.println("");
  lcd1.print(0, 1, "V Aki 1 = ");
  lcd1.print(11, 1, voltage1);
  lcd1.print(15, 1, "V");
  lcdhw1.setCursor(0, 1);
  lcdhw1.print("V Aki 1 = ");
  lcdhw1.print(voltage1);
  lcdhw1.setCursor(15, 1);
  lcdhw1.print("V");
}

void getcurrent1() {
  adc3 = analogRead(aruspin1);
  vin3 = ((adc3 / 4095.0) * voltin); //dalam satuan mv
  current1 = ((vin3 - kalibrasi1) / mVperAmp);
  if (current1 <= 0) {
    current1 = 0;
  }
  //  Serial.print("ADC3:");
  //  Serial.print(adc3);
  //  Serial.print(" bit |");
  Serial.print("Curr1 = ");
  Serial.print(current1, 2);
  Serial.print("A |");
  //Serial.println("");
  lcd1.print(0, 0, "I Aki 1 = ");
  lcd1.print(11, 0, current1);
  lcd1.print(15, 0, "A");
  lcdhw1.setCursor(0, 0);
  lcdhw1.print("I Aki 1 = ");
  lcdhw1.print(current1);
  lcdhw1.setCursor(15, 0);
  lcdhw1.print("A");
}

void getvolt2() {
  adc2 = analogRead(voltpin2);
  vin2 = (adc2 * maxvolt * 4 / 1024.0);
  voltage2 = ((R2 / (R1 + R2) * maxvolt));
  if (voltage2 <= 1.00) {
    voltage2 = 0.00;
  }
  else {
    voltage2 = ((R2 / (R1 + R2) * maxvolt)); //+1
  }
  Serial.print("Vol2 = ");
  Serial.print(voltage1, 2);
  Serial.print("V |");
  //Serial.println("");
  lcd2.print(0, 1, "V Aki 2 = ");
  lcd2.print(11, 1, voltage2);
  lcd2.print(15, 1, "V");
  lcdhw2.setCursor(0, 1);
  lcdhw2.print("V Aki 2 = ");
  lcdhw2.print(voltage2);
  lcdhw2.setCursor(15, 1);
  lcdhw2.print("V");
}

void getcurrent2() {
  adc4 = analogRead(aruspin2);
  vin4 = ((adc4 / 4095.0) * voltin); //dalam satuan mv
  current2 = ((vin4 - kalibrasi2) / mVperAmp);
  if (current2 <= 0) {
    current2 = 0;
  }
  //  Serial.print("ADC4:");
  //  Serial.print(adc4);
  //  Serial.print(" bit |");
  Serial.print("Curr2 = ");
  Serial.print(current2, 2);
  Serial.print("A");
  //Serial.println("");
  lcd2.print(0, 0, "I Aki 2 = ");
  lcd2.print(11, 0, current2);
  lcd2.print(15, 0, "A");
  lcdhw2.setCursor(0, 0);
  lcdhw2.print("I Aki 2 = ");
  lcdhw2.print(current2);
  lcdhw2.setCursor(15, 0);
  lcdhw2.print("A");
}

void setup() { //Inisialisasi
  pinMode(voltpin1, INPUT);   // Pin Voltage Sensor 1 sebagai INPUT
  pinMode(voltpin2, INPUT);   // Pin Voltage Sensor 2 sebagai INPUT
  pinMode(aruspin1, INPUT);   // Pin Sensor SoilMoisture 1 sebagai INPUT
  pinMode(aruspin2, INPUT);   // Pin Sensor SoilMoisture 2 sebagai INPUT
  pinMode(ktpin1, INPUT);     // Pin Sensor SoilMoisture 1 sebagai INPUT
  pinMode(ktpin2, INPUT);     // Pin Sensor SoilMoisture 2 sebagai INPUT
  pinMode(ktpin3, INPUT);     // Pin Sensor SoilMoisture 3 sebagai INPUT
  pinMode(relay1, OUTPUT);    //Pompa Air sebagai OUTPUT
  pinMode(relay2, OUTPUT);    //selenoid valve 1 sebagai OUTPUT
  pinMode(relay3, OUTPUT);    //selenoid valve 2 sebagai OUTPUT
  pinMode(relay4, OUTPUT);    //selenoid valve 3 sebagai OUTPUT
  digitalWrite(relay1, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay2, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay3, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay4, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  delay(1000);
  lcdhw1.begin(); //Menjalankan function() dari lcd hardware pada alamat 0x27
  lcdhw2.begin(); //Menjalankan function() dari lcd hardware pada alamat 0x21
  Serial.begin(115200); //Baud rate bisa diubah samakan pada Serial Monitor
  Serial.println();
  //Blynk.begin(auth, ssid, pass); //Function
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,6), 8080);
  delay(1000);
}

void loop() { //Perulangan Function()
  Blynk.run();
  getSoil1(); //Function SoilMoisture1
  getSoil2(); //Function SoilMoisture2
  getSoil3(); //Function SoilMoisture3
  getSoil4(); //Function Kondisi Pompa
  getvolt1(); //Function Sensor Voltage1
  getcurrent1(); //Function Sensor ACS712_20A 1
  getvolt2(); //Function Sensor Voltage2
  getcurrent2(); //Function Sensor ACS712_20A 1
  Serial.println();
}
