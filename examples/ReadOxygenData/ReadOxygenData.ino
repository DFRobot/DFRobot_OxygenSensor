 /*!
  * @file  ReadOxygenData.ino
  * @brief Read oxygen concentration ,The unit is concentration percent (% vol).
  * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (OXYGEN_ADDRESS_0 for [0 0]), (OXYGEN_ADDRESS_1 for [1 0]), (OXYGEN_ADDRESS_2 for [0 1]), (OXYGEN_ADDRESS_3 for [1 1]).
  * @n       And then read the data.
  * @n note: it takes time to stable oxygen concentration, about 8 minutes.
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

#define COLLECT_NUMBER    10             // collect number, the collection range is 1-100.
#define OXYGEN_I2C_ADDRESS OXYGEN_ADDRESS_3
/*   iic slave Address, The default is OXYGEN_ADDRESS_3.
       OXYGEN_ADDRESS_0               0x70      // iic device address.
       OXYGEN_ADDRESS_1               0x71
       OXYGEN_ADDRESS_2               0x72
       OXYGEN_ADDRESS_3               0x73
*/

DFRobot_OxygenSensor Oxygen;
void setup() 
{
  Serial.begin(9600);
  while(!Oxygen.begin(OXYGEN_I2C_ADDRESS)) {
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
}

void loop()
{
  float oxygenData = Oxygen.ReadOxygenData(COLLECT_NUMBER);
  Serial.print(" Oxygen concentration is ");
  Serial.print(oxygenData);
  Serial.println(" %vol");
  delay(1000);
}