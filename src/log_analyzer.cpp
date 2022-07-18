#include "log_analyzer.h"
#include "input_stream.h"
#include "output_stream.h"
#include "log_interpreter_manager.h"
#include "feature_manager.h"
#include "file_system_manager.h"

void LogAnalyzer::DoAnalysis(uint32_t featureId) {
    OStreamManager::GetInstance().OpenOutputStream();
    try {
        Init(featureId);
        auto path = FsManager::GetInstance().FindLastestLogFile();
        ReadLogsFromFile(path.string());
        GroupingByCallId();
        InterpretLogs();
    } catch(std::exception & e) {
        cout << "日志分析失败，原因如下: " << endl;
        cout << e.what() << endl;
    }
    OStreamManager::GetInstance().CloseOutputStream();
}

void LogAnalyzer::Init(uint32_t featureId) {
    if (!FeatureManager::GetInstance().CheeckFeatureIdValid(featureId)) {
        throw std::logic_error("输入的序号无效, 你是不是傻呢！！!"); 
    }
    featureId_ = featureId;
    vecLogs_.clear();
    vecCallIds_.clear();
    groups_.clear();
}

void LogAnalyzer::ReadLogsFromFile(const string& fileName) {
    try {
        CsvFileReader readerStream(fileName);
        LogItem temp;
        while (!readerStream.IsEndOfFile()) {
            if (readerStream >> temp) {
                vecLogs_.push_back(temp);
            }
        }
    } catch (std::exception& e) {
        cerr << "读取log文件 " << fileName << "失败，原因如下: " << endl;
        throw std::runtime_error("读取log 文件失败!");
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
    OUTPUT_STREAM << "--------------------------------------------------------------------------" << endl;
    OUTPUT_STREAM << "                         用户: CallId = " << std::dec << callId  << endl;
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
}

void LogAnalyzer::PrintEndInfo(uint32_t callId) const {
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
    OUTPUT_STREAM << endl;
}