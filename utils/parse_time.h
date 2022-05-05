#ifndef _PARSE_TIME_H_
#define _PARSE_TIME_H_

#include <chrono>
#include <ctime>
#include "CloudMsgOnMission.pb.h"

namespace mission
{

class ParseTime{
    static constexpr int32_t ONE_MINUTE_SECONDS = 60;
    static constexpr int32_t ONE_HOUR_SECONDS = 60*ONE_MINUTE_SECONDS;
    static constexpr int32_t ONE_DAY_SECONDS = 24*ONE_HOUR_SECONDS;
    static constexpr int32_t ONE_WEEK_SECONDS = 7*ONE_DAY_SECONDS;
    static constexpr int32_t NORMAL_MONTH_DAYS[]={
        31, 28,
        31, 30, 
        31, 30, 
        31, 31,
        30, 31,
        30, 31
    };
    static constexpr int32_t NORMAL_MONTH_DAYS_SIZE = sizeof(NORMAL_MONTH_DAYS);
    typedef std::chrono::system_clock::time_point _TimeStampType;
    enum ExecMode
    {
        CycleMode,
        RegularMode
    };
    enum PlanCycle
    {
        EveryDay,
        EveryWeek,
        EveryMonth
    };
    struct MissionExecPlanTypeHelper
    {
        int32_t exec_mode;
        int32_t plan_cycle;
        _TimeStampType exec_startdate;
        std::tm exec_startdate_tm;
        _TimeStampType exec_enddate;
        std::tm exec_enddate_tm;
        std::vector<int32_t> exec_day;
        std::vector<int32_t> exec_time;
        std::time_t tmp_tt;
        _TimeStampType tmp_stamp_tt;

    };
    public:
    /**
     * @brief 使用 基姆拉尔森计算公式 计算是星期几
     * @param year 年
     * @param month 月
     * @param day 日
     * @return YYYY-MM-DD 这天是星期几 [0,6] 对应 [星期一,星期天]
     */
    static int dayOfTheWeek(unsigned int year, unsigned int month, unsigned int day);

    /**
     * @brief 将 MissionExecPlanType 数据转换成 时间戳 集合
     * @param msg MissionExecPlanType 数据
     * @return 时间戳 数组 
     */
    static std::vector<_TimeStampType> parseMissionExecPlanType(const MissionExecPlanType& msg);
    
    static bool missionExecPlanTypeToHelper(const MissionExecPlanType& msg, MissionExecPlanTypeHelper& helper);
    /**
     * @brief 将 MissionExecPlanTypeHelper 数据转换成 时间戳 集合
     * @param msg MissionExecPlanTypeHelper 数据
     * @return 时间戳 数组 
     */
    static std::vector<_TimeStampType> parseHelperWithCycleMode(const MissionExecPlanTypeHelper& helper);
    /**
     * @brief 将 MissionExecPlanTypeHelper 数据转换成 时间戳 集合
     * @param msg MissionExecPlanTypeHelper 数据
     * @return 时间戳 数组 
     */
    static std::vector<_TimeStampType> parseHelperWithRegularMode(const MissionExecPlanTypeHelper& helper);

    // 默认使用的时候要纠正 年月值 即输入的字符串中 年是大于等于1900 月是[1,12]
    static bool parseYYYYMMDDStringTime(const std::string& msg, std::tm &time_info, bool need_correct_year = true, bool need_correct_mon = true);

    static bool parseYYYYMMDDStringTime(const std::string& msg, _TimeStampType &time_stamp);
    
    static bool parseHHMMStringTime(const std::string& msg, std::tm &time_info);

    static bool parseHHMMStringTime(const std::string& msg, int32_t &time_stamp);

    // 获得所在月份的一个月的秒数
    static int32_t oneMonthSeconds(const time_t time_stamp);

    // 获得所在周的秒数
    static int32_t currentWeekSeconds(const time_t time_stamp);
    // 获得所在周的秒数
    static int32_t currentWeekSeconds(const std::tm &time_stamp);
};

} // mission

#endif // _PARSE_TIME_H_