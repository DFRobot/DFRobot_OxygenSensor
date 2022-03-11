# -*- coding: utf-8 -*
'''!
  @file DFRobot_Oxygen.py
  @brief Define the basic struct of DFRobot_Oxygen class, the implementation of basic method
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0
  @date 2021-10-22
  @url https://github.com/DFRobot/DFRobot_Oxygen
'''
import time
import smbus
import os
           
## I2C address select
ADDRESS_0                 = 0x70
ADDRESS_1                 = 0x71
ADDRESS_2                 = 0x72
ADDRESS_3                 = 0x73
## Register for oxygen data
OXYGEN_DATA_REGISTER      = 0x03
## Register for users to configure key value manually
USER_SET_REGISTER         = 0x08
## Register for automatically configuring key value
AUTUAL_SET_REGISTER       = 0x09
## Register for obtaining key value
GET_KEY_REGISTER          = 0x0A

class DFRobot_Oxygen(object):
  ## oxygen key value
  __key      = 0.0
  ## Data value to be smoothed
  __count    = 0
  __txbuf      = [0]
  __oxygendata = [0]*101
  def __init__(self, bus):
    self.i2cbus = smbus.SMBus(bus)

  def get_flash(self):
    rslt = self.read_reg(GET_KEY_REGISTER, 1)
    if rslt == 0:
      self.__key = (20.9 / 120.0)
    else:
      self.__key = (float(rslt[0]) / 1000.0)
    time.sleep(0.1)
  
  def calibrate(self, vol, mv):
    '''!
      @brief Calibrate sensor
      @param vol Oxygen concentration unit vol
      @param mv Calibrated voltage unit mv
      @return None
    '''
    self.__txbuf[0] = int(vol * 10)
    if (mv < 0.000001) and (mv > (-0.000001)):
      self.write_reg(USER_SET_REGISTER, self.__txbuf)
    else:
      self.__txbuf[0] = int((vol / mv) * 1000)
      self.write_reg(AUTUAL_SET_REGISTER, self.__txbuf)

  def get_oxygen_data(self, collect_num):
    '''!
      @brief Get oxygen concentration
      @param collectNum The number of data to be smoothed
      @n     For example, upload 20 and take the average value of the 20 data, then return the concentration data
      @return Oxygen concentration, unit vol
    '''
    self.get_flash()
    if collect_num > 0:
      for num in range(collect_num, 1, -1):
        self.__oxygendata[num-1] = self.__oxygendata[num-2]
      rslt = self.read_reg(OXYGEN_DATA_REGISTER, 3)
      self.__oxygendata[0] = self.__key * (float(rslt[0]) + float(rslt[1]) / 10.0 + float(rslt[2]) / 100.0)
      if self.__count < collect_num:
        self.__count += 1
      return self.get_average_num(self.__oxygendata, self.__count)
    elif (collect_num > 100) or (collect_num <= 0):
      return -1

  def get_average_num(self, barry, Len):
    temp = 0.0
    for num in range (0, Len):
      temp += barry[num]
    return (temp / float(Len))

class DFRobot_Oxygen_IIC(DFRobot_Oxygen): 
  def __init__(self, bus, addr):
    self.__addr = addr
    super(DFRobot_Oxygen_IIC, self).__init__(bus)

  def write_reg(self, reg, data):
    self.i2cbus.write_i2c_block_data(self.__addr, reg, data)

  def read_reg(self, reg, len):
    while 1:
      try:
        rslt = self.i2cbus.read_i2c_block_data(self.__addr, reg, len)
        return rslt
      except:
        os.system('i2cdetect -y 1')
        time.sleep(1)
