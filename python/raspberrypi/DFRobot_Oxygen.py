# -*- coding: utf-8 -*
""" 
  @file DFRobot_Oxygen.py
  @note DFRobot_Oxygen Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [ZhixinLiu](zhixin.liu@dfrobot.com)
  version  V1.0
  date  2020-5-27
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_Oxygen
"""
import time
import smbus
import os
           
ADDRESS_0                 = 0x70           # iic slave Address
ADDRESS_1                 = 0x71
ADDRESS_2                 = 0x72
ADDRESS_3                 = 0x73

OXYGEN_DATA_REGISTER      = 0x03           # Oxygen data register
USER_SET_REGISTER         = 0x08           # user set key value
AUTUAL_SET_REGISTER       = 0x09           # autual set key value
GET_KEY_REGISTER          = 0x0A           # get key value

class DFRobot_Oxygen(object):
  __key      = 0.0            # oxygen key value
  __count    = 0              # acquisition count
  __txbuf      = [0]          # iic send buffer
  __oxygendata = [0]*101      # ozone data
  def __init__(self ,bus):
    self.i2cbus = smbus.SMBus(bus)

  '''
    @brief get flash value
  '''
  def get_flash(self):
    rslt = self.read_reg(GET_KEY_REGISTER ,1)
    if rslt == 0:
      self.__key = (20.9 / 120.0)
    else:
      self.__key = (float(rslt[0]) / 1000.0)
    time.sleep(0.1)
  
  '''
    @brief calibrate key value
    @param vol oxygen content
    @param mv  the value marked on the sensor
  '''
  def calibrate(self ,vol ,mv):
    self.__txbuf[0] = int(vol * 10)
    if (mv < 0.000001) and (mv > (-0.000001)):
      self.write_reg(USER_SET_REGISTER ,self.__txbuf)
    else:
      self.__txbuf[0] = int((vol / mv) * 1000)
      self.write_reg(AUTUAL_SET_REGISTER ,self.__txbuf)

  '''
    @brief read the oxygen data ,units of vol
    @param collectnum Collect the number
    @return  Oxygen concentration, (units %)
  '''
  def get_oxygen_data(self ,collectnum):
    self.get_flash()
    if collectnum > 0:
      for num in range(collectnum ,1 ,-1):
        self.__oxygendata[num-1] = self.__oxygendata[num-2]
      rslt = self.read_reg(OXYGEN_DATA_REGISTER ,3)
      self.__oxygendata[0] = self.__key * (float(rslt[0]) + float(rslt[1]) / 10.0 + float(rslt[2]) / 100.0)
      if self.__count < collectnum:
        self.__count += 1
      return self.get_average_num(self.__oxygendata ,self.__count)
    elif (collectnum > 100) or (collectnum <= 0):
      return -1

  ''' 
    @brief get the average of the oxygen data ,units of vol
    @param barry ozone data group
    @param Len The number of data
    @return  Oxygen concentration, (units %)
  '''
  def get_average_num(self ,barry ,Len):
    temp = 0.0
    for num in range (0 ,Len):
      temp += barry[num]
    return (temp / float(Len))

'''
  @brief An example of an IIC interface module
'''
class DFRobot_Oxygen_IIC(DFRobot_Oxygen): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    super(DFRobot_Oxygen_IIC, self).__init__(bus)

  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
    self.i2cbus.write_i2c_block_data(self.__addr ,reg ,data)

  '''
    @brief read the data from the register
    @param reg register address
    @param value read data
  '''
  def read_reg(self, reg ,len):
    while 1:
      try:
        rslt = self.i2cbus.read_i2c_block_data(self.__addr ,reg ,len)
        return rslt
      except:
        os.system('i2cdetect -y 1')