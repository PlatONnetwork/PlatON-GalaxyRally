[toc]

>版本信息
>
>ChainID:104
>
>Version: 0.13.1
>
>Git Commit: 5558727256dd4d6e568dbb5d12b5da6f8a17dc60
>
>PlatON二进制下载：http://47.91.153.183/platon-node/0.13.1-20200812/platon-ubuntu-amd64-0.13.1.tar.gz
>
>mtool工具下载链接：http://47.91.153.183/mtool/0.13.1/mtool-client.zip
>
>安卓版ATON下载链接：http://47.91.153.183/atonapk/0.13.1.0-test/PlatONNetwork/aton_android_v0.13.1.0.apk

### 0、节点备份

​		节点质押地址或收益地址是参赛节点将来主网奖励发放地址，请妥善备份；若不幸丢失，请联系节点管理人员进行地址变更。

### 1、安装指南

​		若已安装了PlatON节点，请跳到**第2点**进行更新操作，以下步骤以 Ubuntu18.04 系统为例，安装操作分为两种方式：**PPA、源码编译**，请严格按照官网步骤操作安装，如有需要帮助请联系客服。

- **PPA**

  [官方PPA安装文档](https://devdocs.platon.network/docs/zh-CN/Install_Node/#%E5%AE%89%E8%A3%85-platon)

- **源码编译**

  [官方源码编译文档](https://devdocs.platon.network/docs/zh-CN/Install_PlatON/#ubuntu%E6%BA%90%E7%A0%81%E7%BC%96%E8%AF%91)

### 2、更新指南

​		此次更新操作需要清理链数据，以节点数据目录在/opt/platon-node/为例，首先停止platon进程，然后清理数据操作如下：

```bash
# 查看要清理的文件和目录
$ ls /opt/platon-node/data/platon
chaindata  evidence  LOCK  nodes  snapshotdb  transactions.rlp  wal
# 停止platon进程,参考命令
$ ps -ef | grep platon | grep datadir | grep -v grep | awk '{print $2}' | xargs kill
# 进入相应的目录
$ cd /opt/platon-node/data
# 删除platon目录
$ rm -rf platon 
```

​		以下步骤以 Ubuntu18.04 系统为例，更新操作分为三种方式：**PPA、源码编译、直接使用二进制**，请严格按照以下步骤操作升级，如有需要帮助请联系客服。

- **PPA**

  ```bash
  # 更新
  $ sudo apt update
  # 卸载当前安装版本
  $ sudo apt remove `apt search platon|awk -F/ '/installed/{print $1}'` --purge -y  
  # 安装platon0.13.1
  $ sudo apt install -y platon0.13.1
  # 查看是否是0.13.1版本
  $ platon version
  # 根据各自的管理方式，启动platon进程
  # 查看块高是否正常
  $ platon attach http://127.0.0.1:6789 -exec platon.blockNumber
  ```
  
- **源码编译**（针对之前已成功编译过的环境，全新编译请参考官网：https://devdocs.platon.network/docs/zh-CN/Install_PlatON/）

  ```bash
  $ cd PlatON-Go
  $ git fetch --all
  $ git checkout -b 0.13.1_alpha origin/0.13.1_alpha
  $ make clean
  $ make all
  # 使用PlatON-Go/build/bin/目录下的platon文件替换旧的platon
  $ chown +x platon
  # 查看是否是0.13.1版本
  $ ./platon version
  # 根据各自的管理方式，启动platon进程
  # 查看块高是否正常
  $ ./platon attach http://127.0.0.1:6789 -exec platon.blockNumber
  ```

- **直接用二进制**

  ```bash
  # 下载最新的二进制
  $ wget http://47.91.153.183/platon-node/0.13.1-20200812/platon-ubuntu-amd64-0.13.1.tar.gz
  # 解压,使用新的platon二进制替换旧的platon二进制
  $ tar -xvf platon-ubuntu-amd64-0.13.1.tar.gz
  $ chmod u+x platon
  # 查看是否是0.13.1版本
  $ ./platon version
  # 根据各自的管理方式，启动platon进程
  # 查看块高是否正常
  $ ./platon attach http://127.0.0.1:6789 -exec platon.blockNumber
  ```

### 3、mtool升级及钱包复制

```bash
#备份老版mtool目录，下载并解压新版mtool
$ mv mtool-client mtool-client.bak
$ wget http://47.91.153.183/mtool/0.13.1/mtool-client.zip 
$ unzip mtool-client.zip
$ cp mtool-client.bak/ca.crt mtool-client/
$ cp mtool-client.bak/validator/validator_config.json mtool-client/validator/
```

### 4、反馈

platon升级失败的，可通过以下渠道反馈。

1. 发送至 [gitter room](https://gitter.im/PlatON_Network/Welcome)
2. 验证人微信群
3. 邮箱 rally@platon.network
