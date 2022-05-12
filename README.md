# 说明

该模块实现了进程内的发布订阅模式，将回调的管理和触发统一管理，降低模块间的耦合度。

# 示例代码

```c++
 // 初始化 订阅者 
    subs = inner::Node::subscribe<std::string>(
        TOPIC,                          // 要订阅的话题
        &SubscriberTest::processMsg,    // 该话题的处理函数
        this
    );
```

```c++
// 初始化 发布者
    inner::Publisher pub = inner::Node::advertise<std::string>(TOPIC);
    std::string str1 = "str1";
    // 发布 消息
    pub.publish(str1);
```

