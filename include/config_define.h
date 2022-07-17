/**
 * @file configInfo.h
 * @brief 该文件定义了配置文件对应的数据结构，与配置文件格式一一对应。
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef CONFIG_DEFINE_H
#define CONFIG_DEFINE_H

#include "comm.h"

/**
 * @struct ConfigItem
 * @brief 配置文件的配置项对应的数据结构。
 * @details 当前该数据结构包含6项：特性名、LogId、主题名字、参数1的含义、参数2的含义、参数3的含义、参数4的含义。
 * @note 当参数不存在时，参数含义为空。
 */
struct ConfigItem {
    string featureName;
    uint32_t logId = UINT32_MAX;
    string subject;
    string para1Meaning;
    string para2Meaning;
    string para3Meaning;
    string para4Meaning;
};


/**
 * @enum EntryIndex
 * @brief 定义配置项条目的索引值
 */
enum ConfigEntryIndex : uint8_t {
    CONFIG_ENTRY_INDEX_FEATURENAME = 0,
    CONFIG_ENTRY_INDEX_LOGID = 1,
    CONFIG_ENTRY_INDEX_SUBJECT = 2,
    CONFIG_ENTRY_INDEX_PARAM1 = 3,
    CONFIG_ENTRY_INDEX_PARAM2 = 4,
    CONFIG_ENTRY_INDEX_PARAM3 = 5,
    CONFIG_ENTRY_INDEX_PARAM4 = 6,
    CONFIG_ENTRY_INDEX_BUTT,
};

#endif