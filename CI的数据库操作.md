问题1：
在控制器中使用`$this->db->query()`执行手写sql，此时返回的结果是一个对象而不是数组

问题2：
在数据库操作中使用query_builder构建group_by 和 limit子句结合起来使用导致数据偏移的坑
