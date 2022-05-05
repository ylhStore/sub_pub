#ifndef _INNER_MASTER_H_
#define _INNER_MASTER_H_

#include "utils/singleton_macro.h"
#include "inner_sub_base.h"
#include <string>

namespace mission
{
    class CallMaster
    {
        DECLARE_SINGLETON(CallMaster)
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
                    std::make_shared<InnerSub<M, T>>(
                        InnerSub<M, T>(fp, obj))));
                _id_map.insert(std::make_pair(id, subs_ptr));
            }
            else
            {
                insert_res = _id_map_iter->second->insert(std::make_pair(
                    id,
                    std::make_shared<InnerSub<M, T>>(
                        InnerSub<M, T>(fp, obj))));
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

            if(id_iter->second->empty())
            {
                _id_map.erase(id_iter);
            }
            
            return true;
        }
        
        template<class M>
        void publish(const std::string&id, const M& msg)
        {
            printf("call id : %s\n",id.c_str());
            _SubsMapIterator id_iter = _id_map.find(id);
            if(id_iter == _id_map.end())
            {
                printf("not find in _id_map\n");
                return;
            }
            
            InnerSubCallParams params;
            params._value = &msg;

            if(id_iter->second->empty())
            {
                printf("no sub\n");
            }
            for(const auto& _sub : *id_iter->second)
            {
                printf("publish call\n");
                _sub.second->call(params);
            }

            printf("publish ---------------------------end \n\n\n");
            
        }

    private:
        _SubsMap _id_map;
    };

} // mission

#endif // _INNER_MASTER_H_