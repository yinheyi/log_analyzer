/**
 * @file log_interpreter_factory.h
 * @brief 该文件实现了LOG项的解释器的管理类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "log_interpreter_manager.h"

LogInterpreterManager LogInterpreterManager::manager_;

LogInterpreterManager& LogInterpreterManager::GetInstance() {
    return manager_;
}

void LogInterpreterManager::RegInterpreter(uint32_t logId, std::unique_ptr<LogInterpreter> ptr) {
    if (logId == UINT32_MAX || ptr == nullptr) {
        throw std::invalid_argument("regist log interpreter Failed: invalid argument!");
    }
    if (table_.find(logId) != table_.end()) {
        cerr << "regist log interpreter Failed: " << "repeat logId = " << logId << endl;
        throw std::logic_error("regist log interpreter Failed: repeated logId!");
    }

    try {
        table_.emplace(logId, std::move(ptr));
    } catch (...) {
        cerr << "regist log interpreter Failed: " << "current capacity = " << table_.size() << endl;
        throw;
    }
}

const unique_ptr<LogInterpreter>& LogInterpreterManager::GetLogInterpreter(uint32_t logId) const {
    auto iter = table_.find(logId);
    if (iter == table_.end()) {
        const static unique_ptr<LogInterpreter> nullUniquePtr;
        return nullUniquePtr;
    }
    return iter->second;
}