#include "log_analyzer.h"
#include "input_stream.h"
#include "output_stream.h"
#include "log_interpreter_manager.h"
#include "feature_manager.h"

void LogAnalyzer::DoAnalysis(uint32_t featureId) {
    try {
        Init(featureId);
        string logFile = GetLastestLogFile();
        ReadLogsFromFile(logFile);
        GroupingByCallId();
    } catch(std::exception & e) {
        cout << "日志分析失败，原因如下" << endl;
        cout << e.what() << endl;
    }
}

void LogAnalyzer::Init(uint32_t featureId) {
    featureId_ = featureId;
    vecLogs_.clear();
    vecCallIds_.clear();
    groups_.clear();
}

string LogAnalyzer::GetLastestLogFile() const {
    return "xiaoming";
}

void LogAnalyzer::ReadLogsFromFile(const string& fileName) {
    CsvFileReader readerStream(fileName);
    LogItem temp;
    while (!readerStream.IsEndOfFile()) {
        if (readerStream >> temp) {
            vecLogs_.push_back(temp);
        }
    }
}

void LogAnalyzer::GroupingByCallId() {
    for (size_t i = 0; i < vecLogs_.size(); ++i) {
        if (groups_.find(vecLogs_[i].callId) == groups_.end()) {
            vecCallIds_.push_back(vecLogs_[i].callId);
        }
        groups_[vecLogs_[i].callId].push_back(i);
    }
}

void LogAnalyzer::InterpretLogs() const {
    for (size_t i = 0; i < vecCallIds_.size(); ++i) {
        InterpretSingleUserLog(i);
    }
}

void LogAnalyzer::InterpretSingleUserLog(uint32_t userIndex) const {
    if (userIndex >= vecLogs_.size()) {
        return;
    }

    const LogInterpreterManager& logIntMng = LogInterpreterManager::GetInstance();
    const FeatureManager& featureMng = FeatureManager::GetInstance();

    uint32_t callId = vecCallIds_[userIndex];
    const vector<uint32_t>& vecLogIndexs = groups_.at(callId);

    PrintBeginInfo(callId);
    for (uint32_t i = 0; i < vecLogIndexs.size(); ++i) {
        const LogItem& curLog = vecLogs_.at(vecLogIndexs[i]);
        if (!featureMng.IsMatch(featureId_, curLog.logId)) {
            continue;
        }
        const unique_ptr<LogInterpreter>& logInterpt = logIntMng.GetLogInterpreter(curLog.logId);
        if (logInterpt == nullptr) {
            continue;
        }
        logInterpt->DoInterpret(curLog, OUTPUT_STREAM);
    }
    PrintEndInfo(callId);
}

void LogAnalyzer::PrintBeginInfo(uint32_t callId) const {
    OUTPUT_STREAM << "#############    正在分析用户日志，  CallId = " << callId << "   , 分析结果如下所示:    ##############" << endl;
    OUTPUT_STREAM << endl;
}

void LogAnalyzer::PrintEndInfo(uint32_t callId) const {
    OUTPUT_STREAM << "#############    分析用户日志完毕，  CallId = " << callId << "!                      ##############" << endl;
    OUTPUT_STREAM << endl;
}