#### 1. php-fpm报错信息如下：
WARNING: [pool www] server reached pm.max_children setting (5), consider raising it
该条信息提示需要增加max_children大小

#### nginx设置把所有的.php文件都穿给php解析器解析，但是这种方式存在严重的安全隐患
```
location ~* \.php$ {
    fastcgi_pass backend;
    # [...]
}
```
在这里，每一个.php结尾的请求，都会传递给 FastCGI 的后台处理程序。 这样做的问题是，当完整的路径未能指向文件系统里面一个确切的文件时， 默认的 PHP 配置试图是猜测你想执行的是哪个文件。举个例子，如果一个请求中的 /forum/avatar/1232.jpg/file.php 文件不存在， 但是/forum/avatar/1232.jpg存在,那么PHP解释器就会取而代之， 使用/forum/avatar/1232.jpg来解释。如果这里面嵌入了 PHP 代码， 这段代码就会被执行起来。

