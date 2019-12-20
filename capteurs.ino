const int tempSensorPin = A0;
const int lightSensorPin = A2;
const int potPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
 int temperature = analogRead(tempSensorPin);
 int light = analogRead(lightSensorPin);
 int pot = analogRead(potPin);

 Serial.print("temperature : ");
 Serial.print(temperature);
 Serial.println(" °C");
 Serial.print("luminosite : ");
 Serial.println(light);
 Serial.print("potar : ");
 Serial.println(pot);
 delay(3000);
}
