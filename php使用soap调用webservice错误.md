#### 问题场景
```
服务器:centos
php：7.0.5
服务器采用nginx+php-fpm
```

####  问题描述

soap调用是之前写的，代码已经运行一段时间，之前也偶尔出现加载不出结果的情况，因为有的时候可以加载出来，所以之前还是怀疑是Webservice不稳定

导致的，但是从前两天开始，我发现服务器日志开始出现大量`Severity: Error --> SOAP-ERROR: Parsing WSD: Couldn't load from`的错误信息,于是检

查代码发现现在都加载不出来了，无法获取webservice结果，网上google了好久还是没有找到解决办法，在我的测试机上，同样的环境，测试机访问正常。


....被这个问题折腾了一天了，刚才重启了下php-fpm问题竟然解决！！！！！！！

####  问题重现 

在重启php-fpm后过了一天我再检查服务器发现同样的问题又出现了，难道真是php-fpm的问题么？今天重新Google了一下，在zend论坛上发现了这样

一个[帖子](http://forums.zend.com/viewtopic.php?f=8&t=116708)，我的问题应该属于后者，所以我按照贴子的说明在调用_soapclient客户端之前先调用

了函数`libxml_disable_entity_loader(false);`

