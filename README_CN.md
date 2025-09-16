# DFRobot_OxygenSensor
- [English Version](./README.md)

DFRobot最新推出I2C氧气浓度传感器，有效量程为0~25%Vol。该款传感器利用电化学原理对空气中的氧气浓度进行监测，具有高精度、高灵敏度、线性范围宽、抗干扰能力强以及优异的重复性和稳定性的特点。使用I2C接口，就可读取传感器所在环境中的氧气浓度，可以兼容各类单片机和传感器，使用非常简单。 该氧气传感器可广泛应用于工业、矿井、仓储等空气不易流通的空间，以及环保领域中的氧气浓度检测。


![svg](resources/images/sen0322.jpg)


## 产品链接（https://www.dfrobot.com.cn/goods-2792.html）

    SKU：SEN0322

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

有效量程为0~25%Vol

兼容3.3V和5V主控器（注意：使用3.3V设备时，仍然可以5V供电）

具有快速校准功能，I2C数字输出，反接保护等

## 库安装
这里提供两种使用本库的方法：
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_MGC3130"并安装本库.
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.

## 方法

```C++
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

  /**
   * @fn checkProbeLife
   * @brief 获取传感器探针寿命状态
   * @return eProbeLife_t
   * @n         eProbenExhausted   传感器探头寿命不足,建议更换传感器探头
   * @n            eProbenNormal   传感器探头寿命正常
   * @n            eVersionError   调用此函数功能失败，传感器版本不兼容
  */
  eProbeLife_t checkProbeLife(void);

  /**
   * @fn getCurrentData
   * @brief 获取当前电流数据
   * @return 当前电流数据，单位 uA
   */
  float getCurrentData(void);
```

## 兼容性

| 主板        | 通过 | 未通过 | 未测试 | 备注 |
| ----------- | :--: | :----: | :----: | ---- |
| Arduino uno |  √   |        |        |      |
| Mega2560    |  √   |        |        |      |
| Leonardo    |  √   |        |        |      |
| ESP32       |  √   |        |        |      |
| micro:bit   |      |        |   √    |      |


## 历史

- 2019/10/25 - V0.2.0 版本
- 2021/10/22 - V1.0.0 版本
- 2023/08/02 - V1.0.1 版本
- 2025/09/15 - V1.0.2 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))