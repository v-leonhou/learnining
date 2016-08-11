
http1.1中对于几个动作的说明：


![](https://pic1.zhimg.com/05947e8dbdf0ff4815191624efd38f20_r.png)

put 与 post 区别

1. put是幂等的，post不是（幂等操作：无论操作多少次，结果都是一样的，比如：任何数乘以0其结果都为0),所以尽可能优先使用put更新资源，比如重复执行一个put example/users/1 服务器实际上只改变一次，这个特性被称为幂等性，多次post example/users能就创建多个资源

2. put更新的资源是客户端定义的资源  put example/users/1   post是服务端定义的资源 post example/users

3. post example/users/1 如果该资源存在就更新它，若不存在应该抛出资源未找到

4. 

