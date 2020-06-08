# 压测工具使用说明

> 本次提供JAVA版的压测工具，详细信息查看源码 https://github.com/PlatONnetwork/PlatON-press-java

### 活动时间

开始时间：6月9日上午10点

结束时间：预计6月9日下午4点，实际以微信群管理员通知为准

### 参赛要求

- 部署压测的机器需要jdk8环境 

```bash
# 检查是否安装jdk8环境，若已安装则直接执行下一步操作：下载压测工具
$ java -version
# 下载jdk8
$ sudo wget https://7w6qnuo9se.s3.eu-central-1.amazonaws.com/third-tools/jdk-8u221-linux-x64.tar.gz -P /opt
$ cd /opt && sudo tar -xf jdk-8u221-linux-x64.tar.gz
# 把以下四行内容添加到/etf/profile的文件中
$ sudo vim /etc/profile
export JAVA_HOME=/opt/jdk1.8.0_221
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=${JAVA_HOME}/bin:$JRE_HOME/bin:$PATH
$ source /etc/profile
```




### 下载压测工具

```bash
# 下载压测工具
$ cd ~ && wget http://47.91.153.183/press-tools/PlatON-press-java/platon-press-1.0.0.tar.gz       
# 解压压测工具
$ tar -xf platon-press-1.0.0.tar.gz
```


### 获取压测钱包
**1. 获取压测钱包文件**
请在微信群里联系管理员获取钱包文件，每个节点均不一样。

**2. 放置钱包文件**
将活动钱包文件放到压测工具所在的platon-press-config目录下，并将文件名字修改为"keys.csv"。

```bash
# 修改钱包名称，后续文档操作命令中默认使用keys.csv
$ mv [您的活动钱包文件名] keys.csv    
```
修改配置文件application.yml，将node-public-key这个字段的内容{{ nodeid.stdout }}替换为你的节点的nodeid,其他不用修改。

```bash
# 获取节点nodeid
$ platon attach http://127.0.0.1:6789 -exec "admin.nodeInfo.id"  
"8005...5bbe3445b2"
# 将node-public-key: "0x{{ nodeid.stdout }}"替换成node-public-key: "0x8005...5bbe3445b2"
```

**注意：**如果压测工具和节点不在同一台主机，还需要修改application.yml中的node-url: http://127.0.0.1:6789，将127.0.0.1改为节点IP，并对压测工具所在主机开放6789端口。

### 使用压测工具

使用以下命令启动/停止压测工具，以及查看日志：

```bash
# 切换到压测工具目录
$ cd ~/platon-press-1.0.0     
# 启动压测工具，这将会立即开始往链上发送交易
$ nohup java -jar platon-press-1.0.0.jar > /dev/null 2>&1 &     
# 查看压测工具进程
$ ps aux |grep platon-press
# 查看压测工具日志,如果有看到EVM、TRANFER、WASM这些对应的交易，即为运行正常   
$ tail -f logs/press.log  |egrep '(EVM|TRANFER|WASM)' 
# 结束压测工具进程
$ ps -ef |grep platon-press |grep -v grep |cut -c 9-15 |xargs kill -9   
```





