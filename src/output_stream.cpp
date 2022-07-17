/**
 * @file output_stream.h
 * @brief 该文件定义了输出流管理类的实现
 * @author yinheyi
 * @date 2022/07/16 
 * @version  0.1.0
 */

#include "output_stream.h"
#include "file_system_manager.h"

OStreamManager OStreamManager::single_;

OStreamManager& OStreamManager::GetInstance() {
    return single_;
}

OStreamManager::OStreamManager() {
}

OStreamManager::~OStreamManager() {
    os_ = nullptr;
    if (fileOut_.is_open()) {
        fileOut_.close();
    }
}

void OStreamManager::Init(OStreamType type) {
    streamType_ = type;
}

void OStreamManager::OpenOutputStream() {
    switch (streamType_) {
        case OSTREAM_TYPE_CONSOLE:
            os_ = &cout;
            break;
        case OSTREAM_TYPE_FILE: {
                auto path = FsManager::GetInstance().CreateOutputFilePath();
                fileOut_.open(path);
                if (!fileOut_) {
                    throw runtime_error("ERROR: 创建文件输出流失败! 文件名为: " + path.string());
                }
                os_ = &fileOut_;
            }
            break;
        default:
            throw std::runtime_error("未初始化输出流类型!");
    }
}

void OStreamManager::CloseOutputStream() {
    os_ = nullptr;
    if (streamType_ == OSTREAM_TYPE_FILE) {
        fileOut_.close();
    }
}

basic_ostream<char>& OStreamManager::GetOutputStream() {
    if (os_ == nullptr) {
        throw logic_error(" Nullptr, Result of Uninitialized OStreamManager!");
    }
    return *os_;
}

