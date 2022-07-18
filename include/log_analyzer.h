#ifndef LOG_ANALYZER_H
#define LOG_ANALYZER_H

#include "comm.h"
#include "log_define.h"

class LogAnalyzer {
public:
    void DoAnalysis(uint32_t featureId);

private:
    void Init(uint32_t featureId);
    string GetLastestLogFile() const;
    void ReadLogsFromFile();
    void GroupingByCallId();
    void InterpretLogs() const;
    void InterpretSingleUserLog(uint32_t userIndex) const;
    void PrintBeginInfo(uint32_t callId) const;
    void PrintEndInfo(uint32_t callId) const;

    uint32_t featureId_ = UINT32_MAX;
    vector<LogItem> vecLogs_;
    vector<uint32_t> vecCallIds_;
    unordered_map<uint32_t, vector<uint32_t>> groups_;    // key值为callId, value为log项在vecLogs_中的索引
};

#endif