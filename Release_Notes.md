# v2.0.0 发布公告    
    
## Highlights    
    
- 增加LM3050芯片支持    
- 增加IAR EWARM支持    
    
## 更新内容    
    
### 1. LE501X    
    
1.1 <a name="v200_1_1"></a>HAL I2C驱动更新    
1.2 <a name="v200_1_2"></a>LE501X RTC SET CALENDAR BUGFIX    
1.3 <a name="v200_1_3"></a>XIP BANNED区域函数支持垃圾回收    
1.4 <a name="v200_1_4"></a>BLE FOTA SERVER BUGFIX    
1.5 <a name="v200_1_5"></a>BLE Slave状态下默认关闭More Data    
1.6 <a name="v200_1_6"></a>IO中断回调增加边沿参数    
1.7 <a name="v200_1_7"></a>IIO外部中断API更新，删除enable，disable接口    
1.8 <a name="v200_1_8"></a>BLE AT例程更新    
1.9 <a name="v200_1_9"></a>UART TRANSMIT POLLING BUGFIX    
1.10 <a name="v200_1_10"></a>HAL I2C Slave    
1.11 <a name="v200_1_11"></a>CRYPT AES大小端倒序    
1.12 <a name="v200_1_12"></a>LE501X烧录算法BUGFIX    
1.13 <a name="v200_1_13"></a>BLE：dev gap gatt增加register_callback API    
1.14 <a name="v200_1_14"></a>BLE:增加gap set phy API    
1.15 <a name="v200_1_15"></a>CRYPT: 支持AES加解密Padding Mode    
1.16 <a name="v200_1_16"></a>LE501X LP0 IWDG BUGFIX    
1.17 <a name="v200_1_17"></a>PDM立体声驱动BUGFIX    
1.18 <a name="v200_1_18"></a>HAL FLASH：增加xip函数指针，增加QSPIV2操作临界区控制    
1.19 <a name="v200_1_19"></a>CRYPT AES驱动更新    
1.20 <a name="v200_1_20"></a>LE501X LP2/3 IWDG BUGFIX    
1.21 <a name="v200_1_21"></a>LE501X IWDG BUGFIX    
1.22 <a name="v200_1_22"></a>SPI Master pinmux重命名    
1.23 <a name="v200_1_23"></a>WWDG驱动、例程    
1.24 <a name="v200_1_24"></a>LE501X LSI校准机制更新    
1.25 <a name="v200_1_25"></a>HAL I2C Master DMA适配    
1.26 <a name="v200_1_26"></a>IAP例程    
1.27 <a name="v200_1_27"></a>HAL SPI I2S更新    
1.28 <a name="v200_1_28"></a>HAL TIMER BUGFIX    
1.29 <a name="v200_1_29"></a>LE501X构建系统：使能应用选择BLE依赖库    
1.30 <a name="v200_1_30"></a>MCU LP0统一API low_poower_mode_sched    
1.31 <a name="v200_1_31"></a>LE501X ARMCC链接脚本BUGFIX    
1.32 <a name="v200_1_32"></a>BLE HID多实例    
1.33 <a name="v200_1_33"></a>GPIO例程更新：增加进入低功耗    
1.34 <a name="v200_1_34"></a>LE501X 增加IAR支持    
1.35 <a name="v200_1_35"></a>LE501X 协议栈更新    
1.36 <a name="v200_1_36"></a>BLE svc discovery by uuid    
1.37 <a name="v200_1_37"></a>SSI例程更新    
1.38 <a name="v200_1_38"></a>BLE FOTA例程ARMCC链接脚本BUGFIX    
1.39 <a name="v200_1_39"></a>新增BLE MULTI SERVICES,BLE SINGLE MASTER例程    
1.40 <a name="v200_1_40"></a>CRYPT DES驱动、例程  
1.41 <a name="v200_1_41"></a>同步SDK更新射频BQB测试文件  
1.42 <a name="v200_1_42"></a>更新私有mesh有效数据的数据结构   
1.43 <a name="v200_1_43"></a>Auto sigmesh例程延长复位间隔时间，保证复位间隔时间大于节点解绑的间隔时间  
1.44 <a name="v200_1_44"></a>Auto sigmesh增加seqnum_size应用端可配置  
1.45 <a name="v200_1_45"></a>Auto sigmesh消息同步更新seqnum数值  
1.46 <a name="v200_1_46"></a>BLE ANCS例程增加副标题接收  
1.47 <a name="v200_1_47"></a>BLE HID例程管脚配置BUG修复
    
