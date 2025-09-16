# -*- coding:utf-8 -*-
'''!
  @file  calibratel_oxygen_sensor.py
  @brief calibrate oxygen sensor.
  @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  @n Then configure the mode of active and passive acquisition, Finally, ozone data can be read.
  @n note: it takes time to stable oxygen concentration, about 3 minutes.
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  version  V1.0
  date  2021-10-22
  @url https://github.com/DFRobot/DFRobot_OxygenSensor
'''
import sys
import time
sys.path.append("../..")
from DFRobot_Oxygen import *

OXYGEN_CONECTRATION = 20.9        # The current concentration of oxygen in the air.
OXYGEN_MV           = 0           # The value marked on the sensor, Do not use must be assigned to 0.
IIC_MODE            = 0x01        # default use IIC1
def setup():
  '''
    The first  parameter is to select iic0 or iic1
    The second parameter is the iic device address
    The default address for iic is ADDRESS_3
    ADDRESS_0                 = 0x70
    ADDRESS_1                 = 0x71
    ADDRESS_2                 = 0x72
    ADDRESS_3                 = 0x73 
  '''
  oxygen = DFRobot_Oxygen_IIC(IIC_MODE ,ADDRESS_3)
  oxygen.calibrate(OXYGEN_CONECTRATION ,OXYGEN_MV)
  print("oxygen calibrate success")
  time.sleep(1)

if __name__ == "__main__":
  setup()