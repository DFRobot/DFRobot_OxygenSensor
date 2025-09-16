# -*- coding:utf-8 -*-
''' 
  @file check_probe_life.py
  @brief Obtain the lifespan of the sensor probe.
  @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  @n note: The old version of the sensor cannot use the "check_probel_life" API
  @n The experimental phenomenon is to print the life status of the sensor probe on the serial port.
  @n The longer the oxygen sensor probe is used, the lower the measurement accuracy will be. The probe can be replaced for repair.
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [JiaLi](zhixin.liu@dfrobot.com)
  version  V1.0
  date  2021-10-22
  @url https://github.com/DFRobot/DFRobot_OxygenSensor
'''
import sys
import time
import math
sys.path.append("../..")
from DFRobot_Oxygen import *

COLLECT_NUMBER   = 10              # collect number, the collection range is 1-100
IIC_MODE         = 0x01            # default use IIC1

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
def loop():

  ## note:The old version of the sensor cannot use the "check_probel_life" API
  probe_status = oxygen.check_probel_life()
  if probe_status == PROBEN_EXHAUSTED:
    print("The sensor probe is abnormal! It is recommended to replace the sensor probe.")
  elif probe_status == PROBEN_NORMAL:
    print("The sensor probe is normal!")
  elif probe_status == VERSIO_NERROR:
    print("This sensor version does not support this function!")
  time.sleep(1)

if __name__ == "__main__":
  while True:
    loop()