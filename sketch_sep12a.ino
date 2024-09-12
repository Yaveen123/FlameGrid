
int GAS_SENSOR_PIN = A0;
int BATTERY_PIN = A1;

int battery_percentage = 0;
int gas_percentage = 0;

void setup() {
  Serial.begin(9600);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  battery_percentage = analogRead(BATTERY_PIN);  
  gas_percentage = analogRead(GAS_SENSOR_PIN);

  Serial.println(gas_percentage);
  Serial.println(battery_percentage);
}