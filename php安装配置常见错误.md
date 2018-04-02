```
./configure --prefix=/usr/local/php7 --enable-shmop --enable-wddx --enable-zip --enable-sockets --enable-fpm --with-fpm-user=www --with-fpm-group=www --enable-phpdbg --enable-phpdbg-debug --enable-debug --with-config-file-path=/usr/local/php7/etc --with-bz2 --with-gd --with-jpeg-dir=/usr/local --enable-intl --with-gettext=/usr/local --with-zlib-dir=/usr/local --with-png-dir=/usr/local --with-freetype-dir=/usr/local --enable-gd-native-ttf --with-iconv-dir=/usr/local --enable-exif --enable-mbstring --enable-calendar --with-gettext --with-libxml-dir=/usr/local --with-kerberos --with-openssl --with-zlib --with-pcre-dir --with-pdo-mysql=mysqlnd --with-mysqli=mysqlnd --enable-dom --enable-xml --with-libdir=lib64 --enable-bcmath --enable-ftp --with-pear=/usr/local/php7/lib/php --enable-mysqlnd

```

1. configure: error: xml2-config not found. Please check your libxml2 installation.
 M 解决办法:
  yum install libxml2 libxml2-devel -y

2. configure: error: Please reinstall the BZip2 distribution
 解决办法:
  yum install bzip2-devel
  apt-get install libbz2-dev

3. configure: error: jpeglib.h not found
 解决办法:
 yum install libjpeg-devel -y
 apt-get install libjpeg-dev
 
4. configure: error: png.h not found.
 解决办法:
 yum install libpng-devel -y
 apt-get install libpng-dev
 
5. configure: error: freetype-config not found.
 解决办法:
 yum install  freetype-devel
 apt-get install libfreetype6-dev

6. configure: error: utf8_mime2text() has new signature, but U8T_CANONICAL is missing. This should not happen. Check config.log for additional information.
 解决办法：
 yum -y install libc-client-devel
 
7. configure: error: Unable to detect ICU prefix or no failed. Please verify ICU install prefix and make sure icu-config works.
 解决办法：
 yum install -y icu libicu libicu-devel
 
8. 编译安装Php执行配置时，出现：
   configure: error: Please reinstall the libcurl distribution - easy.h should be in <curl-dir>/include/curl/
   解决办法：
   sudo apt-get install libcurl4-gnutls-dev 
   yum -y install curl-devel
 
9. configure: error: Cannot find OpenSSL\'s <evp.h>   
  解决办法：
apt-get install libssl-dev libsslcommon2-dev
  yum install openssl openssl-devel
 
10. pecl安装event失败 checking for include/event2/event.h... not found
 解决办法：
 手动[下载](https://github.com/expressif/pecl-event-libevent)event源码编译
 
11. mcrypt.h not found
 yum install libmcrypt libmcrypt-devel
 
12. configure: error: bison is required to build PHP/Zend when building a GIT checkout!
 sudo apt-get install bison
 
13. configure: WARNING: You will need re2c 0.13.4 or later if you want to regenerate PHP parsers