### 2. LM3050    
    
2.1 <a name="v200_2_1"></a>LM3050芯片开发基础环境    
2.2 <a name="v200_2_2"></a>LM3050烧录算法更新    
2.3 <a name="v200_2_3"></a>LM3050 QSPIV2 配置更新    
2.4 <a name="v200_2_4"></a>LM3050时钟配置BUGFIX    
2.5 <a name="v200_2_5"></a>LM3050 BOOT RAM更新    
2.6 <a name="v200_2_6"></a>LM3050双线Flash访问复位功能Workaround    
2.7 <a name="v200_2_7"></a>LM3050外部中断更新    
2.8 <a name="v200_2_8"></a>LM3050 TIMER适配    
2.9 <a name="v200_2_9"></a>LM3050休眠更新    
2.10 <a name="v200_2_10"></a>LM3050 IWDG驱动，更新LM3050外设MSP    
2.11 <a name="v200_2_11"></a>LM3050 ROM FLASH API使用    
2.12 <a name="v200_2_12"></a>LM3050 SM4驱动和例程更新    
2.13 <a name="v200_2_13"></a>LM3050 JLink 烧录配置更新    
2.14 <a name="v200_2_14"></a>LM3050 GCC浮点数编译参数    
2.15 <a name="v200_2_15"></a>LM3050 SHA224 SHA256 SM3驱动    
2.16 <a name="v200_2_16"></a>LM3050 arm_cm_set_int_isr BUGFIX    
2.17 <a name="v200_2_17"></a>EXTI Async中断命名更新    
2.18 <a name="v200_2_18"></a>LM3050 DMACV2驱动    
2.19 <a name="v200_2_19"></a>LM3050 UART DMA适配    
2.20 <a name="v200_2_20"></a>LM3050 SSI DMA适配    
2.21 <a name="v200_2_21"></a>LM3050 TouchKey驱动    
2.22 <a name="v200_2_22"></a>LM3050 ADCV2驱动    
2.23 <a name="v200_2_23"></a>LM3050 LP0链接脚本BUGFIX    
2.24 <a name="v200_2_24"></a>LM3050 PINMUX更新    
2.25 <a name="v200_2_25"></a>LM3050 ROM符号移除SHA相关符号    
2.26 <a name="v200_2_26"></a>LM3050 SPI驱动    
2.27 <a name="v200_2_27"></a>LM3050 ADCV2 DMA适配    
2.28 <a name="v200_2_28"></a>LM3050 软件复位    
2.29 <a name="v200_2_29"></a>LM3050 RTCV2驱动、例程    
2.30 <a name="v200_2_30"></a>LM3050 AMIC驱动、例程    
2.31 <a name="v200_2_31"></a>LM3050 COMP驱动、例程    
2.32 <a name="v200_2_32"></a>LM3050 SWD 下拉    
2.33 <a name="v200_2_33"></a>LM3050 OPAMP API    
2.34 <a name="v200_2_34"></a>LM3050 DAC驱动、例程    
2.35 <a name="v200_2_35"></a>LM3050 CAN驱动、例程    
2.36 <a name="v200_2_36"></a>LM3050 sw_timer适配    
2.37 <a name="v200_2_37"></a>LM3050外设MSP时钟复位更新    
2.38 <a name="v200_2_38"></a>LM3050 增加IAR支持    
2.39 <a name="v200_2_39"></a>LM3050外设驱动低功耗适配    
2.40 <a name="v200_2_40"></a>LM3050 TRNGV2驱动和例程    
2.41 <a name="v200_2_41"></a>LM3050使能FPU    
    
### Miscs    
    
3.1 <a name="v200_3_1"></a>CI更新    
3.2 <a name="v200_3_2"></a>README.md更新    
3.3 <a name="v200_3_3"></a>Keil、IAR编译问题修复    
3.4 <a name="v200_3_4"></a>Keil、IAR工程生成脚本更新    
3.5 <a name="v200_3_5"></a>GCC Warnings作为Errors    
    
## 变更版本    
    
