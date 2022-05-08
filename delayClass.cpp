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

void delayProcessor::fillDelayBuffer(float value)
    {
        mDSPBuffer[mWritePos] = value;
    }


void delayProcessor::update_ReadPos1()
    {
        mReadPos1 = (mWritePos - mDelayTimeSamps + mDSPBufferSize) % mDSPBufferSize;
    }


void delayProcessor::update_ReadPos2()
    {
        mReadPos2 = (mWritePos - (int)mDelayTot + mDSPBufferSize) % mDSPBufferSize;
    }



void delayProcessor::update_WritePos()
    {
        mWritePos = (mWritePos + 1) % mDSPBufferSize;
    }


