 /*!
  * @file  CalibrateOxygenSensor.ino
  * @brief Calibrate oxygen sensor.
  * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  * @n       Then calibrate the oxygen sensor
  * @n note: it takes time to stable oxygen concentration, about 10 minutes.
  *
  * @n The experimental phenomenon is that a certain percentage of oxygen concentration is printed on the serial port.
  * @n Because the oxygen concentration in oxygen air is certain, the data will not be greater than 25% vol.
  *
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @licence     The MIT License (MIT)
  * @author      ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version     V0.2
  * @date        2019-10-10
  * @get         from https://www.dfrobot.com
  * @url   */
#include "DFRobot_OxygenSensor.h"

#define Oxygen_IICAddress ADDRESS_3
/*   iic slave Address, The default is ADDRESS_3.
       ADDRESS_0               0x70      // iic device address.
       ADDRESS_1               0x71
       ADDRESS_2               0x72
       ADDRESS_3               0x73
*/
#define OXYGEN_CONECTRATION    20.9      // The current concentration of oxygen in the air.
#define OXYGEN_MV              0         // The value marked on the sensor, Do not use must be assigned to 0.

DFRobot_OxygenSensor Oxygen;
void setup() 
{
  Serial.begin(9600);
  while(!Oxygen.begin(Oxygen_IICAddress)) {
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
  
/*   Choose method 1 or method 2 to calibrate the oxygen sensor.
       1. Directly calibrate the oxygen sensor by adding two parameters to the sensor.
       2. Waiting for stable oxygen sensors for about 10 minutes, 
          OXYGEN_CONECTRATION is the current concentration of oxygen in the air (20.9%mol except in special cases),
          Not using the first calibration method, the OXYGEN MV must be 0.
*/
  Oxygen.Calibrate(OXYGEN_CONECTRATION, OXYGEN_MV);
}

void loop()
{
  Serial.println("The oxygen sensor was calibrated successfully.");
  delay(1000);
}