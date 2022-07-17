/**
 * @file logInfo.h
 * @brief 该文件定义了待解析的LOG 项的对应的数据结构。
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#include "comm.h"

/**
 * @struct LogItem
 * @brief LOG项的数据结构定义
 * @details 当前该数据结构包含7项：时间、callId、logId、参数1、参数2、参数3、参数4.
 * @note 当参数不存在时，参数含义为空。
 */
struct LogItem {
    string time;
    uint32_t logId = UINT32_MAX;
    uint32_t callId = UINT32_MAX;
    uint32_t param1 = UINT32_MAX;
    uint32_t param2 = UINT32_MAX;
    uint32_t param3 = UINT32_MAX;
    uint32_t param4 = UINT32_MAX;
};

/**
 * @enum EntryIndex
 * @brief 定义配置项条目的索引值
 */
enum LogEntryIndex : uint8_t {
    // LOG_ENTRY_INDEX_INDEX = 0, 
    LOG_ENTRY_INDEX_TIME = 1,
    LOG_ENTRY_INDEX_CALLID = 2,
    LOG_ENTRY_INDEX_LOGID = 3,
    // LOG_ENTRY_INDEX_LOG = 4,
    LOG_ENTRY_INDEX_PARAM1 = 5,
    LOG_ENTRY_INDEX_PARAM2 = 6,
    LOG_ENTRY_INDEX_PARAM3 = 7,
    LOG_ENTRY_INDEX_PARAM4 = 8,
    LOG_ENTRY_INDEX_BUTT,
};

#endif
