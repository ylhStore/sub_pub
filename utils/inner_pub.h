#ifndef _INNER_PUB_H_
#define _INNER_PUB_H_

#include <string>
#include <memory>

#include "inner_master.h"

namespace inner
{

class Master;

class PubOptions
{
    public:
    void init(const std::string& id)
    {
        _id = id;
    }
    template<class M>
    void publish(const M& msg)
    {
        Master::instance()->publish(_id,msg);
    }
    private:
    std::string _id;
};

typedef std::shared_ptr<PubOptions> PubOptionsPtr;

class Publisher
{
    public:
    Publisher(){}
    ~Publisher(){}
    Publisher(const PubOptionsPtr& ops)
    {
        _ops = ops;
    }
    template<class M>
    void publish(const M& msg)
    {
        _ops->publish(msg);
    }
    private:
    PubOptionsPtr _ops;
};

} // inner
#endif // _INNER_PUB_H_