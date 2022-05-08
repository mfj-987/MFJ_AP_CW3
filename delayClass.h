/*
  ==============================================================================

    delayClass.h
    Created: 30 Apr 2022 6:09:26pm
    Author:  Matt James

  ==============================================================================
*/

#pragma once
#include <vector>

class delayProcessor
{
public:
    delayProcessor(int maxDelaySamples);
    ~delayProcessor(){};
    
    
    void setSampleRate(int sampleRate){mSampleRate = sampleRate;};
    
    void fillDelayBuffer(float value);
    
    void update_delayTimeTap(int timeSamps){mDelayTimeSamps = timeSamps;}
    
    void update_delayTimeTot(int timeSamps){mDelayTot = timeSamps;};
    
    void update_ReadPos1();

    
    void update_ReadPos2();

    
    float process_delayTap(){return mDSPBuffer[mReadPos1];}
    float process_delayTot(){return mDSPBuffer[mReadPos2];}
    
    void update_WritePos();


     
private:

    int mSampleRate;
    int mDSPBufferSize;
    std::vector<float> mDSPBuffer;
    int mWritePos;
    int mReadPos1 ;
    int mReadPos2 ;
    int mDelayTimeMax;
    int mDelayTot;
    int mDelayTimeSamps;
    
};


