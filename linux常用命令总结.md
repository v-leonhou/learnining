## linux常用命令总结

* [终端命令操作快捷键](#终端命令操作快捷键)
* netstat 
* [ps](#ps) 
* [top](#top) 
* [kill](#kill)

## 终端命令操作快捷键
* ctr + d 删除右边字符
* ctr + h 删除左边字符
* ctr + f 向右移动光标
* ctr + b 向左移动光标
* ctr + s 锁屏
* ctr + q 恢复锁屏
* ctr + l 清屏

## ps
```
ps aux 与 ps -ef 两者都是查看系统所有运行的进程信息

```
```
ps aux(`BSD风格`） ps -ef(`System V风格`）

```

### ps -ef

* UID     //用户ID、但输出的是用户名
* PID     //进程的ID
* PPID    //父进程ID
* C       //进程占用CPU的百分比
* STIME   //进程启动到现在的时间
* TTY     //该进程在那个终端上运行，若与终端无关，则显示? 若为pts/0等，则表示由网络连接主机进程。
* CMD     //命令的名称和参数

### ps aux 

* USER      //用户名
* %CPU      //进程占用的CPU百分比
* %MEM      //占用内存的百分比
* VSZ       //该进程使用的虚拟內存量（KB）
* RSS       //该进程占用的固定內存量（KB）（驻留中页的数量）
* STAT      //进程的状态
* START     //该进程被触发启动时间
* TIME      //该进程实际使用CPU运行的时间

### 其中STAT常见的状态：

* D      //无法中断的休眠状态（通常 IO 的进程）；
* R      //正在运行可中在队列中可过行的；
* S      //处于休眠状态；
* T      //停止或被追踪；
* W      //进入内存交换 （从内核2.6开始无效）；
* X      //死掉的进程 （基本很少见）；
* Z      //僵尸进程；
* `<`      //优先级高的进程
* N      //优先级较低的进程
* L      //有些页被锁进内存；
* s      //进程的领导者（在它之下有子进程）；
* l      //多线程，克隆线程（使用 CLONE_THREAD, 类似 NPTL pthreads）；
* +      //位于后台的进程组；

## kill

* kill -l  //列出所有信号名称
* kill -HUP PID //停止和重启进程
* kill -9 PID   

```
绝杀 kill -9 PID 这个强大和危险的命令迫使进程在运行时突然终止，进程在结束后不能自我清理。

危害是导致系统资源无法正常释放，一般不推荐使用，除非其他办法都无效,当使用此命令时，

一定要通过ps -ef确认没有剩下任何僵尸进程。只能通过终止父进程来消除僵尸进程。如果僵尸进程

被init收养，问题就比较严重了。杀死init进程意味着关闭系统。
```

## top
(摘抄自http://www.epooll.com/archives/828/）
```
运行top后，按1可以看见每个CPU上的繁忙情况以及IOWAIT。

可是，我希望看到，到底哪个进程在哪个CPU上执行，到底是哪个进程导致IOWAIT很高。

认真看man top，终于找到方法：

执行top后，按f，按j，然后按空格退出，这样就出现一列#C，可以看见当前进程正在哪个CPU上执行了。

按W(大写的W)，将top的配置写入配置文件，下次打开top的时候就能看见同样的配置了。

查看php进程运行在那个cpu上面

ps -eo pid,args:50,psr|grep worker.php
```

## 文件操作

### 压缩与解压缩
1.后缀为.tar.gz (or .tgz)

tar -xvf yourfile.tar   解压tar文件
tar -C /myfolder -zxvf yourfile.tar.gz   -c指定解压目录 可以不要

说明： -z解压缩uncompress 
       -f给文件命名
       -v（verbose) 递归的提取文件
       -x 告诉tar 提取文件
       -C /dir 说明提取后文件存放目录

2.后缀为.tar.bz2 (or .tbz)
  
tar xvjf file.tar.tbz

j: This will decompress a bzip2 file.  

3.通用的命令工具：dtrx(do the right extration)

apt-get instlal dtrx

## 文件查找
* find
* locate (updatedb)
* whereis

### find

使用示例:find /指定目录 (-not) -type (d | f) -exec ls -l {} \;

1. find /etc/ -type f -exec vi {} \;


## 时间

今天修改了linux操作系统时区为亚洲/上海时区，然后就发现php date()函数输出时间不对，由之前的上海时区时间变成了不知道是什么时区的
时间，没有来得及记录，由此产生了php默认时区的加载问题

1.tzselect设置时区

2.cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

然后执行date就会发现时区已经修改


自动同步时间： 
ntpdate 0.pool.ntp.org | time.windows.com 

(参考)[https://www.chenyudong.com/archives/linux-ntpdate-time-synchronize.html]


## linux磁盘管理

* du
* df
* [mount](#mount) 
* [umount](#umount)
* [fdisk](#fdisk)
* [设置开机自动挂载/etc/fstab文件配置](#设置开机自动挂载/etc/fstab文件配置)

  du -sh /*   查看某个目录下文件大小
  df -Th      查看系统磁盘使用量

### umount

  umount /disk1
  
  umount /data   //卸载分区

### mount
  mount -a 自动挂载，这里是根据/etc/fstab文件的内容来挂载
  mount /dev/hdb /home/ 手动挂载，机器重启后就得需要重新挂载

### 设置开机自动挂载/etc/fstab文件详解

UUID=‘分区的id号’   /usr/local exit4   default  0  0

获取分区的id号[参考](http://my.oschina.net/leejun2005/blog/290073)
* 方法一：ls -l /dev/disk/by-uuid
* 方法二：vol_id /dev/sdb5
* 方法三：blkid /dev/sdb5
 
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

