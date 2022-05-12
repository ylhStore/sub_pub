#ifndef _MY_NEW_SUB_BASE_H_
#define _MY_NEW_SUB_BASE_H_

#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

namespace inner
{
    //---------------------------------------------------定义 订阅器

    struct SubCallParams
    {
        const void *_value;
    };

    class SubBase
    {
    public:
        virtual void call(SubCallParams &param) = 0;
    };

    template <class M, class T>
    class Sub : public SubBase
    {
    public:
        Sub(void (T::*fp)(const M &) , T *obj)
        {
            _func = std::bind(fp, obj, std::placeholders::_1);
        }

        void call(SubCallParams &param) override
        {
            _func(*((M *)param._value));
        }

    private:
        Sub();
        std::function<void(const M &)> _func;
    };

    typedef std::unordered_multimap<std::string, std::shared_ptr<SubBase>> SubBaseMulMap;
    typedef SubBaseMulMap::iterator SubBaseMulMapIterator;

}

#endif // _MY_NEW_SUB_BASE_H_