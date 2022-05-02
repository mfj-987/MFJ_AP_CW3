/*
  ==============================================================================

    filterClass.h
    Created: 1 May 2022 9:36:47pm
    Author:  Matt James

  ==============================================================================
*/

#pragma once
#include <vector>
enum {
    SQUARE, //0
    HAMMING,//1
    BLACKMAN,//2
    KAISER,//3
};

class filterProcessor
{
public:
    filterProcessor();
    ~filterProcessor(){};
    
    void setSampleRate(int Samplerate){mSampleRate = Samplerate;};
    
    int getReadPos(int i);
    
    void calcCoeffs();
    
    void normalise();
    
    void windowFunction(int type);
    
    float processSample(float input);
    
    
 //=============================================================
private:
    std::vector<float> mDelayLine;
    std::vector<float> mFilterCoeffs;
    std::vector<float> mFilterWeights;
    int mFilterOrder {126};
    int mSampleRate;
    int mWritePos{0};
    int mReadPos;
    float mFilterCutoff{2000};
    float mVC{0};
    float mL;
    
    
};
