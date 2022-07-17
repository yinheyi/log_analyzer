/**
 * @file log_interpreter_factory.h
 * @brief 该文件实现了LOG项的解释器类的工厂类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "log_interpreter_factory.h"

LogInterpreterFactory LogInterpreterFactory::factory_;

LogInterpreterFactory& LogInterpreterFactory::GetInstance() {
    return factory_;
}

unique_ptr<LogInterpreter> LogInterpreterFactory::Create(const ConfigItem& cfg) const {
    auto iter = creatorTable_.find(cfg.logId);
    if (iter == creatorTable_.end()) {
        return defaultCreator(cfg);
    }
    return iter->second(cfg);
}

void LogInterpreterFactory::RegisterCreatFunc(uint32_t logId, LogInterpreterCreator creator) {
    if (logId == UINT32_MAX || creator == nullptr) {
        throw std::invalid_argument("regist creator Failed: invalid argument!");
    }
    if (creatorTable_.find(logId) != creatorTable_.end()) {
        cerr << "regist creator Failed: " << "repeat logId = " << logId << endl;
        throw std::logic_error("creator repeated logId!");
    }

    try {
        creatorTable_.emplace(logId, creator);
    } catch (...) {
        cerr << "regist creator Failed: " << "current capacity = " << creatorTable_.size() << endl;
        throw;
    }
}

unique_ptr<LogInterpreter> LogInterpreterFactory::defaultCreator(const ConfigItem& cfg) const {
    return make_unique<LogInterpreter>(cfg);
}