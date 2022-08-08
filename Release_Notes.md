# v1.1.0 发布公告

## Highlights

- FOTA协议调整，协议栈OTA支持，固件端、APP端与老版本不兼容
- LE5030触控芯片支持

## FOTA协议调整说明（重要）

FOTA协议升级，空中交互流程增加了一条命令。造成SDKv1.0版本手机FOTA APP无法用于SDKv1.1固件，SDKv1.1版本手机FOTA APP无法用于SDKv1.0固件，即固件、APP与老版本互不兼容。

SDKv1.1的FOTA增加了协议栈OTA功能，即SDKv1.1开始，以后版本如SDKv1.2更新，协议栈部分更新可通过FOTA实现。

## 更新内容

### 1、构建系统（SCons）

1.1 <a name="v110_1_1"></a>支持引用上级目录源文件  
1.2 <a name="v110_1_2"></a>构建脚本优化  
1.3 <a name="v110_1_3"></a>Windows平台汇编文件宏定义丢失问题修复  
1.4 <a name="v110_1_4"></a>GCC编译显示内存使用  
1.5 <a name="v110_1_5"></a>Embedded LLVM For ARM工具链支持  
1.6 <a name="v110_1_6"></a>注释CI编译  

### 2、外设驱动

2.1 <a name="v110_2_1"></a>增加Flash SFDP读取接口  
2.2 <a name="v110_2_2"></a>增加SSI阻塞收发接口和半双工接口  
2.3 <a name="v110_2_3"></a>SSI DMA发送BUG修复  
2.4 <a name="v110_2_4"></a>Uart it tx最后一个byte概率性丢失bug修复     
2.5 <a name="v110_2_5"></a>__HAL_TIM_DISABLE_IT() API bug修复  
2.6 <a name="v110_2_6"></a>IWDG LP0 BUG修复  
2.7 <a name="v110_2_7"></a>DMA BUFFER放置于RAM末尾  
2.8 <a name="v110_2_8"></a>增加spi_flash_read_sfdp API  
2.9 <a name="v110_2_9"></a>SPI阻塞API更新  

### 3、BLE

3.1 <a name="v110_3_1"></a>射频参数优化，发射功率一致性优化  
3.2 <a name="v110_3_2"></a>增加安全连接OOB事件  
3.3 <a name="v110_3_3"></a>FOTA支持协议栈更新，FOTA RAM消耗优化  
3.4 <a name="v110_3_4"></a>多连接BUG修复（多路并行批量数据传输，其中一路断连接会影响另一路数据传输）  
3.5 <a name="v110_3_5"></a>增加SCAN REQ IND事件  
3.6 <a name="v110_3_6"></a>增加ADV STARTED和UPDATED事件  
3.7 <a name="v110_3_7"></a>set_svc_permission API更新，删除无效参数  
3.8 <a name="v110_3_8"></a>增加dev_manager_add_service_with_start_handle API  
3.9 <a name="v110_3_9"></a>llcp过程slave latency优化  
3.10 <a name="v110_3_10"></a>active scan bug修复  
3.11 <a name="v110_3_11"></a>增加builtin_timer_active API  
3.12 <a name="v110_3_12"></a>增加bass profile enable api  
3.13 <a name="v110_3_13"></a>修改ecc为polling模式（支持应用使用ecc）  
3.14 <a name="v110_3_14"></a>ble_multi_roles/uart_server_multi_link等demo新增disconnect时清相关全局变量处理  
3.15 <a name="v110_3_15"></a>增加rtos_ble_task_func_post API,支持RTOS环境下，向ble任务发送消息  
3.16 <a name="v110_3_16"></a>调整协议栈全局变量地址，置于向量表之后  
3.17 <a name="v110_3_17"></a>唤醒BLE时钟恢复bug修复  
3.18 <a name="v110_3_18"></a>设定BLE MAX TIME上限为2120，优化个别手机的吞吐率  
3.19 <a name="v110_3_19"></a>增加射频参数温度校准机制  
3.20 <a name="v110_3_20"></a>修复SMP流程在连续func_post过程中被阻塞的问题  
3.21 <a name="v110_3_21"></a>天猫精灵Mesh OTA流程支持  
3.22 <a name="v110_3_22"></a>设置Mesh协议栈加载地址4K对齐  

