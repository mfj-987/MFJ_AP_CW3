/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "delayClass.h"
#include "filterClass.h"

//==============================================================================
/**
*/
class MattJamesCW3AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MattJamesCW3AudioProcessor();
    ~MattJamesCW3AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    //parameter update functions
    
    void setTapGainMix(double theTapGainMix) {mTapGain.setTargetValue(theTapGainMix);};
    void setFeedbackGain(double theFeedbackGain) {mFdbkGain.setTargetValue(theFeedbackGain);};
    void setMix(float theMix) {mMix.setTargetValue(theMix);};
    void setDelayTimeTotal(double theDelay) {mDelayTot.setTargetValue(theDelay);};
    void setDelayTimeTap(double theDelay) {mDelayTap.setTargetValue(theDelay);};
    juce::AudioProcessorValueTreeState treeState;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
   
    juce::LinearSmoothedValue<float> mTapGain;
    juce::LinearSmoothedValue<float> mFdbkGain;
    juce::LinearSmoothedValue<float> mMix;
    juce::LinearSmoothedValue<int> mDelayTot;
    juce::LinearSmoothedValue<int> mDelayTap;
    
    int mMaxDelaySamples;

    delayProcessor mDelay;
    filterProcessor mTapFilter;
    filterProcessor mTotFilter;
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MattJamesCW3AudioProcessor)
};
