编译安装git2.4.0

安装依赖:
```
yum -y install zlib-devel curl-devel openssl-devel perl cpio expat-devel gettext-devel openssl zlib autoconf tk perl-ExtUtils-MakeMaker
```

wget https://github.com/git/git/archive/v2.4.0.tar.gz
tar zxvf v2.4.0.tar.gz

cd git-2.4.0

autoconf
./configure
make

make报错：
```
* tclsh failed; using unoptimized loading
    MSGFMT    po/bg.msg make[1]: *** [po/bg.msg] 错误 127

```

解决办法:
```
yum install tcl  build-essential tk gettext
```
make test 会进行很长的一段test代码，非常耗时，没有执行完我就关了，然后make && make install安装成功！

说明：安装完成后输入git，会提示git命令不存在,需要将安装目录的git执行文件放入/usr/bin/下
