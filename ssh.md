生成公匙:ssh-keygen

将公匙上传至远程主机：ssh-copy-id user@root

上传公匙的另外一种方法：ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub

解释:
`后面的冒号表示登录后执行的shell命令，递归的创建.ssh文件夹，并且将本地的~/.ssh/id_rsa.pub重定向到远程机上的.ssh/authorized_keys文件`
