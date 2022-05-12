#ifndef _INNER_NODE_H_
#define _INNER_NODE_H_

/**
 * @brief 进程内部的发布/订阅实现
 * 
 * 同一个话题可以有多个订阅者 也可以有多个发布者
 * 实际上是把回调的管理和触发给抽离出来 本质上还是回调 
 * 目前没有做额外的线程管理 所以触发是在同一个线程中
 * 
 * 注意：消息数据的类型没有验证 发布订阅时只靠话题名做消息的分发 使用者需要自己保证数据类型的正确
 * 
 * 订阅的回调目前只支持类的成员函数
 * 
 */

#include "inner_sub.h"
#include "inner_pub.h"

namespace inner
{

class Node
{
    public:
    static Subscriber subscribe(SubOptionsPtr& ops)
    {
        return Subscriber(ops);
    }

    template<class M, class T>
    static Subscriber subscribe(const std::string& topic,void(T::*fp)(const M&), T* obj)
    {
        SubOptionsPtr ops(new SubOptions());
        ops->init(topic,fp,obj);

        return subscribe(ops);
    }

    static Publisher advertise(PubOptionsPtr& ops)
    {
        return Publisher(ops);
    }

    template<class M>
    static Publisher advertise(const std::string& topic)
    {
        PubOptionsPtr ops(new PubOptions());
        ops->init(topic);
        
        return advertise(ops);
    }
};

} // inner

#endif // _INNER_NODE_H_