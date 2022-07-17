#ifndef CONFIG_INIT_H
#define CONFIG_INIT_H

#include "comm.h"
#include "config_define.h"
#include "log_interpreter_factory.h"

class ConfigInitializer {
public:
    void init();

private:
    std::vector<ConfigItem> ReadCfgInfoFromFile() const;
    void AddLogFeatureRecords(std::vector<ConfigItem> &cfgItemList) const;
    void GenerateLogInterpreters(std::vector<ConfigItem> &cfgItemList) const;
};


#endif