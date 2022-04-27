#include <Wire.h> // Librarie of the i2c
#include <VL53L1X.h> // Librarie of the VL53L1X

VL53L1X Distance_Sensor;

void setup()
{
  Wire.begin(); // Start the communication with the sensor 
  Wire.setClock(400000); // Uses 400 khz as the frequency for the i2c

  Serial.begin(115200); // Start serial communication
  Serial.println("VL53L1X Distance Sensor tests in long distance mode(up to 4m)."); // Display at serial monitor the message
  Distance_Sensor.setTimeout(500);
  if (!Distance_Sensor.init())
  {
    Serial.println("Failed to initialize VL53L1X Distance_Sensor!"); // Display at serial monitor the message
    while (1);
  }
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 33 ms for medium and long distance mode
  Distance_Sensor.setDistanceMode(VL53L1X::Long);
  Distance_Sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  Distance_Sensor.startContinuous(50);
}

void loop()
{
  Distance_Sensor.read();
  Serial.print("Distance(mm): "); // Display at serial monitor the message
  Serial.print(Distance_Sensor.ranging_data.range_mm); // Display at serial monitor the sensor values
  Serial.println();
}
