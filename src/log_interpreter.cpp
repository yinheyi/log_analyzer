/**
 * @file log_interpreter.cpp
 * @brief 该文件定义了LOG项的解释器类的实现
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "log_interpreter.h"

void LogInterpreter::DoInterpret(const LogItem& inputLog, basic_ostream<char>& os) const
{
    CommOutput(inputLog, os);
    CustomOutput(inputLog, os);
}

void LogInterpreter::CommOutput(const LogItem& log, basic_ostream<char>& os) const
{
    // 第一行: 时间  callId：xxxx    logId: 0xxxxx.
    os << log.time << "        ";
    os << "callId = " << log.callId << "        ";
    os << "logId: = 0x" << std::hex << cfgInfo_.logId;
    os << endl;

    // 第二行： 主题
    os << cfgInfo_.subject << endl;

    if (!cfgInfo_.para1Meaning.empty()) {
        os << cfgInfo_.para1Meaning << " = " << log.param1 << "    ";
    }
    if (!cfgInfo_.para2Meaning.empty()) {
        os << cfgInfo_.para2Meaning << " = " << log.param2 << "    ";
    }
    if (!cfgInfo_.para3Meaning.empty()) {
        os << cfgInfo_.para3Meaning << " = " << log.param3 << "    ";
    }
    if (!cfgInfo_.para4Meaning.empty()) {
        os << cfgInfo_.para4Meaning << " = " << log.param4 << "    ";
    }
    os << endl;
}

void LogInterpreter::CustomOutput(const LogItem& log, basic_ostream<char>& os) const
{
}

