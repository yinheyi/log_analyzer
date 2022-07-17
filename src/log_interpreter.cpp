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
    os << endl << cfgInfo_.subject << endl;
    os << "    时间:" << log.time <<  "   logId: = 0x" << std::hex << cfgInfo_.logId << endl;

    if (!cfgInfo_.para1Meaning.empty()) {
        os << "        " << cfgInfo_.para1Meaning << " = 0x" << std::hex << log.param1 << endl;
    }
    if (!cfgInfo_.para2Meaning.empty()) {
        os << "        " << cfgInfo_.para2Meaning << " = 0x" << std::hex << log.param2 << endl;
    }
    if (!cfgInfo_.para3Meaning.empty()) {
        os << "        " << cfgInfo_.para3Meaning << " = 0x" << std::hex << log.param3 << endl;
    }
    if (!cfgInfo_.para4Meaning.empty()) {
        os << "        " << cfgInfo_.para4Meaning << " = 0x" << std::hex << log.param4 << endl;
    }
}

void LogInterpreter::CustomOutput(const LogItem& log, basic_ostream<char>& os) const
{
}

