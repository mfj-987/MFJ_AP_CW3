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
//    delayProcessor(int sampleRate,int bufferSize);
    ~delayProcessor(){};
    
    void setSampleRate(int sampleRate){mSampleRate = sampleRate;};

    
//    void setBufferSize(const int samplerate, const int maxDelayTime){mSampleRate = samplerate;
//        mDSPBufferSize = maxDelayTime * samplerate;
//        mDSPBuffer.resize(mDSPBufferSize);
//    };
    
    
//    int setMaxDelayTime(const int timeSamps, const int mSampleRate);
//    void setDelayTime(float timeSamps){mDelayTimeSamps = timeSamps;};
    
    
//    float sampsToSecs(int samps){float secs = samps/mSampleRate;
//        return secs;};
//    int secsToSamps(float secs){int samps = secs * mSampleRate;
//        return samps;};
    
    
    void fillDelayBuffer(float value);
    
    void update_delayTimeTap(int timeSamps){mDelayTimeSamps = timeSamps;}
    
    void update_delayTimeTot(int timeSamps){mDelayTot = timeSamps;};
    
    void update_ReadPos1();
    int return_ReadPos1(){return mReadPos1;}
    
    void update_ReadPos2();
    int return_ReadPos2(){return mReadPos2;}
    
    float process_delayTap(){return mDSPBuffer[mReadPos1];}
    float process_delayTot(){return mDSPBuffer[mReadPos2];}
    
    void update_WritePos();
    int return_WritePos(){return mWritePos;}

     
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


