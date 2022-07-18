#include "file_system_manager.h"


FsManager FsManager::fsMng_;

FsManager& FsManager::GetInstance() {
    return fsMng_;
}

void FsManager::Init() {
    try {
        CheckCfgFileExist();
        CheckOrCreateInputDirExist();
        CheckOrCreateOutputDirExist();
    } catch(std::exception& e) {
        cerr << "LOG 分析工具的文件系统初始化失败， 原因如下:" << endl;
        cerr << e.what() << endl;
        throw;
    }
}

const filesystem::path& FsManager::GetCfgFilePath() const {
    return configFilePath;
}

filesystem::path FsManager::FindLastestLogFile() const {

    bool isFind = false;
    filesystem::file_time_type latestTime;
    filesystem::path targetPath;
    for (auto& p : filesystem::directory_iterator(inputPath)) {
        if (p.path().extension() != ".csv") {
            continue;
        }
        auto ftime = p.last_write_time();
        if (ftime < latestTime) {
            latestTime = ftime;
            targetPath = p.path();
            isFind = true;
        }
    }
    if (isFind) {
        return targetPath;
    }
    throw std::logic_error("在log_input目录下，不存在LOG文件(*.csv)");
}

filesystem::path FsManager::CreateOutputFilePath() const {
   string newFileName = CreateFileNameByTime(); 
   return outputPath / newFileName;
}

void FsManager::CheckCfgFileExist() {
    filesystem::directory_entry cfgFile(configFilePath);
    if (!cfgFile.exists()) {
        throw std::logic_error("配置文件不存在，请检查!");
    }
}

void FsManager::CheckOrCreateInputDirExist() {
    try {
        filesystem::directory_entry inputDir(inputPath);
        if (!inputDir.exists()) {
            filesystem::create_directory(inputDir);
        }
    } catch (std::exception& e) {
        throw std::logic_error("LOG输入目录创建失败!");
    }
}

void FsManager::CheckOrCreateOutputDirExist() {
    try {
        filesystem::directory_entry outputDir(outputPath);
        if (!outputDir.exists()) {
            filesystem::create_directory(outputPath);
        }
    } catch (std::exception& e) {
        throw std::logic_error("输出目录创建失败!");
    }
}

string FsManager::CreateFileNameByTime() const {
    try {
        std::time_t tm = time(nullptr);
        std::tm* localTm = localtime(&tm);
        ostringstream oss;
        oss << localTm->tm_year + 1900 << '_';
        oss << setfill('0') << setw(2) << localTm->tm_mon + 1;
        oss << setfill('0') << setw(2) << localTm->tm_mday << '_';
        oss << setfill('0') << setw(2) << localTm->tm_hour;
        oss << setfill('0') << setw(2) << localTm->tm_min << '_';
        oss << setfill('0') << setw(2) << localTm->tm_sec << '_';
        oss << "result.txt";
        return oss.str();
    } catch (std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Error: Create Output File Failed" << endl;
        throw;
    }
}