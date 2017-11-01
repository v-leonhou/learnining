<?php

function microtime_flot()
{
    list($usec,$sec) = explode(" ",microtime());
    return ((float)$usec + (float)$sec);
}

$start = microtime_flot();
function xrange($start,$end)
{
    for($i=$start;$i<$end;$i++)
    {
        yield $i;
    }
}


class xrange implements iterator
{
    private $var;
    private $key = 0;
    private $end;
    public function __construct($start,$end)
    {
        $this->var = $start;
        $this->end = $end;
    }

    public function current()
    {
        return $this->var;
    }

    public function next()
    {
        ++$this->key;
        return $this->var++;
    }

    public function valid()
    {
        return $this->var > $this->end ? FALSE : TRUE;
    }

    public function key()
    {
        return $this->key;
    }

    public function rewind()
    {
        $this->key = 0;
    }
}

//$r = new xrange(0,1000000);
//$r = range(0,1000000);
//$r = xrange(0,1000000);
//foreach( $r as $k => $v )
//{
    ////echo $k . ' => ' . $v . PHP_EOL;
//}

//echo memory_get_peak_usage()/(1024*1024).'兆内存'.PHP_EOL;
//$end = microtime_flot();
//echo "脚本执行时间" . ($end - $start).PHP_EOL;
function test()
{
    yield "nihao".PHP_EOL;
}

echo test()->current();
var_dump(test());
var_dump(test()->key());
var_dump(test()->next());
