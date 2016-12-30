这是在一个群里看到有个人的提问:

```
$list = [];//巨大的数组
/*写法一*/
for($i = 0;$i<count($list);$i++)
{
   $item = array_pop($list);
   $temp[$item['id']] = $item;
}

/*写法二*/
foreach($list as $key => $value)
{
   $tem['$value['id'] = $value;
   unset($list[$key]);
}


写法二的情况下回在第一次unset的时候php需要被动的复制出一个相同的数组来，如果数组占用500兆，那么复制下就变成1G了
