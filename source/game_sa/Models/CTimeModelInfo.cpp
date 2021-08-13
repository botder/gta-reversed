#include "StdInc.h"
#include "CModelInfo.h"

void CTimeModelInfo::InjectHooks() {
    ReversibleHooks::Install("CTimeModelInfo", "GetModelType", 0x4C5660, &CTimeModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CTimeModelInfo", "GetTimeInfo", 0x4C5670, &CTimeModelInfo::GetTimeInfo_Reversed);
    ReversibleHooks::Install("CTimeModelInfo", "FindOtherTimeModel", 0x4C47E0, &CTimeModelInfo::FindOtherTimeModel);
}

// 0x4C5640
CTimeModelInfo::CTimeModelInfo() : CAtomicModelInfo() {
    m_timeInfo.m_nOtherTimeModel = -1;
}

// 0x4C5680, 0x4C6270
CTimeModelInfo::~CTimeModelInfo() {

}

// 0x4C5660
ModelInfoType CTimeModelInfo::GetModelType() {
    return ModelInfoType::MODEL_INFO_TIME;
}

// 0x4C5670
tTimeInfo* CTimeModelInfo::GetTimeInfo() {
    return &m_timeInfo;
}

// 0x4C47E0
tTimeInfo* CTimeModelInfo::FindOtherTimeModel(const char* modelName) {
    char timeSwitchModelName[24];
    strcpy(timeSwitchModelName, modelName);

    char* nightSuffix = strstr(timeSwitchModelName, "_nt");

    if (nightSuffix)
    {
        strncpy(nightSuffix, "_dy", 4);
    }
    else
    {
        char* daySuffix = strstr(timeSwitchModelName, "_dy");

        if (!daySuffix)
            return nullptr;

        strncpy(daySuffix, "_nt", 4);
    }

    int index = 0;
    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfoFromHashKey(CKeyGen::GetUppercaseKey(timeSwitchModelName), &index);
    tTimeInfo* timeInfo = modelInfo ? modelInfo->GetTimeInfo() : nullptr;

    if (timeInfo)
    {
        m_timeInfo.m_nOtherTimeModel = index;
        return timeInfo;
    }

    return nullptr;
}

ModelInfoType CTimeModelInfo::GetModelType_Reversed() {
    return CTimeModelInfo::GetModelType();
}

tTimeInfo* CTimeModelInfo::GetTimeInfo_Reversed() {
    return CTimeModelInfo::GetTimeInfo();
}
