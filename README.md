# 基于STM32的2.4G无线遥控小车

## 简介

程序分为两部分，遥控器（发送端），小车主体（接收端）。

主控芯片采用STM32F103ZET6，手里多余的板子，

无线通信方式为nRF24L01，

电机采用有霍尔三相无刷电机，有独立的驱动

程序比较简单，没有嵌入系统，有些地方是可以简化合并的，



## 功能实现

遥控器上设有上、下、左、右、启动键、功能键，以及一个用来调节速度的电位器。

上、下、左、右，对应前进、后退、左转、右转；

启动键控制无刷电机的电源；

功能键可切换手动模式或自动模式（超声波避障）；

调速电位器共10级调速，每调整一级有提示音；