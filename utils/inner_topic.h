#ifndef _INNER_TOPIC_H_
#define _INNER_TOPIC_H_

namespace mission
{
// mysub topic

constexpr char DB_MISSIONINFO_UPDATA_TOPIC[] =
    "db/missioninfo/update"; // MissionInfo 更新事件

constexpr char CLOUD_MSG_ON_MISSION_INFO_DONE_TOPIC[] =
    "mission/done"; // Mission 结束事件

} // mission

#endif // _MY_SUB_TOPIC_H_