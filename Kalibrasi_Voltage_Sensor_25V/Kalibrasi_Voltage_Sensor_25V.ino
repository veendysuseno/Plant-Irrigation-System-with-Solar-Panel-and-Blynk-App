const int voltage_Pin = 27;
float Tegangan = 0.00;
float vIN = 0.00;
float R1 = 30000.00; // nilai resistor1 dalam ohm --> Voltage sensor
float R2 = 7500.00; // nilai resistor2 dalam ohm --> Voltage Sensor
float ADC_value = 0;
byte max_Vin = 5;

void setup() {
  Serial.begin(115200);
}

void loop() {
  ADC_value = analogRead(voltage_Pin);
  vIN = (ADC_value * max_Vin  * 4 / 1024.0);
  Tegangan = ((R2 / (R1 + R2) * vIN));
  if (Tegangan <= 1.00) {
    Tegangan = 0.00;
  }
  else {
    Tegangan = ((R2 / (R1 + R2) * vIN) + 1);
  }
  Serial.print("Tegangan = ");
  Serial.print(Tegangan);
  Serial.print(" Volt");
  Serial.println("");
  delay(1000);
}
