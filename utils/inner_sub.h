#ifndef _INNER_SUB_H_
#define _INNER_SUB_H_

#include <functional>
#include <string>
#include <memory>
#include <unordered_map>
#include "inner_sub_base.h"
#include "inner_master.h"

namespace inner
{
//------------------------------------------------------定义 RAII 的订阅器-------------------
class CallBackHelper
{};

class Master;

// 封装 自己的消息订阅器 
template<class M,class T>
class CallBack : public CallBackHelper
{
    private:
    using ClassFuncType = void(T::*)(const M&);

    public:
    CallBack(const std::string& id,void(T::*fp)(const M&), T* obj):
        _id(id)
    {
        _regist_iter = Master::instance()->regist(id,fp,obj);
        _func = fp;
    }
    ~CallBack()
    {
        Master::instance()->cancellation(_id,_regist_iter);
    }
    private:
    const std::string _id;
    ClassFuncType _func;
    SubBaseMulMapIterator _regist_iter;
};

class SubOptions
{
    public:
    template<class M,class T>
    void init(const std::string& id,void(T::*fp)(const M&), T* obj)
    {
        _sub_ptr.reset(
            new CallBack<M, T>(id,fp,obj)
        );
    }
    SubOptions(){
    }
    ~SubOptions(){
    }
    private:
    std::shared_ptr<CallBackHelper> _sub_ptr;
};

typedef std::shared_ptr<SubOptions> SubOptionsPtr;

class Subscriber
{
    public:
    Subscriber(){
    }
    ~Subscriber(){
    }

    Subscriber(const SubOptionsPtr& ops)
    {
        _ops = ops;
    }
    private:
    SubOptionsPtr _ops;
};

} // inner

#endif // _INNER_SUB_H_