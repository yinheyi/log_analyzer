#include "feature_manager.h"

FeatureManager FeatureManager::manager_;

FeatureManager& FeatureManager::GetInstance() {
    return manager_;
}

bool FeatureManager::IsMatch(uint32_t featureId, uint32_t logId) const {
    if (commLogIds_.find(logId) != commLogIds_.end()) {
        return true;
    }
    auto iter = featureToLogIds_.find(featureId);
    if (iter == featureToLogIds_.end()) {
        throw std::invalid_argument("feature Id invalid, feature not exist!");
    }
    const auto& logIdSet = iter->second;
    return logIdSet.find(logId) != logIdSet.end();
}

void FeatureManager::AddLogRecord(const string& featureName, uint32_t logId) {
    if (featureName == "comm" || featureName == "Comm" || featureName == "COMM" ||
        featureName == "Common" || featureName == "common") {
        const auto& [it, success] = commLogIds_.insert(logId);
        if (!success) {
            cerr << "Add Common log Record Error! logId = " << logId << endl;
        }
        return;
    }

    uint32_t featureId = GetFeatureId(featureName);
    if (featureId == UINT32_MAX) {
        featureId = featureNames_.size();
        featureNames_.push_back(featureName);
    }
    const auto& [it, success] = featureToLogIds_[featureId].insert(logId);
    if (!success) {
        cerr << "Add log Record Error, featureName = " << featureName << ", logId = " << logId << endl;
    }
}

const vector<string>& FeatureManager::GetFeatureList() const {
    return featureNames_;
}

uint32_t FeatureManager::GetFeatureId(const string& featureName) const {
    for (size_t i = 0; i < featureNames_.size(); ++i) {
        if (featureNames_[i] == featureName) {
            return i;
        }
    }
    return UINT32_MAX;
}