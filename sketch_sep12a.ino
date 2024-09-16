#include "arduino_secrets.h"

#include "thingProperties.h"


int GAS_SENSOR_PIN = A0;
int BATTERY_PIN = A1;

float FUNC_a = 1;
float battery_output = 0;
int max_allowable_gas = 170;



int check_for_fire () {
  gas_reading = analogRead(A0);

  if (gas_reading > max_allowable_gas) {
    fire_output = false;
  } else {
    fire_output = true;
  }
  return gas_reading;
}

int get_battery_charge () { // Get battery capacity remaining.s
  
  battery_output = 0;
  
  // Because voltages are often very variable, averaging it out over a period of time gives a much better result 
  for (int i=0; i<50; i++) { 
    battery_output = battery_output + analogRead(A1);
  }

  battery_output = battery_output / 50;
  int battery_output_raw = battery_output;

  // Converts the battery output to a percentage for contexts that require human readable values. 
  battery_output = (battery_output/850)*100;
  battery_reading = battery_output;
  return battery_output_raw;
}

int get_sleep_cycle () {
  int time_of_day = 12; //Gets the HOUR of the time of day. 
  int battery_charge = get_battery_charge();
  return battery_charge;
}


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);  
  
  // This delay gives the chance to wait for a Serial Monitor without   blocking if none is found
  delay(1500); 
  
  initProperties(); // Defined in thingProperties.h

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Set the pins 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  ArduinoCloud.update(); //Send data to cloud
  // Your code here 
  delay(1000);

  gas_reading = check_for_fire();
  sleep_length = get_sleep_cycle();
  Serial.println(gas_reading);
  Serial.println(sleep_length);  

  
}








/*
  Since GasReading is READ_WRITE variable, onGasReadingChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGasReadingChange()  {
  // Add your code here to act upon GasReading change
}

/*
  Since BatteryReading is READ_WRITE variable, onBatteryReadingChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBatteryReadingChange()  {
  // Add your code here to act upon BatteryReading change
}
/*
  Since FireOutput is READ_WRITE variable, onFireOutputChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFireOutputChange()  {
  // Add your code here to act upon FireOutput change
}
/*
  Since SleepLength is READ_WRITE variable, onSleepLengthChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSleepLengthChange()  {
  // Add your code here to act upon SleepLength change
}