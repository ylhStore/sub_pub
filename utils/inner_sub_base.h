#ifndef _MY_NEW_SUB_BASE_H_
#define _MY_NEW_SUB_BASE_H_

#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

namespace mission
{
    //---------------------------------------------------定义 订阅器

    struct InnerSubCallParams
    {
        const void *_value;
    };

    class InnerSubBase
    {
    public:
        virtual void call(InnerSubCallParams &param) = 0;
    };

    template <class M, class T>
    class InnerSub : public InnerSubBase
    {
    public:
        InnerSub(void (T::*fp)(const M &) , T *obj)
        {
            _func = std::bind(fp, obj, std::placeholders::_1);
        }

        void call(InnerSubCallParams &param) override
        {
            _func(*((M *)param._value));
        }

    private:
        InnerSub();
        std::function<void(const M &)> _func;
    };

    typedef std::unordered_multimap<std::string, std::shared_ptr<InnerSubBase>> SubBaseMulMap;
    typedef SubBaseMulMap::iterator SubBaseMulMapIterator;

}

#endif // _MY_NEW_SUB_BASE_H_