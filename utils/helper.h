#ifndef _MISSION_HELPER_H_
#define _MISSION_HELPER_H_

#include<unordered_map>
#include<list>
#include<chrono>
#include "CloudMsgOnMission.pb.h"

namespace std
{
    /**
     * @brief 为 CloudMsgOnMissionInfo 提供 std::hash<T>特例化实现
     */
    template<>
    struct hash<CloudMsgOnMissionInfo>
    {
        typedef CloudMsgOnMissionInfo argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            // result_type const h1 ( std::hash<mission::MissionInfo>()(s._mission_id) );
            // result_type const h2 ( std::hash<mission::MissionInfo>()(s._mission_id) );
            // return h1 ^ (h2 << 1);
            return std::hash<string>()(s.mission_id());
        }
    };

    /**
     * @brief 为 list<CloudMsgOnMissionInfo>::iterator 提供 std::hash<T>特例化实现
     */
    template<>
    struct hash<list<CloudMsgOnMissionInfo>::iterator>
    {
        typedef list<CloudMsgOnMissionInfo>::iterator  argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            return std::hash<long long>()( (long long)&s);
        }
    };

    /**
     * @brief 为 CloudMsgOnMissionInfo 定义 == 运算符
     */
    bool operator == (const CloudMsgOnMissionInfo &le,const CloudMsgOnMissionInfo &ri);

    /**
     * @brief 为 CloudMsgOnMissionInfo 定义 != 运算符
     */
    bool operator != (const CloudMsgOnMissionInfo &le,const CloudMsgOnMissionInfo &ri);


    /**
     * @brief 为 CloudMsgOnMissionInfo 定义 < 运算符
     */
    bool operator < (const CloudMsgOnMissionInfo &le,const CloudMsgOnMissionInfo &ri);

} // namespace std

// --------------------------------------
// 定义 MissionInfoHelper 以及 其hash 和 ==

namespace mission
{
    namespace helper
    {
        struct MissionInfoHelper
        {
            std::unordered_map<std::string,CloudMsgOnMissionInfo>::iterator info_iter;
            std::chrono::system_clock::time_point time_stamp;
        };
    }// namespace helper
}// namespace mission

namespace std
{
    template<>
    struct hash<list<mission::helper::MissionInfoHelper>::iterator>
    {
        typedef list<mission::helper::MissionInfoHelper>::iterator  argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            return std::hash<long long>()( (long long)&s);
        }
    };

    template<>
    struct hash<mission::helper::MissionInfoHelper>
    {
        typedef mission::helper::MissionInfoHelper  argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            return std::hash<std::string>()( s.info_iter->second.mission_id());
        }
    };


    /**
     * @brief 为 helper::MissionInfoHelper 定义 == 运算符
     */
    bool operator == (const mission::helper::MissionInfoHelper &le,const mission::helper::MissionInfoHelper &ri);

}// namespace std


#endif // _MISSION_HELPER_H_