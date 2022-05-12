#include"utils/inner_node.h"

#include<string>
#include<iostream>

const std::string TOPIC = "hello";

class SubscriberTest
{
    public:
    void init()
    {
        // 初始化订阅者 
        subs = inner::Node::subscribe<std::string>(
            TOPIC,                          // 要订阅的话题
            &SubscriberTest::processMsg,    // 该话题的处理函数
            this
        );
    }
    void processMsg(const std::string& msg)
    {
        std::cout<<"process msg : "<<msg<<std::endl;
    }
    private:
    inner::Subscriber subs;
};

int main()
{
    // 初始化 订阅
    SubscriberTest sub_test;
    sub_test.init();
    
    // 初始化 发布者
    inner::Publisher pub = inner::Node::advertise<std::string>(TOPIC);
    std::string str1 = "str1";
    pub.publish(str1);

    return 0;
}

