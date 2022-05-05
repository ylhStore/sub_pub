#ifndef _INNER_SUB_H_
#define _INNER_SUB_H_

#include <functional>
#include <string>
#include <memory>
#include <unordered_map>
#include "inner_sub_base.h"
#include "inner_master.h"

namespace mission
{
//------------------------------------------------------定义 RAII 的订阅器-------------------
class InnerCallBackHelper
{
};

class CallMaster;

// 封装 自己的消息订阅器 
template<class M,class T>
class InnerCallBack : public InnerCallBackHelper
{
    private:
    using ClassFuncType = void(T::*)(const M&);


    public:
    InnerCallBack(const std::string& id,void(T::*fp)(const M&), T* obj):
        _id(id)
    {
        _regist_iter = CallMaster::instance()->regist(id,fp,obj);
        _func = fp;
    }
    ~InnerCallBack()
    {
        CallMaster::instance()->cancellation(_id,_regist_iter);
    }
    private:
    const std::string _id;
    ClassFuncType _func;
    SubBaseMulMapIterator _regist_iter;
};

class InnerSubOptions
{
    public:
    template<class M,class T>
    void init(const std::string& id,void(T::*fp)(const M&), T* obj)
    {
        _sub_ptr.reset(
            new InnerCallBack<M, T>(id,fp,obj)
        );
    }
    InnerSubOptions(){
    }
    ~InnerSubOptions(){
    }
    private:
    std::shared_ptr<InnerCallBackHelper> _sub_ptr;
};

typedef std::shared_ptr<InnerSubOptions> InnerSubOptionsPtr;

class InnerSubscriber
{
    public:
    InnerSubscriber(){
    }
    ~InnerSubscriber(){
    }

    InnerSubscriber(const InnerSubOptionsPtr& ops)
    {
        _ops = ops;
    }
    private:
    InnerSubOptionsPtr _ops;
};

} // mission

#endif // _INNER_SUB_H_