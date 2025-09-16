/*!
 * @file DFRobot_OxygenSensor.cpp
 * @brief Define the basic struct of DFRobot_OxygenSensor class, the implementation of basic method
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
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
    uint8_t version = getVersion();
    if(version == 0xFF){
      this->_version = eOldVersion;
    }else if(version == 0x01){
      this->_version = eNewVersion;
    }
    return true;
  }
  return false;
}

void DFRobot_OxygenSensor::readFlash()
{
  uint8_t value[2] ={0};
  _pWire->beginTransmission(_addr);
  _pWire->write(GET_KEY_REGISTER);
  _pWire->endTransmission();
  delay(50);
  _pWire->requestFrom(_addr, (uint8_t)2);
  int i = 0;
  while (_pWire->available()){
    value[i++] = _pWire->read();
  }
  uint16_t temp = ((uint16_t)value[1] << 8) | value[0];
  if(temp == 0){
    this->_Key = 20.9 / 120.0;
  }else{
    this->_Key = (float)temp / 1000.0;
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
  uint16_t keyValue = vol * 10;
  uint8_t keytemp = 0;
  if(mv < 0.000001 && mv > (-0.000001) ) {
    keytemp = ((uint8_t)keyValue & 0xff);
    i2cWrite(USER_SET_REGISTER, keytemp);
  }else {
    keyValue = (vol / mv) * 1000;
    if(_version == eOldVersion){
      if(keyValue <= 255){
        keytemp = ((uint8_t)keyValue & 0xff);
      }else{
        keytemp = 255;
      }
      i2cWrite(AUTUAL_SET_REGISTER, keytemp);
    }else{
      _pWire->beginTransmission(_addr);
      _pWire->write(AUTUAL_SET_REGISTER_);
      _pWire->write(keyValue & 0xFF);
      _pWire->write((keyValue >> 8) & 0xFF);
      _pWire->endTransmission();
    }
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

eProbeLife_t DFRobot_OxygenSensor::checkProbeLife(void)
{
  int8_t value = 0;
  if(_version == eOldVersion){
    return eVersionError;
  }
  _pWire->beginTransmission(_addr);
  _pWire->write(PROBE_LIFE_REGISTER);
  _pWire->endTransmission();
  _pWire->requestFrom(_addr, (uint8_t)1);
  if(_pWire->available()){
    value = _pWire->read();
  }
  return (eProbeLife_t)value;
}

uint8_t DFRobot_OxygenSensor::getVersion(void)
{
  uint8_t value = 0;
  _pWire->beginTransmission(_addr);
  _pWire->write(VERSION_REGISTER);
  _pWire->endTransmission();
  _pWire->requestFrom(_addr, (uint8_t)1);
  if(_pWire->available()){
    value = _pWire->read();
  }
  return value;
}

float DFRobot_OxygenSensor::getCurrentData(void)
{
  float crrData = 0.0;
  uint8_t rxbuf[10]={0}, k = 0;

  _pWire->beginTransmission(_addr);
  _pWire->write(OXYGEN_DATA_REGISTER);
  _pWire->endTransmission();
  delay(100);
  _pWire->requestFrom(_addr, (uint8_t)3);
  while (_pWire->available()){
    rxbuf[k++] = _pWire->read();
  }
  crrData = ((float)rxbuf[0]) + ((float)rxbuf[1] / 10.0) + ((float)rxbuf[2] / 100.0);
  delay(50);
  return crrData;
}
