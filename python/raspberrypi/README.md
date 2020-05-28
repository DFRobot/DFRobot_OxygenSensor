# DFRobot Oxygen concentration sensor

This RaspberryPi Oxygen sensor board can communicate with RaspberryPi via IIC.<br>
Oxygen sensor can measure data from 0-30%vol.<br>
Oxygen sensor High precision and wide linear range.<br>
Oxygen sensor Strong anti-interference ability.<br>
Oxygen sensor Excellent repeatability and stability.<br>

## DFRobot Oxygen Library for RaspberryPi

Provide the Raspberry Pi library for the DFRobot_Oxygen module.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)

## Summary

Oxygen module.

## Feature

1. The module has two modes for calibration, one is button calibration, the other is code calibration. <br>
2. Long press the button for calibration. Press the button to determine whether it has been calibrated. <br>
3. Code calibration 10 minutes after the sensor is electrified, the running code will be calibrated successfully. <br>
4. You can measure the concentration of oxygen in the air. <br>

## Installation

This Sensor should work with DFRobot_Oxygen on RaspberryPi. <br>
Run the program:

```
$> python get_oxygen_data.py
$> python calibratel_oxygen_sensor.py
```

## Methods

```py

  def get_ozone_data(self ,collectnum):
    '''
      @brief get the oxygen data,units of vol
      @param collectnum: Collect the number
      @return  Oxygen concentration, (units %)
    '''

  def calibrate(self ,vol ,mv):
    '''
      @brief calibrate key value
      @param vol oxygen content
      @param mv  the value marked on the sensor
  '''

```
## History

May 27, 2020 - Version 1.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2020. (Welcome to our website)