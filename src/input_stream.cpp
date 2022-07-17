/**
 * @file input_stream.h
 * @brief 该文件定义了输入流类的实现
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "input_stream.h"

TxtFileInputStream::~TxtFileInputStream() {
    if (ifs_.is_open()) {
        ifs_.close();
    }
}

TxtFileInputStream& TxtFileInputStream::operator>>(string& str) {
    getline(ifs_, str);
    return *this;
}

TxtFileInputStream::operator bool() const {
    return ifs_.operator bool();
}


CsvFileReader& CsvFileReader::operator>> (ConfigItem& cfg) {
    isReadSuccess_ = false;
    string lineContent;
    if (!(txtInputStream_ >> lineContent)) {
        return *this;
    }
    vector<string> splits = SplitStr(lineContent);
    if (CheckValidForConfig(splits)) {
        return *this;
    }

    try {
        cfg.featureName = splits[CONFIG_ENTRY_INDEX_FEATURENAME];
        cfg.logId = stoul(splits[CONFIG_ENTRY_INDEX_FEATURENAME], nullptr, 16);
        cfg.subject = splits[CONFIG_ENTRY_INDEX_SUBJECT];
        cfg.para1Meaning = splits[CONFIG_ENTRY_INDEX_PARAM1];
        cfg.para2Meaning = splits[CONFIG_ENTRY_INDEX_PARAM2];
        cfg.para3Meaning = splits[CONFIG_ENTRY_INDEX_PARAM3];
        cfg.para4Meaning = splits[CONFIG_ENTRY_INDEX_PARAM4];
    } catch(std::exception& e) {
        cerr << e.what() << endl;
        cerr << "LOG ID 格式有误，转换失败:" << splits[CONFIG_ENTRY_INDEX_FEATURENAME] << endl;
        return *this;
    }

    isReadSuccess_ = true;
    return *this;
}

CsvFileReader& CsvFileReader::operator>> (LogItem& log) {
    isReadSuccess_ = false;
    string lineContent;
    if (!(txtInputStream_ >> lineContent)) {
        return *this;
    }
    vector<string> splits = SplitStr(lineContent);
    if (CheckValidForLog(splits)) {
        return *this;
    }

    try {
        log.time = splits[LOG_ENTRY_INDEX_TIME];
        log.callId = stoul(splits[LOG_ENTRY_INDEX_CALLID]);
        log.logId = stoul(splits[LOG_ENTRY_INDEX_LOGID].substr(15), nullptr, 16);
        log.param1 = stoul(splits[LOG_ENTRY_INDEX_PARAM1]);
        log.param2 = stoul(splits[LOG_ENTRY_INDEX_PARAM2]);
        log.param3 = stoul(splits[LOG_ENTRY_INDEX_PARAM3]);
        log.param4 = stoul(splits[LOG_ENTRY_INDEX_PARAM4]);
    } catch(std::exception& e) {
        cerr << e.what() << endl;
        cerr << "LOG 解析过程中，数字转换失败, 当前的LOG信息为:" << lineContent << endl;
        return *this;
    }

    isReadSuccess_ = true;
    return *this;
}

bool CsvFileReader::IsEndOfFile() const {
    return txtInputStream_.operator bool();
}

CsvFileReader::operator bool() const {
    return isReadSuccess_;
}

vector<string> CsvFileReader::SplitStr(const string& input) {
    vector<string> rst;
    string temp;
    for (size_t pos = 0; pos < input.size(); ++pos) { 
        if (input[pos] == ',') {
            rst.push_back(temp);
            temp.clear();
            continue;
        }
        temp.push_back(input[pos]);
    }
    if (rst.size() > 0) {
        rst.push_back(temp);
    }
    return rst;
}

bool CsvFileReader::CheckValidForConfig(const vector<string> &strs) {
    if (strs.size() != CONFIG_ENTRY_INDEX_BUTT) {
        cerr << "Config File Entry Error, Expected Num = "
             << CONFIG_ENTRY_INDEX_BUTT << ", Actual Num = " << strs.size() << "!" << endl;
        return false;
    }
    // 跳过行首
    if (strs[0] == "FeatureName") {
        return false;
    }
    return true;
}

bool CsvFileReader::CheckValidForLog(const vector<string> &strs) {
    if (strs.size() != LOG_ENTRY_INDEX_BUTT) {
        cerr << "Log File Entry Error, Expected Num = "
             << LOG_ENTRY_INDEX_BUTT << ", Actual Num = " << strs.size() << "!" << endl;
        return false;
    }
    // 跳过首行
    if (strs[LOG_ENTRY_INDEX_LOGID] == "logId") {
        return false;
    }
    // 过滤掉非DUUEM模块的LOG
    if (strs[LOG_ENTRY_INDEX_LOGID].substr(0, 6) != "DU_UEM") {
        return false;
    }
    return true;
}