| Commit Hash                              |                |    
| ---------------------------------------- | -------------- |    
| bdf86ab5d2bea0b8d8eb1dca261eedaa3e6ef796 | [1.39](#v200_1_39) | 
| 66983cf1c18587cbc339cbb801bb17f86108d374 | [1.47](#v200_1_47) |   
| 62c3121ff0d13097651f0fd7fb1681bc2078f335 | [1.46](#v200_1_46) |        
| 9d1b12c9fc130d5ba9d28d3d7a6f54201a2f1075 | [1.40](#v200_1_40) |        
| 4a09a5e4e0fea11b7efd88a5ad4edf79b624f7a8 | [2.40](#v200_2_40) |        
| a08f2cfde851c02a3aa3c7aa718130d82413e806 | [1.40](#v200_1_40) |        
| d299d1bb3830291765d603ebb8c0029af5c343c6 | [2.34](#v200_2_34) |        
| 92dd170cf752c617796877b72367162d12b3886d | [1.40](#v200_1_40) |        
| 2bb88e95906d748f5b4410110e2a8edf647f693a | [2.40](#v200_2_40) |        
| 0284023f556e9cb234ca749f0c43d1db118ba782 | [2.1](#v200_2_1)   |           
| f192e87a51476662b1050fe616d0e2032cb0541b | [2.21](#v200_2_21) |        
| 48dedfbf06398f9321621369dd2a3e73c419d30c |                    |                   
| ed264b15994cbbf1cbf2c5258d266ecf9e7b8ba3 | [1.41](#v200_1_41) |     
| 8e41204632dc1ef0cabc1a26849c4f0c1f20c650 | [2.41](#v200_2_41) |                                  
| 189d55058f36a7d88563e6e11c5170cc47fc40ba | [3.2](#v200_3_2)   |                           
| ecc8e65b4b05569f9c34e9e146d8d721765c7c73 | [1.42](#v200_1_42) |     
| 07dd35b16bba6aa21da2a3a0b43ea176fb9d76b2 | [1.26](#v200_1_26) |           
| ece9d96135abba51650af228dfbc9e5ff07d062c | [2.40](#v200_2_40) |           
| 714f1ca1ac3b25010ad4bc029803431d86407e52 | [2.40](#v200_2_40) |           
| 36ffb939dcae8c67987886be63f6408d818f0496 | [1.39](#v200_1_39) |           
| 7acccefc78de8fb00c53efcd8809ee6a87f27595 | [1.39](#v200_1_39) |           
| 019e2cd522131d23cf3b60bfe1e0351b619c71e8 | [1.10](#v200_1_10) |           
| 352765f92a44a872fc6ca8973e550f2f98a17f73 | [2.36](#v200_2_36) |           
| 09d38bcd7fb8cefc879cc53f417359cae047dc1a | [2.8](#v200_2_8) |             
| dd5aa57e3798f862b88d30dad097ea9699aaf0ea | [1.43](#v200_1_43)|     
| 07eec27e49cefed7a0e0aa144dcc5fa699bef0a6 | [1.38](#v200_1_38) |             
| 7c65aad4a05e9ca46a99b459128982dd7e758853 | [1.38](#v200_1_38) |             
| 36ebcf807413c0d6d8aa75cd8fa5064d7259a6f7 | [1.38](#v200_1_38) |             
| 15d50fb8e53306936e1d80c0c73e04f2d6f889e9 | [1.24](#v200_1_24) |             
| 3836989d397603e4975feb32ab0696888d5207a0 | [1.19](#v200_1_19) |    
| 35921f25f01f6223705d0bdc76101438900ab898 | [2.22](#v200_2_22)  |            
| 6f395f541e989790381fc3bc8e66400104ee8038 | [3.3](#v200_3_3) |               
| d7389f393660979f2d323b472ab4020d4e871d8c | [2.12](#v200_2_12) |             
| 14f3b7c9a8f9003d57b689a900b044e3bf29ef55 | [2.39](#v200_2_39) |             
| e4a0566910671b7e186b1a38a3c1560650b8b5f5 | [3.3](#v200_3_3) |               
| da853cf2d05ba182416e7f2a73477790fab3a113 | [3.3](#v200_3_3)  | 　　　　    
| 894d59a7fc8e1df93ff37ee8125ef1e40416267e | [1.8](#v200_1_8)  |              
| 4bba5e6fe031d647c556c2e4d787fd7ef293a6dc | [3.3](#v200_3_3) |               
| a523db3145e00b1632141900c87b1fa9cd37b351 | [2.9](#v200_2_9) |               
| 437c0d763eddaee9e4bd6ef048d83b548db716d1 | [1.37](#v200_1_37) |             
| 29f21982ee87e4cd70ced9560bf837cd1570c1f4 | [3.3](#v200_3_3) |     
| 04232f2d1d910c976e5773d7915f1e287f864838 | [1.27](#v200_1_27) |      
| 169aa4c2f5f2b9f562607f070386078ed31d3653 | [1.36](#v200_1_36) |      
| 282daf5453e27b603f5ed6267ca1791ba221bfe6 |                    |     
| fa0ce0003ba82755cef0da6934d821120970bdcf | [1.35](#v200_1_35) |      
| 635f83c5c3e6c2ac9a92d96523011e5a909cffd9 | [1.33](#v200_1_33) |      
| d8d3d5ecf1b47bbb302ac27e437575abf0a925cf | [2.9](#v200_2_9) |        
| 62b3ed7b2d67d95594b473187bef8e729e7d0aa8 | [3.1](#v200_3_1) |        
| fde6c83e3f8fa0ed43edc049be39a00c4020f8ce | [3.3](#v200_3_3) |        
| d54d8363ae67228eb1f2677fda224ccdf4b85dac | [1.26](#v200_1_26) |      
| f8724eaf6b31eb498ef574761ab4641ab715ad1e | [3.3](#v200_3_3) |        
| b56713d8f601b1282d09183cb714d93395295bf6 | [3.5](#v200_3_5) |        
| fa308c4a161fc57fbc327e6052669c3a17ea7396 | [3.3](#v200_3_3) |        
| 8951c142e59faafeecc1a09c2f5fe2d6ac845364 | [3.3](#v200_3_3) |        
| d4c59c962cd15eebe82ca009e0784be85b5d02f5 | [3.4](#v200_3_4) |        
| b5be2c3203ecd9fa88cf8fdd7f8a6c94aeedb661 | [3.3](#v200_3_3) |        
| 497d98f2a4bf9d5b9816bbd8f3770232d0893c7d | [2.38](#v200_2_38) |      
| 76f7a9f18e69446e4c9b822f065e79ae9438ca51 | [3.3](#v200_3_3) |        
| dda221071c5f410d22ac86d6ef7a143ce3ee09c3 | [3.3](#v200_3_3) |        
| 47b7f977d60359c7a10d837166f87ce051e7b537 | [3.1](#v200_3_1) |        
| 702c08cf49b30067159cbfe889ab26fee800ca0c | [3.1](#v200_3_1) |        
| 31e32acc2a8a94fb163b2989fee72d32bdcd5677 | [3.3](#v200_3_3) |        
| 8153289858073503e4bf25920cd5fea2fbedb6c8 | [3.1](#v200_3_1) |        
| 22dc1c2753e7805aa4951c80e13da3b31b9ceaf7 | [3.3](#v200_3_3) |        
| b039218922a22ede5684bcaae2283b0045e5af37 | [1.34](#v200_1_34) |      
| e098bd7013b2ce8346fca417c1034f595dfa780a | [3.3](#v200_3_3) |        
| 765a22761297f8c5d29b6f715b24000354d2cde9 | [1.34](#v200_1_34) |      
| 944206953e5623148561cb643b5b397c848945a3 | [3.3](#v200_3_3) |        
| 3bbd62d3e64625ff5f0c85c448248b7e1d89aaca | [3.3](#v200_3_3) |        
| 0bc35994f8024aee6fe673ea8b411a067602860a | [1.1](#v200_1_1) |        
| e0553d09c9ee8a40542a45e1e08191abae1ccc72 | [1.27](#v200_1_27) |      
| bea1d86a4e7db1608706271dc1e6acc6ae043734 | [1.27](#v200_1_27) |      
| 9330bbaaca5194e5f53f0a625fd1df2c1a84d982 | [1.1](#v200_1_1) |     
| 60223403e88055885a42ff531764b2ba46d0e501 | [1.1](#v200_1_1)  |                                    
| 46724b43ff345bb981a35d33103f442743fc56f7 | [3.1](#v200_3_1)  |                                         
| 7de14fc37c2f9e75f5e9d77e028bd22d80ff6657 | [3.1](#v200_3_1)  |                               
| 7f5e4fb88685ed7df2c7fe5b1f1befd54947fe98 | [1.27](#v200_1_27) |                                     
| a70f2de190d17fd7e5ceeee63c7667ece0e0aa03 | [1.34](#v200_1_34) |                             
| 5b330fc3a1877723896df972d1afa340e38d2a8c | [1.27](#v200_1_27) |                                 
| 6aa7db72c15fa891ff91f3ec0b24c59043e06fff | [2.38](#v200_2_38) |                   
| 923711d48abfb7e0eaaefd9782260bb17335a610 | [2.38](#v200_2_38) |    
| abf2e48429cf2db0a6002248d2f418627233c1a1 | [2.38](#v200_2_38) |                                 
| ede3275c37a344c7fd58da328370583d9762812b |                    |                            
| 5ebef58243fcb100c107971ad35d1df7135f302a | [1.27](#v200_1_27) |    
| ee121bc546675672bbc0c2c4827853ce34ffc67a | [1.34](#v200_1_34) |                                 
| 8545667698981ac08e3b7c38b722b6f82123a418 | [1.33](#v200_1_33) |                                  
| 02c963aa0f1e575936ea83fe30769d2c6e092417 | [1.32](#v200_1_32) |                       
| 2d425497756809782963d3fec367f2e9accfc0ff | [2.21](#v200_2_21) |                                 
| 395dd9a6997a1d923e34afb6289a4fe8c2a56977 | [1.31](#v200_1_31) |                     
| 35712cbba401bec77dc4159cce5ec4466338f3db | [2.31](#v200_2_31) |                           
| 80796ff1ac4b139d4dd97aa91096a4fb2a5b43fc | [1.30](#v200_1_30) |                          
| 12e6a19a63e42bbd4faab09e038a7ea5b35b43c0 | [1.29](#v200_1_29) |     
| 4d4a8164738eecf16b11989d48ec571bf3768fc5 | [2.37](#v200_2_37) |                                     
| de333cf61b21a871edce14adbb5a16e71992dbe3 | [2.31](#v200_2_31) |                         
| 0e84b795ccabeaacdc1e5fce2e51fe7e28740968 | [1.28](#v200_1_28) |                                      
| 9e1a7887dfa2c85eec94afb452fcb222d47f5926 | [2.36](#v200_2_36) |                                    
| fd4f66371db6bb9a97879a3cc01d1f9d35a2ad80 | [2.35](#v200_2_35) |                                      
| 5352dedeece3965cb630df6b3bff2ec91e36ede6 | [3.2](#v200_3_2) |               
| 1555860887a21fd4ecbb68e2aab432701b6a3b8b | [2.34](#v200_2_34) |                                      
| 0296ba65abec55ce44f13483b3c7683757a984c1 | [1.27](#v200_1_27) |                          
| 1ef1c6f6b967972d8108e1f3f21f8adedcbaa924 | [1.27](#v200_1_27) |                            
| 84fcb95f502e906ae0426c87b5c0536a802c4b42 | [1.27](#v200_1_27) |                             
| 79b78056077bb50a4b6ff4a2596337333fadebda | [2.34](#v200_2_34) |                             
| 9594914c205f79abd22ea6b67bb0dcf74f937f83 | [2.9](#v200_2_9) |                    
| c8819be8fbe041505c2d283e8978c09f46c28436 | [3.2](#v200_3_2) |    
| 6794638aef3900cbe1a8a3716fa422afdd10ba79 | [2.29](#v200_2_29) |                                      
| ca59037ca7205ee94355cb9770ff10eafb43f2c5 | [3.1](#v200_3_1) |                                       
| ee7bf11354693baf069395fc00b7ca318aa54070 | [3.1](#v200_3_1) |                                      
| a5bfb79817ee18fb075403198046901383c82ad3 | [1.26](#v200_1_26) |                                       
| ddbc00aa6c857dace55a3cb2827a008f8d3765f0 | [1.25](#v200_1_25) |                             
| ae514f2999cfc151c82b77e0c7f019679c83b6ea | [2.9](#v200_2_9) |    
| 04b6104519a317ad75754926b164b3d0d854c365 | [1.24](#v200_1_24) |              
| 47d983c12efea8b4f99c5b6380c9de8d61e554d6 | [2.34](#v200_2_34) |                                         
| 5241ba5c0b3c9ceeb4a3b48fd27464476af143b8 | [2.33](#v200_2_33) |                                     
| b7ea9d880d11ba07ea2d5696973bc7f4f8be3b2f | [2.33](#v200_2_33) |                                           
| edc604ccf81367c50630609e6bbfe4b1b79fc4da | [2.31](#v200_2_31) |                                  
| 59544a3371501732f1c63299cbb673eb0ae0d6c9 | [2.31](#v200_2_31) |                                   
| 7b38e2121f05636b35b520721f870a74b230617e | [2.32](#v200_2_32) |                               
| f1c4a846a8dc9907c2046c6ea4c40e81401e07d7 | [2.31](#v200_2_31) |                                    
| 210312c29a98314f8bbd667eb929910d436b1e38 | [1.1](#v200_1_1) |     
| 60c68306a0889a71691511109f1a659b2f016e2c | [2.29](#v200_2_29) |    
| c8cdf07339b8eafdf9fb82d566b00ef63705338f | [1.23](#v200_1_23) |                                       
| ff87891d6eb3cfbb2be18763489a5f7fec7f9110 | [2.30](#v200_2_30) |                                  
| ab0b1ae0bc5135687be23d196f8b8fefdc74363e | [2.29](#v200_2_29) |                              
| 0f039fdca77796ce899954cb23b436e2deadf704 | [2.12](#v200_2_12) |    
| de9d6ec807fcbb9e076e32c5f12c3c7a239771c2 | [1.1](#v200_1_1) |    
| ac9d44d6ba762c02c881347a72fc8fc5a4052af0 | [2.28](#v200_2_28) |                                           
| cfec406ec6da41d140d5b24cf5168ebb49b81805 | [2.9](#v200_2_9) |    
| 161bb20e3602354b4d58047830381b1706b5ef22 | [1.1](#v200_1_1) |                                
| af3f51cf7b94cd1f29bd1b09a5572e371e309db1 | [2.7](#v200_2_7)   |                             
| d1bdcd22079a97126ac9ff5978941bb0c2625706 | [2.27](#v200_2_27) |                             
| d7c770a10001df535e0f8125c25966e5ac3340b8 | [2.26](#v200_2_26) |                              
| 93105dbeb98f0de297fcb26925135988d908363f | [2.25](#v200_2_25) |                                     
| 7a0d4592e7bad492f07d497c87a312ef8424e681 | [2.21](#v200_2_21) |    
| 7281e98e592009854c80baab8647035d07604dff | [2.22](#v200_2_22) |    
| 703c69dfed60b6ce3eb24b0ff71c704f2c4374a1 | [2.24](#v200_2_24) |                                         
| 5c13fa2799280462343b562d9c7d1ea872b12d9b | [1.22](#v200_1_22) |                                      
| 9f3be9310306673647c6cbb3da4215cdf6dca3f2 | [2.23](#v200_2_23) |    
| 536207a268aa22bbfc675da7a9cb327f311ea969 | [2.22](#v200_2_22) |                                  
| 2b1d17814850670cc53adaa90aadcba5a767ffff | [2.21](#v200_2_21) |                               
| e5ab08cc428cbdd2cf026420a005eadc0c7e92ef | [2.20](#v200_2_20) |                                     
| bff2fd95e269b28a7ba58a31db6330c8faa8bc7f |                    |                                        
| 7508148e79a5138c8d248cc1e154877d92a7b3f6 | [2.19](#v200_2_19) |                                       
| ccddac8ff9826e5c0e3ba2aad329d76ae6094255 | [1.21](#v200_1_21) |                                        
| 9a526bf00104d12f28732add3a53b17a199d1f05 | [2.18](#v200_2_18) |                                  
| f74003eba4902de3e292f2932e2255e8ac865394 | [2.17](#v200_2_17) |                    
| 2ca42da884eec23b801fa8dcafcccbb77f1f3133 | [2.16](#v200_2_16) |    
| a11b585ca944e9d294fbd9207394628b657436dd | [2.12](#v200_2_12) |    
| 6f647b127036f034a35b628734412f58f001d3f9 | [2.15](#v200_2_15) |    
| 5c930a1a5297e12a46315afd2371ca02069ec192 | [2.14](#v200_2_14) |                  
| f64b8f4ec827026835f0f9aa2de9fedbcc00327a | [1.19](#v200_1_19) |                                       
| eea2f5d8ec6af27f4a94f46b12c996499e7696f1 | [1.20](#v200_1_20) |    
| 8c25cffdb4c2c5bde1021bb9c04ed47fd5f5606a | [1.19](#v200_1_19) |                     
| 5eec93c11e60b0b137aa0d009f2247bfc8e393a4 | [2.12](#v200_2_12) |    
| 47f797efc6c6f9e53a7ca620923ccf58628d7fc5 | [1.18](#v200_1_18) |    
| a839a38db5f9171d3c7eaef9817a0f6822312428 | [1.1](#v200_1_1) |     
| 75a6c5d46c1166bc9f63ccb960eda540a8485774 | [2.13](#v200_2_13) |                 
| e7b697c09c9c63f2da1b8141982ef441b9c6c2dc | [2.12](#v200_2_12) |                                     
| ba5558119c7cf8724c344aa09aa8efacb1582d05 | [1.17](#v200_1_17) |                             
| 34793545513e9018c6d985a8693701a5f888e9a0 | [1.16](#v200_1_16) |                                    
| 773d72821a518da0b83bfe559f16a426a92179f8 | [1.15](#v200_1_15) |                             
| 9687d1b20b13e279febce8101c8683fb756e994d | [1.14](#v200_1_14) |                                       
| bdb1483c166d3bdec4ca4427d1f6f132bf019d1f | [1.1](#v200_1_1) |                                     
| c82753840a0e44afcd55b0eeb3bdd6030bcd2278 | [1.13](#v200_1_13) |                                   
| 41fa17df0093d4a1402d973d96a42a26b0d72203 | [1.12](#v200_1_12) |                      
| df4045c33ec8d65413c5b5df0675e69c9b2c965a | [1.11](#v200_1_11) |    
| 9809e7091e7021ac5e5c9d8acdaa721a58ccf8a7 | [1.10](#v200_1_10) |                        
| ae813431c3784ec2f38c31594602221a99688028 | [1.9](#v200_1_9) |                               
| 9541897d9aade115f9769a1a70661aa14932740b | [2.2](#v200_2_2) |    
| 0e358ed1dab95f08d23804a68a468ca26df40634 | [2.11](#v200_2_11) |                       
| da5e3b4bd7cb2a9c8a587d7dc73ab82d2dd7628e | [1.8](#v200_1_8) |    
| 815cf60c05de41d063e98a141ce717c1087b5602 | [2.10](#v200_2_10) |    
| 342eb5199533014871d920c7a7b31a0ad31816b7 | [1.7](#v200_1_7) |    
| 4badf2672411824f618a103512a54c0f1ee0d78f | [1.6](#v200_1_6) |    
| cb917808e715dd314abe34ff14f322d2c12acb3c | [1.5](#v200_1_5) |    
| e9f60bb785e933dcf46520784b6205047370ff87 | [1.4](#v200_1_4) |    
| 4fa547958d132f34157d77b1cc8b6c1563f96c44 | [1.3](#v200_1_3) |    
| 5ce424178199f17b08641691832841f6e040af3b | [1.44](#v200_1_44)] |     
| 19e2b24e0ff57178274cf1b3966f4430c8694f61 | [1.2](#v200_1_2) |                   
| e1297150b54ca4122a4cbdb75bd688be3fc3e721 | [2.4](#v200_2_4) |    
| 613c922e43bfdfab21f5f312b070aa55f5bb1456 | [2.9](#v200_2_9) |    
| d57c58947750b2e95b0f9540d155fbddffb04e61 | [2.8](#v200_2_8) |    
| 9c7bfa93e4b76bab5d41fef1e3a59cf3cbd2853b | [2.7](#v200_2_7) |    
| 1e1561f71ea4a16880aadf7d52ee27ca11cc7dd7 | [2.4](#v200_2_4) |    
| 1633108ecbe885d96defc2e04dbecff487d1a5f6 | [2.6](#v200_2_6) |    
| b405d324971ceaf6a7224064d09ae6798d5d0b07 | [2.5](#v200_2_5) |    
| be6778719c47e92799777360991b0f149146d078 | [2.4](#v200_2_4) |    
| 41a96b26519a768ccf1e76568abe6ce127dabe16 | [1.1](#v200_1_1) |    
| ad41ef9ba2670212c4d778166eeeacd33b54a7da | [2.3](#v200_2_3) |    
| 41d93d32863d297bbe6f0f6de88dc45d240fa836 | [1.45](#v200_1_45)|               
| 74a83dbf9f1d7d6ab6e60450c00cf9d24e578abe | [2.2](#v200_2_2) |    
| bc3d488f47bcc70801473cc67a1ed78d104b3da3 | [2.1](#v200_2_1) |    
    
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
