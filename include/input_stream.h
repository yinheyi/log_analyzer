/**
 * @file input_stream.h
 * @brief 该文件定义了输入流类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef INPUT_STREAM_H
#define INPUT_STREAM_H

#include "comm.h"
#include "config_define.h"
#include "log_define.h"

/**
 * @class TxtFileInputStream
 * @brief Txt文件输入流类
 * @details 
 * @attention 一次输入，读取一行。 
 */
class TxtFileInputStream final {
public:
    TxtFileInputStream(const string& file) : ifs_(file) {}
    ~TxtFileInputStream();
    TxtFileInputStream& operator>>(string& str);
    operator bool() const;
    
private:
    ifstream ifs_;
};

/**
 * @class CsvFileReader
 * @brief CSV 文件读取类
 * @details 该类调用TxtFileInputStram流完成行读取，然后再把行进行解析，当前支持两种类型的解析:ConfigItem 和 LogItem.
 */
class CsvFileReader {
public:
    CsvFileReader(const string& file) : txtInputStream_(file) {}
    ~CsvFileReader() = default;
    CsvFileReader& operator>> (ConfigItem& cfg);
    CsvFileReader& operator>> (LogItem& log);
    bool IsEndOfFile() const; 
    operator bool() const;

private:
    vector<string> SplitStr(const string& input);
    bool CheckValidForConfig(const vector<string> &strs);
    bool CheckValidForLog(const vector<string> &strs);

    bool isReadSuccess_ = false;
    TxtFileInputStream txtInputStream_;
};


#endif