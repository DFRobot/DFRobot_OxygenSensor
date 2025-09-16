# DFRobot_OxygenSensor
- [中文版](./README_CN.md)

The Gravity: I2C Oxygen Sensor is based on electrochemical principles and it can measure the ambient O2 concentration accurately and conveniently. Its effective range is 0~25%Vol. The sensor boasts high precision, high sensitivity, wide linear range, high anti-interference ability, high stability, and good repeatability. When equipped with an I2C interface, the sensor can read the ambient O2 concentration easily, meanwhile, it can also work with various MCU and sensors. This Arduino-compatible oxygen sensor can be widely applied to fields like industries, mines, warehouses, and other spaces where the air is not easy to circulate as well as to measure the oxygen concentration in the environment.

![svg](resources/images/sen0322.jpg)


## Product Link（https://www.dfrobot.com/product-2052.html）

    SKU：SEN0322

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary

* Effective range: 0~25%Vol

* Compatible with both 3.3V and 5V micro-controllers (Note: it can be powered by 5V when using devices of 3.3V)

* Fast calibration function, I2C digital output, reverse connection protection, etc.

## Installation
There are two methods for using this library：
1. Open Arduino IDE, search for "DFRobot_OxygenSensor" on the status bar in Tools ->Manager Libraries and install the library.
2. Download the library file before use, paste it into \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /**
   * @fn begin
   * @brief Initialize i2c
   * @param addr i2c device address
   * @n     Default to use i2c address of 0x70 without passing parameters
   * @return None
   */
  bool begin(uint8_t addr = ADDRESS_0);

  /**
   * @fn calibrate
   * @brief Calibrate oxygen sensor
   * @param vol Oxygen concentration unit vol
   * @param mv Calibrated voltage unit mv
   * @return None
   */
  void calibrate(float vol, float mv = 0);

  /**
   * @fn getOxygenData
   * @brief Get oxygen concentration
   * @param collectNum The number of data to be smoothed
   * @n     For example, upload 20 and take the average value of the 20 data, then return the concentration data.
   * @return Oxygen concentration, unit vol
   */  
  float getOxygenData(uint8_t collectNum);

  /**
   * @fn checkProbeLife
   * @brief Get probe lifespan status
   * @return eProbeLife_t
   * @n     eProbenExhausted    The probe's lifespan has been exhausted.It is recommended to replace the sensor probe.
   * @n     eProbenNormal       The probe's lifespan is normal
   * @n     eVersionError       The sensor is not a new version, so it does not have the probe lifespan status register.
  */
  eProbeLife_t checkProbeLife(void);

  /**
   * getCurrentData
   * @brief Get current data
   * @return Current current data, unit: uA
   */
  float getCurrentData(void);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
Micro:bit          |              |              |      √      |


## History

- 2019/10/25 - V0.2.0 version
- 2021/10/22 - V1.0.0 version
- 2023/08/02 - V1.0.1 version
- 2025/09/15 - V1.0.2 version

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