### 4、Demos

4.1 <a name="v110_4_1"></a>增加AMIC示例  
4.2 <a name="v110_4_2"></a>Keil info_sbl和stack烧录支持  
4.3 <a name="v110_4_3"></a>增加LE5030触控BLE示例和外设示例  
4.4 <a name="v110_4_4"></a>输入捕获示例中调试IO不翻转bug修复  
4.5 <a name="v110_4_5"></a>增加BLE主从配对示例  
4.6 <a name="v110_4_6"></a>SSI示例标志位BUG修复  
4.7 <a name="v110_4_7"></a>Mesh例程更新，BUG修复  

### 5、LE5010

5.1 <a name="v110_5_1"></a>1M Flash 烧录算法支持  
5.2 <a name="v110_5_2"></a>进入LP2 LP3函数BUG修复（新增stop systick & global irq disable）  

### 6、Prop 2.4G

6.1 <a name="v110_6_1"></a>优化2.4g tx prog delay  
6.2 <a name="v110_6_2"></a>支持FreeRTOS  
6.3 <a name="v110_6_3"></a>支持LP0  
6.4 <a name="v110_6_4"></a>支持在sw_timer cb里调用RF_Stop接口  
6.5 <a name="v110_6_5"></a>支持legacy adv的收发  
6.6 <a name="v110_6_6"></a>修复2.4g例程uart/rf共用buffer导致数据出错bug  
6.7 <a name="v110_6_7"></a>删除2.4g每次tx前都默认做pll gain calib的多余行为  
6.8 <a name="v110_6_8"></a>删除2.4g pll gain calib流程中无效空等行为  
6.9 <a name="v110_6_9"></a>删除2.4g rx abort flag(不需要中断flag同步，改为阻塞式等待)  

### 7、Modules

7.1 <a name="v110_7_1"></a>sw_timer_stop bug修复  
7.2 <a name="v110_7_2"></a>增加general_fifo_get/set API  

### 8、BLE LL Standalone Stack

8.1 <a name="v110_8_1"></a>协议栈基地址更新  



## 变更版本

