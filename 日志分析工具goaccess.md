首先在[官网](https://goaccess.io/download)里找到安装位置：

```
$ wget http://tar.goaccess.io/goaccess-1.0.2.tar.gz 
$ tar -xzvf goaccess-1.0.2.tar.gz 
$ cd goaccess-1.0.2/ 
$ ./configure --enable-geoip --enable-utf8 
$ make # make install
```

在执行第四步报错：`configure: error: *** Missing development files for the GeoIP library`

于是google了一下解决办法：

```
yum install geoip-devel
```

然并卵，还是报错：`No package geoip-devel availabl`

继续查找资料：

```
rpm -Uvh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
rpm -Uvh http://rpms.famillecollet.com/enterprise/remi-release-6.rpm
````

以上两条只执行第一条然后就直接`yum install geoip-devel`

geoip-devel终于安装成功！

然后继续执行`make && make instal` ,goaccess安装成功！

make过程中出现了几个警告信息：

```
In file included from src/gkhash.c:40:
src/gkhash.h: 在函数‘ins_is32’中:
src/gkhash.h:43: 警告：调用‘kh_resize_is32’时内联失败：call is unlikely and code size would grow
src/gkhash.h:43: 警告：从此处调用
src/gkhash.h:43: 警告：调用‘kh_resize_is32’时内联失败：call is unlikely and code size would grow
src/gkhash.h:43: 警告：从此处调用
src/gkhash.h: 在函数‘ht_insert_meta_data’中:
src/gkhash.h:53: 警告：调用‘kh_resize_su64’时内联失败：call is unlikely and code size would grow
src/gkhash.h:53: 警告：从此处调用
src/gkhash.h:53: 警告：调用‘kh_resize_su64’时内联失败：call is unlikely and code size would grow
src/gkhash.h:53: 警告：从此处调用
src/gkhash.h: 在函数‘ht_insert_agent’中:
src/gkhash.h:51: 警告：调用‘kh_resize_igsl’时内联失败：call is unlikely and code size would grow
src/gkhash.h:51: 警告：从此处调用
src/gkhash.h:51: 警告：调用‘kh_resize_igsl’时内联失败：call is unlikely and code size would grow
src/gkhash.h:51: 警告：从此处调用
src/gkhash.h: 在函数‘ht_insert_maxts’中:
src/gkhash.h:45: 警告：调用‘kh_resize_iu64’时内联失败：call is unlikely and code size would grow
src/gkhash.h:45: 警告：从此处调用
src/gkhash.h:45: 警告：调用‘kh_resize_iu64’时内联失败：call is unlikely and code size would grow
src/gkhash.h:45: 警告：从此处调用
```
说明还是有问题，不过应该不影响使用，先就这样吧，试试程序再说。
