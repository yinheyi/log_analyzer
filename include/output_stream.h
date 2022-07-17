/**
 * @file output_stream.h
 * @brief 该文件定义了日志分析结果的输出流管理类
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#ifndef OUTPUT_STREAM_H
#define OUTPUT_STREAM_H

#include "comm.h"

#define OUTPUT_STREAM (OStreamManager::GetInstance().GetOutputStream())

/**
 * @enum OStreamType
 * @brief 输出流的类型
 * @note 当前支持两种输出操作：输出到控制台和输出到文件
 */
enum OStreamType {
    OSTREAM_TYPE_CONSOLE,
    OSTREAM_TYPE_FILE,
    OSTREAM_TYPE_BUTT,
};


/**
 * @class OStreamManamger
 * @brief 输出流管理类，根据初始化时指定的输出流类型，提供输出流对象。
 * @details 当类型为OSTREAM_TYPE_CONSOLE时， 对应了标准输出流
 *          当类型为OSTREAM_TYPE_FILE时，对应了文件输出流
 * @attention 对于文件输出流时，文件名会根据当前的系统时间进行默认创建，文件的名字在当前目录下。
 */
class OStreamManager {
public:
    static OStreamManager& GetInstance();
    void Init(OStreamType type);
    void OpenOutputStream();
    void CloseOutputStream();
    basic_ostream<char>& GetOutputStream();

private:
    OStreamManager() = default;
    ~OStreamManager();

    string CreateFileName();

    ostream consoleCout;
    ofstream fileCount;
    basic_ostream<char>* os_ = nullptr;
    OStreamType streamType_ = OSTREAM_TYPE_CONSOLE;
    static OStreamManager single_;
};


#endif