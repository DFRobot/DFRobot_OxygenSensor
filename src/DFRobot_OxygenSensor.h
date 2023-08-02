/*!
 * @file DFRobot_OxygenSensor.h
 * @brief Define basic struct of DFRobot_OxygenSensor class
 * @details This is an electrochemical oxygen sensor, I2C address can be changed by a dip switch, and the oxygen concentration can be obtained through I2C.
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0.1
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
  
private:
  void readFlash();
  void i2cWrite(uint8_t reg, uint8_t data);
  uint8_t  _addr;                               
  float _Key = 0.0;                          ///< oxygen key value
  float oxygenData[OCOUNT] = {0.00};
  float getAverageNum(float bArray[], uint8_t len);
  TwoWire *_pWire;
};
#endif
