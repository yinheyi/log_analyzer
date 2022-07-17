/**
 * @file log_interpreter.h
 * @brief 该文件定义了LOG项的解释器类声明
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef LOG_INTERPRETER_H
#define LOG_INTERPRETER_H

#include "comm.h"
#include "config_define.h"
#include "log_define.h"

/**
 * @class LogInterpreter
 * @brief 通用的LOG项解释器
 * @details 通过配置文件的配置项初始化不同的log项解释器, 不同的logId, 对应不同的log解释器。
 * @note 该类定义了一个私有的自定义输出接口，如果要针对某一个logId进行定制化，请继承该类。
 */
class LogInterpreter {
public:
    LogInterpreter(const ConfigItem& inputCfg) : cfgInfo_(inputCfg) {}
    virtual ~LogInterpreter() = default;
    void DoInterpret(const LogItem& inputLog, basic_ostream<char>& os) const;

protected:
    const ConfigItem cfgInfo_;

private:
    void CommOutput(const LogItem& log, basic_ostream<char>& os) const;
    virtual void CustomOutput(const LogItem& log, basic_ostream<char>& os) const;
};


#endif