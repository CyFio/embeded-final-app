# 嵌入式系统实验课程设计——上位机部分
筛选条件从到 应用 返回
当前阻值
采样间隔
导出图片
阻值曲线
时间
# 话题
阻值resistance
+ 阻值数据 data
+ 上位机应答 feedback
<!-- + 下位机间隔 down -->
<!-- + 上位机间隔 up -->
相机camera
+ 相机数据 data
+ 上位机应答 feedback
<!-- + 下位机间隔 down -->
<!-- + 上位机间隔 up -->
间隔interval
+ 下位机发送设置好的间隔 down
+ 上位机发送设置下位机的间隔 up
心跳heartbeat
+ 下位机心跳 down
+ 上位机心跳 up

## 问题记录
使用const QString& 作为MyMQTTClient的地址、服务器名、用户名、密码会导致连接验证失败(error code 5)
采用qPrintable()或者toStdString().c_str()将入参转为const char* 都是这样，而且在debug时看到转换结果没有问题
写死参数后，如address="xxx.xxx.xxx.xxx:xxxx"后正常
目前认为是变量生存期的问题，由于暂时不影响其他功能实现所以暂时采用写死的方式。