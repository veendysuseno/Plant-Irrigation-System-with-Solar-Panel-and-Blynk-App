#define ktpin1 27   // GPIO Pin 27 SoilMoisture Sensor ke-1
#define ktpin2 33   // GPIO Pin 35 SoilMoisture Sensor ke-2
#define ktpin3 32   // GPIO Pin 34 SoilMoisture Sensor ke-3
#define relay1 25    // GPIO Pin 5 Relay Channel ke-1
#define relay2 26   // GPIO Pin 18 Relay Channel ke-2
#define relay3 4   // GPIO Pin 19 Relay Channel ke-3
#define relay4 2   // GPIO Pin 23 Relay Channel ke-4

int soil1, soil2, soil3;

void setup() {
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
  Serial.begin(115200);
  digitalWrite(relay1, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay2, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay3, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
  digitalWrite(relay4, HIGH); // Keadaan Mati (Perkabelan menggunakan - Normally Open)
}

void loop() {
  getSoil1();
  getSoil2();
  getSoil3();
  getSoil4();
  Serial.println();
  delay(1000);
}

void getSoil1() {
  soil1 = analogRead(ktpin1);
  soil1 = map(soil1, 4095, 0, 0, 1023);
  Serial.print("KT1 = ");
  Serial.print(soil1);
  Serial.print("bit | ");
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
  Serial.print("KT2 = ");
  Serial.print(soil2);
  Serial.print("bit | ");
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
  Serial.print("KT3 = ");
  Serial.print(soil3);
  Serial.print("bit");
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
