#include <CurieBLE.h>


#include <math.h>
#include "CurieIMU.h"


const int B=4275;                 // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A2;     // Grove - Temperature Sensor connect to A2
/*
   This sketch example partially implements the standard Bluetooth Low-Energy Battery service.
   For more information: https://developer.bluetooth.org/gatt/services/Pages/ServicesHome.aspx
*/

/*  */
BLEPeripheral blePeripheral;                // BLE Peripheral Device (the board you're programming)
BLEService bloodPressureService("2222222222222222");    // Blood Pressure Service
  
BLEUnsignedCharCharacteristic switchCharacteristic("11111111-2222-3333-4444-555555555555", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic newCharacteristic("11111111-2222-3333-3333-555555555555", BLERead | BLEWrite);
int i = 0;

void setup() {
  Serial.begin(9600);       // initialize serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(1000);
  
  blePeripheral.setLocalName("ClickME");
  blePeripheral.setAdvertisedServiceUuid(bloodPressureService.uuid());  // add the service UUID
  blePeripheral.addAttribute(bloodPressureService);   // Add the BLE Blood Pressure service

  blePeripheral.addAttribute(switchCharacteristic);
  blePeripheral.addAttribute(newCharacteristic);
  blePeripheral.begin();
  Serial.println("Bluetooth device active, waiting for connections...");
  

}

void loop() {
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
 
    while (central.connected())
    {
      float ax, ay, az;   //scaled accelerometer values
      float temperature, R;  //temperature value, Resistance
      int a; //temperature sensor
      //************TEMPERATURESECTION*********************************
      a = analogRead(pinTempSensor );  //assign whatever value sensor is reading
      R = 1023.0/((float)a)-1.0;
      R = 100000.0*R;
      temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;    //TEMPERATURE VALUE OUTPUT IN Celsius
      //***********ACCELEROMETERSECTION************************************
      // read accelerometer measurements from device, scaled to the configured range
      CurieIMU.readAccelerometerScaled(ax, ay, az);     //ax value = acceleration in x-axis, ay = y-axis, etc
      Serial.println(sqrt(ax*ax + ay*ay + az*az)*100);
      switchCharacteristic.setValue(sqrt(ax*ax + ay*ay + az*az)*100);
      newCharacteristic.setValue(temperature);
      i++;
    }
    Serial.println("Talking to central");
    
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  } else {
      Serial.println("Not Connected.");
  }
}

