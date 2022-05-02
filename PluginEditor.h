/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MattJamesCW3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MattJamesCW3AudioProcessorEditor (MattJamesCW3AudioProcessor&);
    ~MattJamesCW3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

juce::Slider mTappedGainMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> TappedGainMixSliderAttachment;
    
    juce::Slider mFeedbackGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> FeedbackGainSliderAttachment;
    
    juce::Slider mMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> MixSliderAttachment;
    
    juce::Slider mDelayTotalSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DelayTimeTotalAttachment;
    
    juce::Slider mDelayTapSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DelayTimeTapAttachment;


    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MattJamesCW3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MattJamesCW3AudioProcessorEditor)
};
