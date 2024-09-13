#define kt 14
#define relay 25

void setup() {
  Serial.begin(9600);
  pinMode(kt, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH); //OFF
}

void loop() {
  int ADC = analogRead(kt);
  ADC = map(ADC, 4095, 0, 0, 1023);
  Serial.print(ADC);
  delay(2000);
  if (ADC <= 300) {
    digitalWrite(relay, LOW); //POMPA ON
  }
  else {
    digitalWrite(relay, HIGH); //POMPA OFF
  }
}
