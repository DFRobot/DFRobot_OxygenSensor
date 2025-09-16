/*!
 * @file checkProbeLife.ino
 * @brief Obtain the lifespan of the sensor probe
 * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
 * @n note: The old version of the sensor cannot use the "checkProbeLife" API
 * @n The experimental phenomenon is to print the life status of the sensor probe on the serial port.
 * @n The longer the oxygen sensor probe is used, the lower the measurement accuracy will be. The probe can be replaced for repair.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2021-10-22
 * @url https://github.com/DFRobot/DFRobot_OxygenSensor
 */
#include "DFRobot_OxygenSensor.h"

/**
 * i2c slave Address, The default is ADDRESS_3.
 * ADDRESS_0   0x70  i2c device address.
 * ADDRESS_1   0x71
 * ADDRESS_2   0x72
 * ADDRESS_3   0x73
 */
#define Oxygen_IICAddress ADDRESS_3
DFRobot_OxygenSensor oxygen;

void setup(void) 
{
  Serial.begin(9600);
  while(!oxygen.begin(Oxygen_IICAddress)){
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
}

void loop(void)
{
  /*note:The old version of the sensor cannot use the "checkProbeLife" API*/
  int8_t probeStatus = oxygen.checkProbeLife();

  if(probeStatus == eProbenNormal){
    Serial.println("The sensor probe is normal!");
  }else if(probeStatus == eProbenExhausted){
    Serial.println("The sensor probe is abnormal! It is recommended to replace the sensor probe.");
  }else if(probeStatus == eVersionError){
    Serial.println("This sensor version does not support this function!");
  }
  delay(1000);
}
