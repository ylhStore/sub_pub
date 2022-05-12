#ifndef _INNER_MASTER_H_
#define _INNER_MASTER_H_

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

#include "inner_sub_base.h"
#include <string>

namespace inner
{
    class Master
    {
    private:
        Master(const Master &);
        Master &operator=(const Master &);
        Master() {}
        ~Master() {}

    public:
        static Master *instance()
        {
            static Master instance;
            return &instance;
        }

    public:
        typedef std::unordered_map<std::string, std::shared_ptr<SubBaseMulMap>> _SubsMap;
        typedef _SubsMap::iterator _SubsMapIterator;

        // 注册 监听
        template <class M, class T>
        SubBaseMulMapIterator regist(const std::string &id, void (T::*fp)(const M &), T *obj)
        {
            _SubsMapIterator _id_map_iter = _id_map.find(id);
            SubBaseMulMapIterator insert_res;
            if (_id_map_iter == _id_map.end())
            {
                std::shared_ptr<SubBaseMulMap> subs_ptr(new SubBaseMulMap());
                insert_res = subs_ptr->insert(std::make_pair(
                    id,
                    std::make_shared<Sub<M, T>>(
                        Sub<M, T>(fp, obj))));
                _id_map.insert(std::make_pair(id, subs_ptr));
            }
            else
            {
                insert_res = _id_map_iter->second->insert(std::make_pair(
                    id,
                    std::make_shared<Sub<M, T>>(
                        Sub<M, T>(fp, obj))));
            }
            return insert_res;
        };

        // 取消 监听
        bool cancellation(const std::string &id, SubBaseMulMapIterator &call_addr)
        {
            _SubsMapIterator id_iter = _id_map.find(id);
            if (id_iter == _id_map.end())
            {
                printf("id_iter is end\n");
                return false;
            }
            SubBaseMulMapIterator sub_type_iter = id_iter->second->find(id);
            if (sub_type_iter != call_addr)
            {
                printf("sub_type_iter != call_addr\n");
                return false;
            }
            printf("cancell id:%s\n", id.c_str());
            id_iter->second->erase(sub_type_iter);

            if (id_iter->second->empty())
            {
                _id_map.erase(id_iter);
            }

            return true;
        }

        template <class M>
        void publish(const std::string &id, const M &msg)
        {
            printf("call id : %s\n", id.c_str());
            _SubsMapIterator id_iter = _id_map.find(id);
            if (id_iter == _id_map.end())
            {
                printf("not find in _id_map\n");
                return;
            }

            SubCallParams params;
            params._value = &msg;

            if (id_iter->second->empty())
            {
                printf("no sub\n");
            }
            for (const auto &_sub : *id_iter->second)
            {
                printf("publish call\n");
                _sub.second->call(params);
            }

            printf("publish ---------------------------end \n\n\n");
        }

    private:
        _SubsMap _id_map;
    };

} // inner

#endif // _INNER_MASTER_H_