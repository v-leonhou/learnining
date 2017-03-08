生成公匙:ssh-keygen

将公匙上传至远程主机：ssh-copy-id user@root

上传公匙的另外一种方法：ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub

命令解释:

`后面的冒号表示登录后执行的shell命令，递归的创建.ssh文件夹，并且将本地的~/.ssh/id_rsa.pub重定向到远程机上的.ssh/authorized_keys文件`

通过ssh登陆服务器的时候会出现各种错误，最近在我的vps上面开启免密码登陆的过程中还是踩了不少坑

1. Authentication refused: bad ownership or modes for directory

此处错误为目录权限不正确,当前用户目录权限必须设置为550

2. .ssh/authorsized.keys文件权限为600

最后，遇到ssh登陆不上的问题，很多新手会盲目的百度或者搜索找资料，却不知道最精确的问题其实都在你的服务器日志上面，so:
```
有问题，一定要记得先看日志。。。。。

有问题，一定要记得先看日志。。。。。

有问题，一定要记得先看日志。。。。。
```
重要的事情说三遍。。。。。。。
