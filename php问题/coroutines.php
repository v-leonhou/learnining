<?php
//单向通信
 function logger($fileName)
 {
     $fileHandle = fopen($fileName,'a');
     while(TRUE)
     {
         fwrite($fileHandle,yield . "\n");
     }
 }

$log = logger(__DIR__ . '/log');
$log->send('foo');
$log->send('bar');



// function gen()
// {
//     $ret = (yield 'yield1');
//     var_dump($ret);
//     $ret = (yield 'yield2');
//     var_dump($ret);
// }
//
// $gen = gen();
//
// var_dump($gen->current());
// var_dump($gen->sent('ret1'));
// var_dump($gen->sent('ret2'));

