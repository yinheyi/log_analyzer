/**
 * @file log_interpreter_factory.h
 * @brief 该文件定义了LOG项的解释器类的工厂类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef LOG_INTERPRETER_FACTORY_H
#define LOG_INTERPRETER_FACTORY_H

#include "comm.h"
#include "config_define.h"
#include "log_interpreter.h"

using LogInterpreterCreator = std::function<unique_ptr<LogInterpreter> (const ConfigItem&)>;
class LogInterpreterFactory {
public:
    static LogInterpreterFactory& GetInstance();
    unique_ptr<LogInterpreter> Create(const ConfigItem& cfg) const;
    void RegisterCreatFunc(uint32_t logId, LogInterpreterCreator creator);

private:
    LogInterpreterFactory() = default;
    ~LogInterpreterFactory() = default;
    unique_ptr<LogInterpreter> defaultCreator(const ConfigItem& cfg) const;

    static LogInterpreterFactory factory_;
    unordered_map<uint32_t, LogInterpreterCreator> creatorTable_;
};

#endif