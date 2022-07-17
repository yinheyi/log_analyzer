/**
 * @file log_interpreter_manager.h
 * @brief 该文件定义了LOG项的解释器的管理类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "comm.h"
#include "log_interpreter.h"

class LogInterpreterManager {
public:
    static LogInterpreterManager& GetInstance();
    void RegInterpreter(uint32_t logId, unique_ptr<LogInterpreter> ptr);
    const unique_ptr<LogInterpreter>& GetLogInterpreter(uint32_t logId) const;

private:
    LogInterpreterManager() = default;
    ~LogInterpreterManager() = default;

    static LogInterpreterManager manager_;
    unordered_map<uint32_t, unique_ptr<LogInterpreter>> table_;
};