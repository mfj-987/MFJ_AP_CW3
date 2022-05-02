/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MattJamesCW3AudioProcessorEditor::MattJamesCW3AudioProcessorEditor (MattJamesCW3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    //tapped gain Slider
    mTappedGainMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mTappedGainMixSlider.setNumDecimalPlacesToDisplay(1);
    mTappedGainMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true,((getWidth()/2)*3) , (getHeight()/2));
    addAndMakeVisible(mTappedGainMixSlider);
    TappedGainMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "TAP_GAIN_MIX", mTappedGainMixSlider);
    
    //==============================================================================
    //feedback gain Slider
    mFeedbackGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mFeedbackGainSlider.setNumDecimalPlacesToDisplay(2);
    mFeedbackGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, (getWidth()/3), (getHeight()/3));
    addAndMakeVisible(mFeedbackGainSlider);
    FeedbackGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "FDBK_GAIN", mFeedbackGainSlider);
    
    //==============================================================================
    //mix slider
    mMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mMixSlider.setNumDecimalPlacesToDisplay(2);
    mMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/2)*3) , (getHeight()/2));
    addAndMakeVisible(mMixSlider);
    MixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "MIX", mMixSlider);
    
    //==============================================================================
    //total delay time slider
    mDelayTotalSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDelayTotalSlider.setNumDecimalPlacesToDisplay(2);
    mDelayTotalSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, (getWidth()/3), (getHeight()/3));
    addAndMakeVisible(mDelayTotalSlider);
    DelayTimeTotalAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "DELAY_TOTAL", mDelayTotalSlider);
    
    //==============================================================================
    //delay tap time slider
    mDelayTapSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDelayTapSlider.setNumDecimalPlacesToDisplay(2);
    mDelayTapSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, (getWidth()/3), (getHeight()/3));
    addAndMakeVisible(mDelayTapSlider);
//    DelayTimeTapAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "DELAY_TAP", mDelayTapSlider);
    DelayTimeTapAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.treeState, "DELAY_TAP", mDelayTapSlider));

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MattJamesCW3AudioProcessorEditor::~MattJamesCW3AudioProcessorEditor()
{
}

//==============================================================================
void MattJamesCW3AudioProcessorEditor::paint (juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.setFont (10.0f);
    g.drawText("Tap Gain Mix", getBounds(), (getWidth()*2), (getHeight()/2));

    g.drawFittedText("Feedback Gain", getBounds(), (getWidth()*2), (getHeight()/2));
}

void MattJamesCW3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    mTappedGainMixSlider.setBounds((getWidth()/3), 0.0, (getWidth()*2.5), (getHeight()/2));
    mFeedbackGainSlider.setBounds(0.0 ,((getHeight()/3)*2), (getWidth()/3), (getHeight()/3));
    mMixSlider.setBounds((getWidth()/3), (getHeight()/2), (getWidth()*2.5), (getHeight()/2));
    mDelayTotalSlider.setBounds(0.0, 0.0, (getWidth()/3), (getHeight()/3));
    mDelayTapSlider.setBounds(0.0, (getHeight()/3), (getWidth()/3), (getHeight()/3));
    
}



