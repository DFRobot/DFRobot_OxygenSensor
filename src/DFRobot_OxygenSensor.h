/*!
 * @file DFRobot_OxygenSensor.h
 * @brief Define basic struct of DFRobot_OxygenSensor class
 * @details This is an electrochemical oxygen sensor, I2C address can be changed by a dip switch, and the oxygen concentration can be obtained through I2C.
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2023-08-02
 * @url https://github.com/DFRobot/DFRobot_OxygenSensor
 */
#ifndef __DFRobot_OxygenSensor_H__
#define __DFRobot_OxygenSensor_H__

#include <Arduino.h>
#include <Wire.h>

#define ADDRESS_0   0x70
#define ADDRESS_1   0x71
#define ADDRESS_2   0x72
#define ADDRESS_3   0x73  ///< iic slave Address select
#define OCOUNT      100   ///< oxygen Count Value
#define OXYGEN_DATA_REGISTER 0x03   ///< register for oxygen data
#define USER_SET_REGISTER    0x08   ///< register for users to configure key value manually
#define AUTUAL_SET_REGISTER  0x09   ///< register that automatically configure key value
#define GET_KEY_REGISTER     0x0A   ///< register for obtaining key value

//      GET_KEY_REGISTER_L 0x0A
//      GET_KEY_REGISTER_H 0x0B
#define AUTUAL_SET_REGISTER_  0x0C ///< Register for automatic configuration of key values in v1.0.2
//      AUTUAL_SET_REGISTER_L = 0xC
//      AUTUAL_SET_REGISTER_H = 0xD
#define PROBE_LIFE_REGISTER  0x0E   ///< register for probe life status
#define VERSION_REGISTER 0x0F   ///< register for obtaining version information

/**
 * @enum eVersion_t
 * @brief Sensor version type
 */
typedef enum{
  eOldVersion = 0x00,
  eNewVersion = 0x01
}eVersion_t;

/**
 * @enum eProbeLife_t
 * @brief Probe lifespan status type
*/
typedef enum{
  eVersionError = -1,
  eProbenExhausted = 0,
  eProbenNormal = 1
}eProbeLife_t;

class DFRobot_OxygenSensor
{
public:
  DFRobot_OxygenSensor(TwoWire *pWire = &Wire);
  ~DFRobot_OxygenSensor();
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
   * @param vol oxygen concentration unit vol
   * @param mv calibrated voltage unit mv
   * @return None
   */
  void calibrate(float vol, float mv = 0);

  /**
   * @fn getOxygenData
   * @brief Get oxygen concentration
   * @param collectNum The number of data to be smoothed
   * @n     For example, upload 20 and take the average value of the 20 data, then return the concentration data
   * @return Oxygen concentration, unit
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
   * @return float current data
   */
  float getCurrentData(void);

private:
  void readFlash();
  void i2cWrite(uint8_t reg, uint8_t data);
  uint8_t  _addr;                               
  uint8_t _version;
  float _Key = 0.0;                          ///< oxygen key value
  float oxygenData[OCOUNT] = {0.00};
  float getAverageNum(float bArray[], uint8_t len);
  uint8_t getVersion(void);
  TwoWire *_pWire;
};
#endif
