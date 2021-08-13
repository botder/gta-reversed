#pragma once

class CTimeInfo {
public:
    unsigned char m_nTimeOn;
    unsigned char m_nTimeOff;
    signed short  m_nOtherTimeModel = -1;

public:
    static void InjectHooks();

public:
    CTimeInfo* FindOtherTimeModel(const char* modelName);

    int GetOtherTimeModel() const { return m_nOtherTimeModel; }

    void SetOtherTimeModel(signed short otherTimeModel) { m_nOtherTimeModel = otherTimeModel; }

    unsigned char GetTimeOn() const { return m_nTimeOn; }

    unsigned char GetTimeOff() const { return m_nTimeOff; }

    void SetTimes(unsigned char timeOn, unsigned char timeOff) { m_nTimeOn = timeOn; m_nTimeOff = timeOff; }
};

VALIDATE_SIZE(CTimeInfo, 0x4);
