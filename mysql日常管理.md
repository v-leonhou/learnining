## mysql 日常使用 

mysql有三种安装方式，通过源码编译安装，通过yum在线下载安装，通过rpm安装离线安装包

本本记录为下载一个程序包，包名为：mysql-5.7.12-el5.x86_64.rpm-bundle.tar

包含有:

mysql-5.7.12-1.el5.x86_64.rpm

mysql-community-client-5.7.12-1.el5.x86_64.rpm

mysql-community-common-5.7.12-1.el5.x86_64.rpm

mysql-community-devel-5.7.12

mysql-community-libs-5.7.12-1.el5.x86_64.rpm

mysql-community-test-5.7.12-1.el5.x86_64.rpm

mysql-community-server-5.7.12-1.el5.x86_64.rpm

mysql-community-embedded-5.7.12-1.el5.x86_64.rpm

mysql-community-embedded-devel-5.7.12-1.el5.x86_64.rpm

mysql-community-libs-compat-5.7.12-1.el5.x86_64.rpm

安装顺序：common->libs->libs-compat->client->server

参考文章：http://www.cnblogs.com/weiok/p/5373270.html


第一阶段：mysql首先会检查是否允许连接，创建用户的时候会加上主机限制，可以限制成本地，某个ip,某个ip段，以及任何地方，只允许从配置的指定地
方登陆，

第二阶段：mysql会检查请求的内容,对某个表，或者某一列是否有执行权限，比如select,update,

| 权限 | 权限级别 | 权限说明 |
| :------: | :------: | :------: |
| CREATE | 数据库、表或索引 | 创建数据库、表或索引权限 |
| DROP | 数据库或表 | 删除数据库或表权限 |
| GRANT OPTION | 数据库、表或保存的程序 | 赋予权限选项 |
| REFERENCES | 数据库或表 |   |
| ALTER | 表 | |   |
| ALTER ROUTINE | 存储过程 | 更改存储过程权限 |
| CREATE ROUTINE | 存储过程 | 创建存储过程权限 |
| EXECUTE |   | 执行存储过程权限 |
| FILE |   | 文件访问权限 |
| CREATE TEMPORARY TABLES | 服务器管理 | 创建临时表权限 |
| PROCESS | 服务器管理 | 查看进程权限 |
| RELOAD | 服务器管理 | 执行flush-hosts, flush-logs, flush-privileges, flush-status, flush-tables, flush-threads, refresh, reload等命令的权 |
| REPLICATION CLIENT | 服务器管理 | 复制权限 |
| REPLICATION SLAVE | 服务器管理 | 复制权限 |
| SHUTDOWN | 服务器管理 | 关闭权限 |
| SUPER | 服务器管理 | 执行kill线程权限 |

权限分类

| 权限分类 | 可能的设置的权限 |
| :------: | :------: | 
| 表权限 | 'Select', 'Insert', 'Update', 'Delete', 'Create', 'Drop', 'Grant', 'References', 'Index', 'Alter' |
| 列权限 | 'Select', 'Insert', 'Update', 'References' |
| 过程权限 | 'Execute', 'Alter Routine', 'Grant' |

## 权限管理实例

* grant all privileges on *.* to jack@'localhost' identified by "jack" with grant option;
* flush privileges; 赋予权限之后要执行刷新权限

```
GRANT命令说明：
ALL PRIVILEGES 是表示所有权限，你也可以使用select、update等权限。

ON 用来指定权限针对哪些库和表。

*.* 中前面的*号用来指定数据库名，后面的*号用来指定表名。

TO 表示将权限赋予某个用户。

jack@'localhost' 表示jack用户，@后面接限制的主机，可以是IP、IP段、域名以及%，%表示任何地方。注意：这里%有的版本不包括本
地，以前碰到过给某个用户设置了%允许任何地方登录，但是在本地登录不了，这个和版本有关系，遇到这个问题再加一个localhost的
用户就可以了。

IDENTIFIED BY 指定用户的登录密码。

WITH GRANT OPTION 这个选项表示该用户可以将自己拥有的权限授权给别人。注意：经常有人在创建操作用户的时候不指定WITH GRANT 
OPTION选项导致后来该用户不能使用GRANT命令创建用户或者给其它用户授权。

备注：可以使用GRANT重复给用户添加权限，权限叠加，比如你先给用户添加一个select权限，然后又给用户添加一个insert权限，那么
该用户就同时拥有了select和insert权限。
```

* 查看当前用户的权限： mysql> show grants;
* 查看某个用户的权限： mysql> show grants for 'jack'@'%';
* 回收权限: mysql> revoke delete on *.* from 'jack'@'localhost';
* 删除用户: mysql> drop user 'jack'@'localhost';
* 对账户重命名: mysql> rename user 'jack'@'%' to 'jim'@'%';
* 修改密码用set password命令: mysql> SET PASSWORD FOR 'root'@'localhost' = PASSWORD('123456');
* 修改密码用mysqladmin: [root@rhel5 ~]# mysqladmin -uroot -p123456 password 1234abcd
* 在丢失root密码的时候： [root@rhel5 ~]# mysqld_safe --skip-grant-tables &
* 关闭,开启，重启mysql服务 /etc/init.d/mysqld start | stop | restart
