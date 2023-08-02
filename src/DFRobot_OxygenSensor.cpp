/*!
 * @file DFRobot_OxygenSensor.cpp
 * @brief Define the basic struct of DFRobot_OxygenSensor class, the implementation of basic method
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0.1
 * @date 2022-08-02
 * @url https://github.com/DFRobot/DFRobot_OxygenSensor
 */
#include "DFRobot_OxygenSensor.h"

DFRobot_OxygenSensor::DFRobot_OxygenSensor(TwoWire *pWire)
{
  this->_pWire = pWire;
}

DFRobot_OxygenSensor::~DFRobot_OxygenSensor()
{
  this->_pWire = NULL;
}

bool DFRobot_OxygenSensor::begin(uint8_t addr)
{
  this->_addr = addr;
  _pWire->begin();
  _pWire->beginTransmission(_addr);
  if(_pWire->endTransmission() == 0){
    return true;
  }
  return false;
}

void DFRobot_OxygenSensor::readFlash()
{
  uint8_t value = 0;
  _pWire->beginTransmission(_addr);
  _pWire->write(GET_KEY_REGISTER);
  _pWire->endTransmission();
  delay(50);
  _pWire->requestFrom(_addr, (uint8_t)1);
    while (_pWire->available()){
      value = _pWire->read();
    }
  if(value == 0){
    this->_Key = 20.9 / 120.0;
  }else{
    this->_Key = (float)value / 1000.0;
  }
}

void DFRobot_OxygenSensor::i2cWrite(uint8_t reg, uint8_t data)
{
  _pWire->beginTransmission(_addr);
  _pWire->write(reg);
  _pWire->write(data);
  _pWire->endTransmission();
}

void DFRobot_OxygenSensor::calibrate(float vol, float mv)
{
  uint8_t keyValue = vol * 10;
  if(mv < 0.000001 && mv > (-0.000001) ) {
    i2cWrite(USER_SET_REGISTER, keyValue);
  }else {
    keyValue = (vol / mv) * 1000;
    i2cWrite(AUTUAL_SET_REGISTER, keyValue);
  }
}

float DFRobot_OxygenSensor::getOxygenData(uint8_t collectNum)
{
  uint8_t rxbuf[10]={0}, k = 0;
  static uint8_t i = 0, j = 0;
  readFlash();
  if(collectNum > 0){
    for(j = collectNum - 1;  j > 0; j--) {  oxygenData[j] = oxygenData[j-1]; }
    _pWire->beginTransmission(_addr);
    _pWire->write(OXYGEN_DATA_REGISTER);
    _pWire->endTransmission();
    delay(100);
    _pWire->requestFrom(_addr, (uint8_t)3);
      while (_pWire->available()){
        rxbuf[k++] = _pWire->read();
      }
    oxygenData[0] = ((_Key) * (((float)rxbuf[0]) + ((float)rxbuf[1] / 10.0) + ((float)rxbuf[2] / 100.0)));
    if(i < collectNum) i++;
    return getAverageNum(oxygenData, i);
  }else {
    return -1.0;
  }
}

float DFRobot_OxygenSensor::getAverageNum(float bArray[], uint8_t len)
{
  uint8_t i = 0;
  double bTemp = 0;
  for(i = 0; i < len; i++) {
    bTemp += bArray[i];
  }
  return bTemp / (float)len;
}
