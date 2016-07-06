## linux磁盘管理

* du
* df
* [mount](#mount) 
* [fdisk](#fdisk)
* [设置开机自动挂载/etc/fstab文件配置](#设置开机自动挂载/etc/fstab文件配置)

  du -sh /*   查看某个目录下文件大小
  df -Th      查看系统磁盘使用量

### mount
  mount -a 自动挂载，这里是根据/etc/fstab文件的内容来挂载
  mount /dev/hdb /home/ 手动挂载，机器重启后就得需要重新挂载

### 设置开机自动挂载/etc/fstab文件详解

总共6列

1. 需要挂载的系统设备
2. 挂载点
3. 指定文件系统或者分区的类型
4. 挂载选项
  auto:系统自动挂载，fstab默认就是这个
  ro:read-only
  rw:read-write
  defaults:rw,suid,dev,exec,auto,nouser,and async
5. dump选项，设置是否让备份程序dump备份文件系统,0忽略，1备份
6. fask选项，告诉fsck程序以什么顺序检查文件系统，0忽略

### fdisk

* fdisk /dev/vdb  //给数据盘/dev/vdb创建分区

fdisk 参数介绍：
| 参数 | 详解 |
| :------: | :------: |
| n | 新建一个分区 |
| p | 设置为主分区 |
| e | 扩展分区 |
| p | 查看一下分区 |
| w | 保存分区 |

分区之后得格式化之后才可以挂载
 
mkfs.ext4 /dev/hdd1
