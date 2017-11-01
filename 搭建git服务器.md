#16-4-11-windows搭建git服务器

最近需要在工作中在服务器上搭建一个git服务器，用于团队的协作。

在网上找了几个帖子

具体参考文章：
http://blog.csdn.net/ccf0703/article/details/7578276
http://blog.csdn.net/marcus_x/article/details/11709461
http://blog.csdn.net/marcus_x/article/details/11709461

按照文章1所述操作之后在我系统中却不能正常运行，报错信息为：
`/usr/bin/git.exe: error while loading shared libraries: ?: cannot open shared object file: No such file or directory`
很明显，这个错误是由于copssh无法读取git执行程序造成的，于是又找了几个文章，尝试过了设置环境变量，包括添加所有的git相关可执行程序为系统环境变量
然并卵，还是报这个错误。。。。。。。。。。。。

终于找到了这个http://www.jinweijie.com/git/step-by-step-setup-git-server-on-windows-with-copssh-msysgit-and-integrate-git-with-visual-studio/

于是按照这个教程，修改了还是报同样的错

最后看到这个https://github.com/msysgit/msysgit/wiki/Setting-up-a-Git-server-on-Windows-using-Git-for-Windows-and-CopSSH

在初始化远程仓库时最好使用 git --bare init   而不要使用：git init

   如果使用了git init初始化，则远程仓库的目录下，也包含work tree，当本地仓库向远程仓库push时,   如果远程仓库正在push的分支上（如果当时不在push的分支，就没有问题）, 那么push后的结果不会反应在work tree上,  也即在远程仓库的目录下对应的文件还是之前的内容，必须得使用git reset --hard才能看到push后的内容.

然后分别创建git.exe git-receive-pack.exe git-upload-pack.exe git-upload-archive.exe 的符号链接到copssh安装目录的/bin文件夹下，问题解决！

我的服务器环境为windows server 2008

copssh control panel v2.4.0

git Git-2.8.1-64-bit


## linux搭建git服务器

可能出现的错误:
1. git-upload-pack: command not found
解决办法:
将git-upload-pack 移到/usr/bin目录下