| Commit Hash                              |                |
| ---------------------------------------- | -------------- |
| 0cc4b4441a62256ea5d4640d6c1e1a85ba73a601 | [4.7](#v110_4_7) |
| 275b7e2a21f95a1de983a89bfb38e5457a5f26dd |                  |
| b57306199141956ee914bc59aaf0370f43f5725b |                  |
| 10acbf88c158f07a80fe2e94bc55b6fdc4d21e31 | [4.7](#v110_4_7) |
| 74b1ff220c3457bfdc462abf7d271190935bf9eb |                  |
| 34660d6e3832baebb592dd3f241bf72486ccf380 | [2.9](#v110_2_9) |
| 811f59a2092a96a34fadd23aecce2c4b08f2adf6 | [3.22](#v110_3_22) |
| 8919e5a73acd4e6051ba77d091ee52ef8716c70e | [3.21](#v110_3_21) |
| 911a2c095c1430d822b54b2389438978d8c9d3c7 | [3.20](#v110_3_20) |
| ae1280a45a4574b3a1c419a5f10a064ead984047 | [3.19](#v110_3_19) |
| 9200c6b2c7d88627f57dc41d9e7ef56729038a38 | [4.5](#v110_4_5) |
| 79b9ee570c7e621fd8407b1ccce0b86c4e494d72 | [6.9](#v110_6_9) |
| d733ff0ca843ebbc64fa737244e2e217355a8e99 | [2.3](#v110_2_3) |
| 63ae708f9879802380d6d908a6416a1422fbd353 | [2.8](#v110_2_8) |
| ccf6b9d06cc12defc218970d384fa82b4959fd2f |                  |
| b76c6d6fe95f65b889eada0f2f8ce1ebf7bb3446 | [2.2](#v110_2_2) |
| 36e43b84f87f6ed6cbe5e8b9035c7b2fc9ae4f72 | [4.4](v110_4_4)  |
| 449369a529d8f3db81dbb8692f5792ab5cb451d0 | [5.2](#v110_5_2) |
| 5dc723500d9091726b4977425101f6ebb8680156 | [2.1](#110_2_1)  |
| 7d94c46edcab67afb53efa74e37fc455f144a09e | [2.7](#v110_2_7) |
| 07e8a6b7893c2469cc5df6907cf22c38422005e2 | [2.7](#v110_2_7) |
| ed735bd33dc86358f5aa368521bb4735e3e72ce3 | [4.6](#v110_4_6) |
| e757f6ae9987606129f9591523f2bff0f7dc5e5e |                |
| 9234f9c36b4b3835649dd328d72d99f37c28edfa | [3.17](#v110_3_17) |
| f6830b7b4c761e4df29c40145f5a676dd815c351 |                |
| 6e74b02de60f8c3f954602513028760737f00c62 |                |
| 696ad72f2661ca88c6bebae28ddaaeedd364057c | [3.3](#v110_3_3) |
| 728cd3ffe26851eca28c50b30f080f255df8bb51 |                |
| aa197779f74d73995c3e93a3758e2b1e406f39fd | [3.12](#v110_3_12) |
| af74d3b5cdcf626031481d4a2f726e3e1f795b57 | [3.3](#v110_3_3)   |
| d8504a0a670f4fb61efcf65458c86eab102579e8 | [2.4](#v110_2_4)   |
| e76e8bf8214c0cd847bfc12af9e6205825291ed8 | [2.3](#v110_2_3)   |
| ac6dddbeb59235e205b18da71a5628713f7c60b1 | [3.13](#v110_3_13) |
| 5257fe5f9684a4f9e26cd18bab31a44c5b9dc481 |                |
| 970e83e632b1d384beb99400c9d7f5033dd2d6d0 |                |
| 1f5024c5c070813a5780699b99ca5c0d545458d3 | [3.4](#v110_3_4) |
| f4f38d2cd354fb9b5fcdaf679b432eb9d642c620 | [4.2](#v110_4_2) |
| 0bebdac1bbdabd6ea86c696681097aeabcf14bec | [2.6](#v110_2_6) |
| 22b041b846c1295bc9981e845cd882d695f2820f | [3.11](#v110_3_11) |
| 1eedf09e4916940d11e10ac4a20813d37661c6bd | [3.6](#v110_3_6) |
| a9d5e594d2309108950a182fe280bc4946bf6be7 | [7.2](#v110_7_2) |
| 152699e4c1811615027ed4b59766f110021528be |                |
| ce25890b2b1cbd779bd363ff603814915df84462 | [1.6](#v110_1_6) |
| 8137d97458712a9bb5e93394e38706302682d254 | [3.10](#v110_3_10) |
| 20656610fb15cdbc37e6f958e2aeece968fb58d9 | [3.1](#v110_3_1) |
| ff5d4a641350bd27e331dd51b0be851e0deb2525 | [3.3](#v110_3_3) |
| 1c7386623f15ef92e5b03101de1351d729037f46 | [6.4](#v110_6_4) |
| 21c7202d3d0dcc1ef635f976b5c0f9795e48653e | [4.1](#v110_4_1) |
| a2e1205bd33aa19ef75b43db95925d8454e47b72 | [1.5](#v110_1_5) |
| 8bf4fefa33c02ec68559fc1c0f649ece94f1e8f9 | [3.9](#v110_3_9) |
| 0d2d942ae08936005c057994ec0eaa4697359dd4 |                |
| fa30912f067ae00718890661ced5f8e4fd1f1b8e |                |
| 67d784332952e37f25350a172e1877ecfa38f158 | [3.3](#v110_3_3)   |
| 23778ea917f42551b4fcaa50ebaf46be06cc855c | [5.1](#v110_5_1) |
| 99cb52349ff8d451a41a64c4dc5e8e839c091ff5 |                |
| 51b444ba925f675511e415553b850a0a4d068109 | [6.1](#v110_6_1) |
| b9ac05b0bd91e63d9854bcc7d94a3b0a7132b2db | [3.3](#v110_3_3) |
| 91693e8efd2f44cab0aa0c0949b20ed637b87a3b | [1.1](#v110_1_1) |
| cbff5bd4497b528fcbdeefffd34994475195bbc4 | [3.18](#v110_3_18) |
| 13b80710fe0da8c5350180442b39f53a6d8b3e2f | [4.3](#v110_4_3) |
| 81503a752c26b43d3f1ba1dd80920f0813267664 | [3.16](#v110_3_16) |
| 5af6193742d3fe52d9f3676d8060a25fa4db332d | [2.4](#v110_2_4)  |
| f7b4d749e8ab09628cb26145b606ad1f1fe04855 | [2.4](#v110_2_4)  |
| c82eb30c4a0137835554ce4063f4c74abf5efb44 | [3.1](#v110_3_1)  |
| ad4c9830884d968e3c281e56c295a1c29ffc55f0 | [3.14](#v110_3_14) |
| 2eaebfecb6a6e1b720d81d49cda8336b974d96eb | [6.8](#v110_6_8) |
| c12d811a4916e9609dd6e7dfc79148de21fb82ae | [3.3](#v110_3_3)  |
| b6d7e95751631d7fa3bc950082f2db14a87f846a | [1.4](#v110_1_4)  |
| 9f95fe0befc7235244d0da59cd2474d2ed31c99b | [3.14](#v110_3_14) |
| d53c07bd7857bbd23c22402bcd6a3a31ece43176 | [4.5](#v110_4_5) |
| 8318469a5a76575573d3b67012af4f9050adff72 | [6.7](#v110_6_7) |
| 1026ca5e90d7f23d6f0a5ddda00fb6a64cdf34f8 | [3.8](#v110_3_8) |
| 5589080a2536c8b7281f3c0f0efaa0e8f7f3617e | [4.3](#v110_4_3) |
| 26adfd45bcd7594655c7f3fcccdb377aacca8fcd | [6.1](#v110_6_1) |
| 1bbebd9c63719901c9925b7754ebafe7f61ed874 | [4.3](#v110_4_3) |
| 9f31905a2dcc649c1246f666b40b51988dd70ec4 | [6.5](#v110_6_5) |
| c8b224ebefe3d2339f9fd42629714516207d7dd9 | [3.7](#v110_3_7) |
| 84a9c3fee8fc7be187deb345ddcd5996cc0cb12a | [4.3](#v110_4_3) |
| 0745dad1c547adc902e3bbb815998a690795c283 | [4.4](#v110_4_4) |
| 7365e245e985e34d54b3eaa200e6cea4a557e265 | [4.3](#v110_4_3) |
| 116f125d09d65ffa228d0896c8a34c6929866d0e | [6.6](#v110_6_6) |
| ee161c3864c6e9a458eeda593101c455dcba7d60 | [6.5](#v110_6_5) |
| 5d0a4c6c5869e54491bdbabc4681613fc05f73a0 | [3.2](#v110_3_2) |
| ba6663a6014051fb09652e7272482a110826eb7b | [6.2](#v110_6_2) |
| 6a3ca3915674df846f659bbd53f63309abb6307a | [3.5](#v110_3_5) |
| b345a64f3f653846a4093263dc52038e14bab6b6 | [2.5](#v110_2_5) |
| 9e5fd241ff28f570916429c5933deae4b9ebe717 | [4.3](#v110_4_3) |
| 3b375f5b296eaccd5dd27537117f16ab1ddd1d1f | [1.2](#v110_1_2) |
| 167800c9428559f56f7044b918d4f21d4b95d676 | [1.3](#v110_1_3) |
| 20c8e62519878d7120cf12661b74c8d0c0b97ebc | [1.2](#v110_1_2) |
| 32bfc9ba9589ad34bd3239e25e183b3d6c1b1bff | [6.3](#v110_6_3) |
| ac82321656ee2fa1b75397a2edbab4d98a38659c | [3.1](#v110_3_1) |
| b5d3963d4e804de10bab4c3e9bac1b1747b159ea | [7.1](#v110_7_1) |
| fb8ca67c7692e1f1d03ea7d308974a0b89e593bd | [4.3](#v110_4_3) |
| c17ce1499e1be72f241b9b88bd93d5aac588428e | [3.15](#v110_3_15) |
| b573576eec89763e490c2c910d2dea1332d8ded4 | [3.15](#v110_3_15) |
| bd9a4993cc2356a9f68060bd78ef01eb57848f6b |                |
| 30ff6f2758d90f82995a0b718979860639065f9f | [1.2](#v110_1_2) |
| 690a3512338e18a58517f628e9c6dedd1331fb18 | [8.1](#v110_8_1) |
| 067815c0d8a0156a84d842c2c35ae017cf64ba5d |                |

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
