# DFRobot_OxygenSensor
DFRobot's OxygenSensor

## DFRobot_OxygenSensor Library for Arduino
---------------------------------------------------------
Arduino library is provided for reading oxygen concentrations through I2C and gas sensors.
Used to read the ozone and oxygen concentrations of the current module


## Table of Contents

* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

<snippet>
<content>

## Installation

To use this library download the zip file, uncompress it to a folder named DFRobot_OxygenSensor.
Download the zip file first to use this library and uncompress it to a folder named DFRobot_OxygenSensor.

## Methods

```C++
class DFRobot_OxygenSensor{  
public:

 /*
  * @brief initialization parameters for i2c.
  *
  * @param addr is I2c device number.
  *     iic slave Address, The default is ADDRESS 3.
  *     ADDRESS_0               0x70           // iic slave Address
  *     ADDRESS_1               0x71
  *     ADDRESS_2               0x72
  *     ADDRESS_3               0x73
  *
  * @return true and false.
  */
   bool begin(uint8_t addr);

 /*
  * @brief Calibrate Oxygen sensor
  *
  * @param vol is oxygen concentration
  *
  * @param mv  is mv
  *  1. Directly calibrate the oxygen sensor by adding two parameters to the sensor
  *  2. Waiting for stable oxygen sensors for about 10 minutes, 
  *     OXYGEN_CONECTRATION is the current concentration of oxygen in the air (20.9%mol except in special cases) 
  *     Not using the first calibration method, the OXYGEN MV must be 0.
  */
   void Calibrate(float vol, float mv)


 /*
  * @brief read Oxygen data.
  *
  * @return Percent oxygen concentration.
  */
   float ReadOxygenData();
};

```
## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266|      √       |              |             | 
Mega2560  |      √       |             |            | 
Arduino uno |       √      |             |            | 
Leonardo  |      √       |              |             | 




## History

- October 10, 2019 - Version 0.2 released.


## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))