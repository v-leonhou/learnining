## 压缩与解压缩
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
