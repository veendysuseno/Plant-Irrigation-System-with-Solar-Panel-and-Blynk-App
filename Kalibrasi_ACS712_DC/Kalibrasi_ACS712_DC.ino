const int sensorpin = 27;
const int mVperAmp = 100; // 100 mV/A output sensitivity
int vmikon = 5000; //tegangan input mikon
int ADC = 0; // variabel bebas
int kalibrasi = 3618; //kalibarasi berdasar nilai vacs pin
double vacs = 0;
double Amps = 0;
double maxAnalog = 4095.00;

void setup() {
  Serial.begin(115200);
  pinMode(sensorpin, INPUT);
}

void loop() {
  ADC = analogRead(sensorpin);
  vacs = ((ADC / maxAnalog) * vmikon); // dalam satuan mV
  Amps = ((vacs - kalibrasi) / mVperAmp);
  if (Amps <= 0) {
    Amps = 0;
  }
  Serial.print("ADC = " ); // shows pre-scaled value
  Serial.print(ADC);
  Serial.print(" | mV = "); // shows the vacs measured
  Serial.print(vacs);
  Serial.print(" | Amps = ");
  Serial.println(Amps, 2);
  delay(500);
}
