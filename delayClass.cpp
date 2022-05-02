/*
  ==============================================================================

    delayClass.cpp
    Created: 30 Apr 2022 6:09:26pm
    Author:  Matt James

  ==============================================================================
*/

#include "delayClass.h"



delayProcessor::delayProcessor(int maxDelaySamples) :mSampleRate(44100),mDSPBufferSize(maxDelaySamples + 1), mDSPBuffer(mDSPBufferSize), mWritePos(0), mReadPos1(0), mReadPos2(0)
    {
        
    }


//delayProcessor::delayProcessor(const int sampleRate, const int bufferSize) :mSampleRate(sampleRate),mDSPBufferSize(bufferSize)
//    {
//       //overload constructor ((USE THIS)) ^^
//    }


//int delayProcessor::setMaxDelayTime(const float time, const int sampleRate)
//    {
//        mDelayTimeMax = time;
//        mSampleRate = sampleRate;
//        mDSPBufferSize = (mDelayTimeMax * mSampleRate) + 1;
//        mDSPBuffer.resize(mDSPBufferSize);
//        return mDelayTimeMax;
//
//    }


void delayProcessor::fillDelayBuffer(float value)
    {
        //value = mAudioBuffer[return_ReadPos1()];
        
        mDSPBuffer[mWritePos] = value;
    }


void delayProcessor::update_ReadPos1()
    {
        mReadPos1 = (mWritePos - mDelayTimeSamps + mDSPBufferSize) % mDSPBufferSize;
//    mReadPos1 = mWritePos;
    }


void delayProcessor::update_ReadPos2()
    {
        mReadPos2 = (mWritePos - mDelayTot + mDSPBufferSize) % mDSPBufferSize;
    }



void delayProcessor::update_WritePos()
    {
        mWritePos = (mWritePos + 1) % mDSPBufferSize;
    }


