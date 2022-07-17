#ifndef FEATURE_MANAGER_H
#define FEATURE_MANAGER_H

#include "comm.h"

class FeatureManager {
public:
    static FeatureManager& GetInstance();
    bool IsMatch(uint32_t featureId, uint32_t logId) const;
    void AddLogRecord(const string& featureName, uint32_t logId);
    const vector<string>& GetFeatureList() const;
    bool CheeckFeatureIdValid(uint32_t featureId) const;

private:
    FeatureManager() = default;
    ~FeatureManager() = default;
    uint32_t GetFeatureId(const string& featureName) const;

    unordered_set<uint32_t> commLogIds_;       // 公共的logId集合
    vector<string> featureNames_;
    unordered_map<uint32_t, unordered_set<uint32_t>> featureToLogIds_;
    static FeatureManager manager_;
};


#endif