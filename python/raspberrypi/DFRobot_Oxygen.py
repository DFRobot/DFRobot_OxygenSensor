# -*- coding: utf-8 -*
'''!
  @file DFRobot_Oxygen.py
  @brief Define the basic struct of DFRobot_Oxygen class, the implementation of basic method
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0
  @date 2021-10-22
  @url https://github.com/DFRobot/DFRobot_OxygenSensor
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
## GET_KEY_REGISTER_L       = 0x0A  
## GET_KEY_REGISTER_H       = 0x0B  
GET_KEY_REGISTER          = 0x0A
## Register for automatically configuring key-value pairs for the new version
## AUTUAL_SET_REGISTER_L     = 0x0C  
## AUTUAL_SET_REGISTER_H     = 0x0D  
AUTUAL_SET_REGISTER_      = 0x0C
## Register for obtaining probe life
PROBE_LIFE_REGISTER       = 0x0E
## Register for obtaining version number
GET_VERSION_REGISTER      = 0x0F

## Obtain the relevant code for the lifespan API
VERSIO_NERROR              = -1
PROBEN_EXHAUSTED           = 0
PROBEN_NORMAL              = 1

class DFRobot_Oxygen(object):
  ## oxygen key value
  __key      = 0.0
  ## Data value to be smoothed
  __count    = 0
  __txbuf      = [0]
  __oxygendata = [0]*101

  ## Oxygen sensor old version and new version
  old_version = 0x00
  new_version = 0x01

  __version    = 0x01

  def __init__(self, bus):
    self.i2cbus = smbus.SMBus(bus)
    version = self.grt_version()
    if(version == 0xFF):
      self.__version = self.old_version
    elif(version == 0x01):
      self.__version = self.new_version
  def get_flash(self):
    rslt = self.read_reg(GET_KEY_REGISTER, 2)
    temp = (rslt[1] << 8) | rslt[0]

    if temp == 0:
      self.__key = (20.9 / 120.0)
    else:
      self.__key = float(temp) / 1000.0
    time.sleep(0.1)
  
  def calibrate(self, vol, mv):
    '''!
      @brief Calibrate sensor
      @param vol Oxygen concentration unit vol
      @param mv Calibrated voltage unit mv
      @return None
    '''
    key_value = int(vol * 10)
    if (mv < 0.000001) and (mv > (-0.000001)):
      self.__txbuf = [key_value & 0xFF]
      self.write_reg(USER_SET_REGISTER, self.__txbuf)
    else:
      key_value = int((vol / mv) * 1000)
      if self.__version == self.old_version:
        if key_value > 255:
          key_value = 255
        else:
          key_value &= 0xFF
        self.__txbuf = [key_value]
        self.write_reg(AUTUAL_SET_REGISTER, self.__txbuf)
      else:
        self.__txbuf = [key_value & 0xFF, (key_value >> 8) & 0xFF]
        self.write_reg(AUTUAL_SET_REGISTER_, self.__txbuf)

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

  def check_probel_life(self):
    '''!
      @brief Get probe lifespan status
      @return The lifespan status of the sensor probe.
      @n     0: The probe's lifespan has been exhausted.It is recommended to replace the sensor probe.
      @n     1: The probe's lifespan is normal
      @n    -1: The sensor is not a new version, so it does not have the probe lifespan status register.
    '''
    if(self.__version == self.old_version):
      return VERSIO_NERROR
    rslt = self.read_reg(PROBE_LIFE_REGISTER, 1)
    return rslt[0]
  
  def grt_version(self):
    '''!
      @brief Get the version number of the sensor
      @return The version number of the sensor
    '''
    rslt = self.read_reg(GET_VERSION_REGISTER, 1)
    return rslt[0]
  
  def get_current_data(self):
    '''!
      @brief Get current data
      @return Current current data, unit: uA
    '''
    rslt = self.read_reg(OXYGEN_DATA_REGISTER, 3)
    return ((float(rslt[0]) + float(rslt[1]) / 10.0 + float(rslt[2]) / 100.0))

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
