/*
  ==============================================================================

    filterClass.cpp
    Created: 1 May 2022 9:36:47pm
    Author:  Matt James

  ==============================================================================
*/

#include "filterClass.h"
#include <math.h>
#include <string.h>

filterProcessor::filterProcessor()
{
    mWritePos = 0;
    mDelayLine.resize(mFilterOrder + 1);
    mFilterCoeffs.resize(mFilterOrder + 1);
    mFilterWeights.resize(mFilterOrder + 1);
}


int filterProcessor::getReadPos(int i)
{
    int index = (mWritePos - i + (mFilterOrder + 1)) % (mFilterOrder + 1);
    return index;
}

void filterProcessor::calcCoeffs()
{
    mVC = mFilterCutoff / mSampleRate;
    mL = mFilterOrder / 2;
    
    for(int k = 0; k < mFilterOrder + 1; ++k)
    {
        if (k == mL)
        {
            mFilterCoeffs[k] = 2 * mVC;
        }
        else
        {
            mFilterCoeffs[k] = (sin(2.0f * M_PI * mVC * (k - mL))) / (M_PI * (k - mL));
        }
    }
}


void filterProcessor::normalise()
{
    float sum = 0.0;
    
    for(int k = 0; k < mFilterOrder + 1; ++k)
    {
        sum = sum + mFilterCoeffs[k];
    }
    
    for(int k = 0; k < mFilterOrder + 1; ++k)
    {
        mFilterCoeffs[k] = mFilterCoeffs[k] / sum;
    }
}

void filterProcessor::windowFunction(int type)
{
   if(type == HAMMING)
   {
       for (int i=0; i < mFilterOrder + 1; i++){
           mFilterWeights[i]= 0.54 - ((0.46)*(cos((2*M_PI* i)/(mFilterOrder+1))));
           
           mFilterCoeffs[i] *= mFilterWeights[i];
       }
   }
   if(type == BLACKMAN)
   {
       for (int i=0; i < mFilterOrder+1; i++){
           mFilterWeights[i]= (0.42)-((0.5)*(cos((2.0*M_PI*i)/(mFilterOrder+1))))+((0.08)*(cos((4.0*M_PI*i)/(mFilterOrder+1))));
           
           mFilterCoeffs[i] *= mFilterWeights[i];
       }
   }
   if(type == KAISER)
   {
       for (int i=0; i < mFilterOrder+1; i++){
           float beta = (sqrtf(2*M_PI));
           float num = j0(beta*(sqrt(1-(pow((2*i)/(mFilterOrder+1)-1,2)))));
           float denom =j0(beta);
           mFilterWeights[i]= num/denom;
           
           mFilterCoeffs[i] *= mFilterWeights[i];
       }
       
   }
}




float filterProcessor::processSample(float input)
{
    mDelayLine[mWritePos] = input;
    
    float filter_sample = 0.0f;
    
    mWritePos = (mWritePos + 1) % (mFilterOrder + 1);
    
    for(int i = 0; i < mFilterOrder; ++i)
    {
        mReadPos = getReadPos(i);
        
        float sampleI = mFilterCoeffs[i] * mDelayLine[mReadPos];
        
        filter_sample += sampleI;
    }

    return filter_sample;
}
