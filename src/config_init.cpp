
#include "config_init.h"
#include "input_stream.h"
#include "log_interpreter_factory.h"
#include "log_interpreter_manager.h"
#include "feature_manager.h"
#include "file_system_manager.h"

void ConfigInitializer::init() {
    try {
        vector<ConfigItem> cfgInfo = ReadCfgInfoFromFile();
        AddLogFeatureRecords(cfgInfo);
        GenerateLogInterpreters(cfgInfo);
    } catch(std::exception& e) {
        cerr << e.what() << endl;
        cerr << "Error: Config Info Initial Failed!" << endl;
        throw;
    }
}

std::vector<ConfigItem> ConfigInitializer::ReadCfgInfoFromFile() const {
    const auto& path = FsManager::GetInstance().GetCfgFilePath();
    CsvFileReader readerStream(path);

    vector<ConfigItem> result;
    ConfigItem temp;
    while (!readerStream.IsEndOfFile()) { 
        if (readerStream >> temp) {
            result.push_back(temp);
        }
    }
    return result;
}

void ConfigInitializer::AddLogFeatureRecords(std::vector<ConfigItem> &cfgItemList) const {
    FeatureManager &featureMng = FeatureManager::GetInstance();
    for (auto& cfg : cfgItemList) {
        featureMng.AddLogRecord(cfg.featureName, cfg.logId);
    }
}

void ConfigInitializer::GenerateLogInterpreters(std::vector<ConfigItem> &cfgItemList) const {
    const LogInterpreterFactory &factory = LogInterpreterFactory::GetInstance();
    LogInterpreterManager &manager = LogInterpreterManager::GetInstance();
    for (auto& cfg : cfgItemList) {
        std::unique_ptr<LogInterpreter> inst = factory.Create(cfg);
        manager.RegInterpreter(cfg.logId, std::move(inst));
    }
}