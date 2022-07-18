#ifndef FILE_SYSTEM_MANAGER_H
#define FILE_SYSTEM_MANAGER_H

#include "comm.h"

class FsManager {
public:
    static FsManager& GetInstance();

    void Init();
    const filesystem::path& GetCfgFilePath() const;
    filesystem::path FindLastestLogFile() const;
    filesystem::path CreateOutputFilePath() const;

private:
    FsManager() = default;
    ~FsManager() = default;
    void CheckCfgFileExist();
    void CheckOrCreateInputDirExist();
    void CheckOrCreateOutputDirExist();
    string CreateFileNameByTime() const;

    const filesystem::path configFilePath{"config/config.csv"};
    const filesystem::path outputPath{"log_output/"};
    const filesystem::path inputPath{"log_input/"};

    static FsManager fsMng_;
};


#endif