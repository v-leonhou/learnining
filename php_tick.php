<?php
declare(ticks =1);
//
$a = pcntl_signal(SIGALRM,function($sig){
    echo "women\n";
},FALSE);

$b = pcntl_alarm(1);

while(1)
{
    sleep(1);
    $a = 20+2;

    $b = 22;
    sleep(1);
    $m = 20;
    $m += $b;

    $k = pcntl_alarm(1);
    echo $k."\n";
    // echo "hello\n";

}
