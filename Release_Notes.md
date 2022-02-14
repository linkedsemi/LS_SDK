# v1.0.0 发布公告

## 主要更新

### 构建系统(SCons)

- 构建命令在工程路径下执行
- 支持独立于SDK目录的工程编译
- 支持命令行附加编译参数

### FreeRTOS

- 系统任务静态分配
- 支持Tickless Idle

### Flash布局

- 程序段在前，数据段在后，利于实施Flash写保护，因此BLE、MESH、MCU应用起始地址有所差异

### 外设驱动

- ECC HAL Driver
- LE5010 IO唤醒使能情况下，ADC采集后休眠漏电问题修复
- LE5010 RTC休眠唤醒后中断异常问题修复

### 组件

- linked_buffer元素RAM空间消耗优化
- LE501X MCU模式下的sw_timer和sw_calendar
- Tinyfs垃圾回收过程中掉电恢复BUG修复

### BLE

- OTA 4K整数倍固件升级失败修复
- Profile多连接错误修复

### BLE MESH

- SigMesh 节点支持Amazon的Alexa的灯控场景
- SigMesh 无主机模式下，自动入网的节点上电初始化时，可配置消息的TTL值，以及Sequence Offset
- SigMesh 有主机模式 Provisioner
    * 添加获取主机端消息的iv ，seq数值，节点的dev_key.
    * 添加主机解绑节点功能
    * 解决主机入网设备有概率性失败的问题
    * 解决主机重新上电，概率性有节点不受控的问题
    * 增加主机的相关的AT指令
- tmall genie mesh
   * 添加支持天猫精灵的GLP模式，设备在LP2模式下有IO中断后才进入待入网模式，被精灵入网以后才进入GLP模式
   * 支持凌思微APP OTA升级Tmall genie Mesh

### 其他

- LSI频率调整为20KHz附近，漂移更小
- 支持LSE