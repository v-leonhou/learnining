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
