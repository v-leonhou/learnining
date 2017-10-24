#!/bin/bash
  #1.安装依赖

  yum install -y gcc texinfo-tex flex zip libgcc.i686 glibc-devel.i686 gcc-c++ gcc

  cd /tmp/ && mkdir installgcc && cd installgcc

  #2.下载文件
  wget http://gcc.skazkaforyou.com/releases/gcc-4.8.2/gcc-4.8.2.tar.gz
  tar zxvf ./gcc-4.8.2.tar.gz

  #2.
  cd ./contrib && ./download_prerequisites

  #3.
  mkdir /usr/local/gcc482/

  #3.
  yum install gmp-devel mpfr-devel libmpc-devel

  #4.
  ./configure --prefix=/usr/local/gcc482 --enable-checking=release --enable-languages=c,c++ --disable-multilib

  #5.
  make && make install

  #6.
   mv /usr/bin/c++ /usr/bin/c++.bak
   ln -s /usr/local/bin/c++ /usr/bin/c++
   mv ./g++ ./g++.bak
   ln -s /usr/local/bin/g++ /usr/bin/g++
   mv ./gcc ./gcc.bak
   ln -s /usr/local/bin/gcc /usr/bin/gcc

    #7.查看系统gcc动态链接库  strings /usr/lib64/libstdc++.so.6 | grep GLIBC
  #如果是：
  #GLIBCXX_3.4
  #GLIBCXX_3.4.1
  #GLIBCXX_3.4.2
  #GLIBCXX_3.4.3
  #GLIBCXX_3.4.4
  #GLIBCXX_3.4.5
  #GLIBCXX_3.4.6
  #GLIBCXX_3.4.7
  #GLIBCXX_3.4.8
  #GLIBCXX_3.4.9
  #GLIBCXX_3.4.10
  #GLIBCXX_3.4.11
  #GLIBCXX_3.4.12
  #GLIBCXX_3.4.13   说明需要更新

  #8.
  cp /usr/local/gcc482/lib64/libstdc++.so.6.0.18 /usr/lib64
  mv /usr/lib64/libstdc++.so.6 /usr/lib64/libstdc++.so.6.bak
  ln -s /usr/lib64/libstdc++.so.6.0.18 /usr/lib64/libstdc++.so.6


