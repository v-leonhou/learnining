## 记录一个php函数SScanf写法

php官方文档中是这样说明的
```
根据指定格式解析输入的字符
```
官方标准用法:
```
mixed sscanf ( string $str , string $format [, mixed &$... ] )
```
说明:
`$str`为需要解析的字符串，`$format`为设定的格式，后面都是匹配的输出变量，其中格式用法类似于函数sprintf

并且给出了例子：
```
<?php
// get author info and generate DocBook entry
$auth = "24\tLewis Carroll";
$n = sscanf($auth, "%d\t%s %s", $id, $first, $last);
echo "<author id='$id'>
    <firstname>$first</firstname>
    <surname>$last</surname>
</author>\n";
?>
```

官方给出的都是很简单的例子，最近在CodeIgniter框架源码中有这么一段代码：
```
if (sscanf($this->default_controller, '%[^/]/%s', $class, $method) !== 2)
{
  $method = 'index';
}
```
sscanf参数中如果没有设定匹配的变量，也就是只有两个参数时，返回的是一个匹配的数组，有匹配变量时，返回的是匹配个数。

问题是使用的匹配规则`%[^/]/%s`用法在文档里面好像没有说明。

这里应该是用到的正则匹配%[^/]意思为匹配到不是/的字符，比如如果解析的字符串为'hello/world'，那么匹配的结果就是$class = hello,$method = world














