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
    juce::Label mTappedGainMixSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> TappedGainMixSliderAttachment;
    
    juce::Slider mFeedbackGainSlider;
    juce::Label mFeedbackGainSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> FeedbackGainSliderAttachment;
    
    juce::Slider mMixSlider;
    juce::Label mMixSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> MixSliderAttachment;
    
    juce::Slider mDelayTotalSlider;
    juce::Label mDelayTotalSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DelayTimeTotalAttachment;
    
    juce::Slider mDelayTapSlider;
    juce::Label mDelayTapSliderLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DelayTimeTapAttachment;
    
    juce::Label GUI_Title;

    
  
    MattJamesCW3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MattJamesCW3AudioProcessorEditor)
};
