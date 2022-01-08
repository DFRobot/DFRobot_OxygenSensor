/*!
 * @file DFRobot_OxygenSensor.h
 * @brief 定义DFRobot_OxygenSensor 类的基础结构
 * @details 这是一个电化学氧气传感器，IIC地址可以由拨码开关改变，可以通过IIC获取氧气浓度
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2019-07-13
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
#define OXYGEN_DATA_REGISTER 0x03   ///< 氧气数据的寄存器
#define USER_SET_REGISTER    0x08   ///< 手动配置key值的寄存器
#define AUTUAL_SET_REGISTER  0x09   ///< 自动配置key值的寄存器
#define GET_KEY_REGISTER     0x0A   ///< 获取key值的寄存器

class DFRobot_OxygenSensor
{
public:
  DFRobot_OxygenSensor();
  ~DFRobot_OxygenSensor();
  /**
   * @fn begin
   * @brief 初始化i2c
   * @param addr i2c的设备地址
   * @n     不传参数默认使用i2c地址0x70
   * @return None
   */
  bool begin(uint8_t addr = ADDRESS_0);

  /**
   * @fn calibrate
   * @brief 校准氧气传感器
   * @param vol 氧气的浓度 单位 vol
   * @param mv 校准的电压 单位 mv
   * @return None
   */
  void calibrate(float vol, float mv = 0);

  /**
   * @fn getOxygenData
   * @brief 获取氧气浓度
   * @param collectNum 平滑数据的个数
   * @n     例如传入20取20个数据进行平均，再返回浓度数据
   * @return 氧气的浓度，单位 vol
   */  
  float getOxygenData(uint8_t collectNum);
  
private:
  void readFlash();
  void i2cWrite(uint8_t reg, uint8_t data);
  uint8_t  _addr;                               
  float _Key = 0.0;                          ///< oxygen key value
  float oxygenData[OCOUNT] = {0.00};
  float getAverageNum(float bArray[], uint8_t len);
};

#endif