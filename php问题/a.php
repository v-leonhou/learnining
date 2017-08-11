<?php

$a[] = [
    'a' => 'nihao',
    'b' => 'women',
    'c' => 'kjjj'
];

foreach( $a as &$m)
{
    $m['k'] = 'hello';
}

$b = $a;

print_r($b);
print_r($a);

for($i=0,$c=count($a);$i<$c;$i++)
{
    $a[$i]['h'] = "是么";
}

unset($a[0]['a']);

echo "\n";
print_r($b);
print_r($a);
