#ifndef _INNER_PUB_H_
#define _INNER_PUB_H_

#include <string>
#include <memory>

#include "inner_master.h"

namespace mission
{

class CallMaster;

class InnerPubOptions
{
    public:
    void init(const std::string& id)
    {
        _id = id;
    }
    template<class M>
    void publish(const M& msg)
    {
        CallMaster::instance()->publish(_id,msg);
    }
    private:
    std::string _id;
};

typedef std::shared_ptr<InnerPubOptions> InnerPubOptionsPtr;

class InnerPublisher
{
    public:
    InnerPublisher(){}
    ~InnerPublisher(){}
    InnerPublisher(const InnerPubOptionsPtr& ops)
    {
        _ops = ops;
    }
    template<class M>
    void publish(const M& msg)
    {
        _ops->publish(msg);
    }
    private:
    InnerPubOptionsPtr _ops;
};

} // mission
#endif // _INNER_PUB_H_