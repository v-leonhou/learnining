今天在vi上使用默认用户登陆系统，在终端上用su切换到root用户后打开vi报错：
```
(gksu:2256): GConf-WARNING **: Client failed to connect to the D-BUS daemon:
Did not receive a reply. Possible causes include: the remote application did not send a reply, the message bus security policy blocked the reply, the reply timeout expired, or the network connection was broken.
GConf 错误：D-BUS 守护进程没有运行
```

解决办法：

应该是shell执行环境不对造成dbus没有启动，执行sudo -s -H完美解决
