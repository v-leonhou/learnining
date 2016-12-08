## 编译安装vi

加参数 --enable-multibyte 让vi支持多字符编码

## vi多文档编辑

### 横向切割窗口
* :new 窗口名 //保存后就是文件名
* :split 窗口名 //保存就是文件名 ：sp 窗口名

### 纵向切割窗口
* :vsplit(vsp) 窗口名 

### 关闭窗口
* q! close close只是暂时关闭，内容还在缓冲区
* :tabc //关闭当前窗口
* :tabo //关闭所有窗口

### 窗口切换
* ctr+w+j/k     j/k上下切换

### 纵向调整
* :ctrl+w + 纵向扩大（行数增加）
* :ctrl+w - 纵向缩小 （行数减少）
* :res(ize) num  例如：:res 5，显示行数调整为5行
* :res(ize)+num 把当前窗口高度增加num行
* :res(ize)-num 把当前窗口高度减少num行

### 全局搜索，查找，替换

* :vimgrep /findme/ **/*.*         //第二个参数为要查找的字符串，最后为查找的路径 
```
vimgrep /匹配模式/[g][j] 要搜索的文件/范围 
g：表示是否把每一行的多个匹配结果都加入
j：表示是否搜索完后定位到第一个匹配位置
vimgrep /pattern/ %           在当前打开文件中查找
vimgrep /pattern/ *             在当前目录下查找所有
vimgrep /pattern/ **            在当前目录及子目录下查找所有
vimgrep /pattern/ *.c          查找当前目录下所有.c文件
vimgrep /pattern/ **/*         只查找子目录

cn                                          查找下一个
cp                                          查找上一个
copen                                    打开quickfix
cw                                          打开quickfix
cclose                                   关闭qucikfix
```
* 插件easygrep
* ack.vim（针对大型的项目下easygrep太慢的问题）

[参考](http://codezye.com/2015/11/01/vim%E9%A1%B9%E7%9B%AE%E5%85%A8%E5%B1%80%E6%90%9C%E7%B4%A2%E7%9A%84%E6%96%B9%E6%B3%95%E6%AF%94%E8%BE%83/)

### 窗口横向调整
* :vertical res(ize) num 指定当前窗口为num列
* :vertical res(ize)+num 把当前窗口增加num列
* :vertical res(ize)-num 把当前窗口减少num列

### 窗口重命名
* :f file

### vi打开多文件
* :n 跳转到下一个文件
* :e# 回到刚才编辑的文件

### 文件浏览
* :Ex 开启目录浏览器，可以浏览当前目录下的所有文件，并可以选择
* :Sex 水平分割当前窗口，并在一个窗口中开启目录浏览器
* :ls 显示当前buffer情况

### vi与shell切换
* :shell 可以在不关闭vi的情况下切换到shell命令行
* :exit 从shell回到vi

### 翻页
* ctrl+f          向前翻页  
* ctrl+b          向后翻页  
* ctrl+d          向前翻半页  
* ctrl+u          向后翻半页  

### 查找替换
* :[range]s/from/to/[flags]
* range 搜索范围，没有指定作用域当前行
* range取值范围：
    * %(所有行) 或者具体的1，n 
* flags取值范围:
    1. 'c' confirm,每次替换前询问
    2. 'i' ignore,忽略大小写
    3. 'g' global 不询问，整行替换，如果不加g选项，则只替换每行第一个匹配的字符
    4. 'e' error 不显示错误
  

### 删除所有空白行
* :g/^$/d  

### 查找 ( ? | / )
* ? //向上查找
* / //向下查找

### 多行缩进
* v选择多行然后>或者<
* n>> 或者n<<    //n行缩进  
* .          //重复上一个命令
* 自动缩进
   * == 自动缩进
   * n== 自动缩进n行
   * gg=G 整篇缩进
   

### 解决一个中文乱码问题
* set fileencodings=utf-8  //vi启动时会按照此选项列出的字符编码方式逐一探测打开文件的字符编码，并将fileencoding设置为探测值
* set fileencoding=utf-8  //vi当前编辑的文件的字符编码方式，保存时也是保存为这种字符编码
* set temencoding=utf-8
* set encoding=utf-8

[参考](http://www.cnblogs.com/joeyupdo/archive/2013/03/03/2941737.html)

### 编辑命令
* s  //删除光标所在的一个字符, 光标还在当行
* S  //删除光标所在的一行，光标还在当行，不同于dd
* J  //合并下一行到上一行
* ~  //变换为大写
* /pattern 正向搜索    ?pattern  反向搜索
* v选中一个或多个  V选择一行
* o   //新开一行
* I    //插入到行的开始位置

#### 记录一个奇怪的问题
在vim打开很长的一个类文件时，当看代码看到类的h中间部分或者底部的时候执行查找某个函数，匹配的部分在当前位置上方时有时会发现vim代码高亮失效
解决办法:
:syntax sync fromstart
追根溯源查看帮助说明:help syn-sync 

#### 从vim7.4升级到8.0.86
ubuntu环境
https://github.com/vim/vim下载vim到本地/vim/目录下./configure --prefix=/usr/local/vim  
报错：
```
 no terminal library found
checking for tgetent()... configure: error: NOT FOUND!
      You need to install a terminal library; for example ncurses.
      Or specify the name of the library with --with-tlib.
 ```
 解决办法:
 apt-get install ncurses-dev
重新编译即可

安装ctags
sudo apt-get install exuberant-ctags

vi适用小技巧每次
每次从系统剪贴板粘贴代码到vim中总是会看到代码缩进是乱的，于是分享个小技巧
在normal模式下1 :gg   2:=G
