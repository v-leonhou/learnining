#### nginx设置把所有的.php文件都穿给php解析器解析，但是这种方式存在严重的安全隐患
```
location ~* \.php$ {
    fastcgi_pass backend;
    # [...]
}
```
在这里，每一个.php结尾的请求，都会传递给 FastCGI 的后台处理程序。这样做的问题是，当完整的路径未能指向文件系统里面一个确切的文件时，默认的 PHP 配置试图是猜测你想执行的是哪个文件。举个例子，如果一个请求中的 /forum/avatar/1232.jpg/file.php 文件不存在，但是/forum/avatar/1232.jpg存在,那么PHP解释器就会取而代之， 使用/forum/avatar/1232.jpg来解释。如果这里面嵌入了 PHP 代码，这段代码就会被执行起来。

解决办法：
* 设置php配置文件中cgi.fix_pathfinfo = 0 只尝试给定的文件路径执行，若不存在，不执行任何代码.
* 设置nginx配置具体文件
```
location ~* （a | b | c)\.php$ {
    fastcgi_pass backend;
    # [...]
}
```

* 对于任何用户可以上传的目录，特别的关闭 PHP 文件的执行权限
```
location /uploaddir {
    location ~ \.php$ {return 403;}
    # [...]
}
```

* 使用 try_files 指令过滤出文件不存在的情况
```
location ~* \.php$ {
    try_files $uri =404;
    fastcgi_pass backend;
    # [...]
}
```

* 使用嵌套的 location 过滤出文件不存在的情况
```
location ~* \.php$ {
    location ~ \..*/.*\.php$ {return 404;}
    fastcgi_pass backend;
    # [...]
}
```

[官网参考](https://www.nginx.com/resources/wiki/start/topics/tutorials/config_pitfalls/)


### php-fpm进程控制信号
* SIGTERM,SIGINT 立即终止进程
* SIGQUIT 平滑终止进程,从容关闭
* SIGUSR1 重新打开日志文件
* SIGUSR2 平滑重载所有worker进程并重新载入配置和二进制模块

    ```
        重载php-fpm
        kill -SIGUSR2 `cat /var/run/php-fpm.pid`
    ```



