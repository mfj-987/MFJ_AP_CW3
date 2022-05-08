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
    setResizable(true, true);
    setResizeLimits(500,400, 1920, 1080);

    //TapGainMix slider
        addAndMakeVisible(mTappedGainMixSlider);
    mTappedGainMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mTappedGainMixSlider.setNumDecimalPlacesToDisplay(1);
    mTappedGainMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/10)) , (getHeight()/10));
    
    
    //label
    addAndMakeVisible(&mTappedGainMixSliderLabel);
    mTappedGainMixSliderLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    mTappedGainMixSliderLabel.setText("Tap Gain Mix", juce::dontSendNotification);
    mTappedGainMixSliderLabel.setColour (juce::Label::textColourId, juce::Colours::cornflowerblue);
    mTappedGainMixSliderLabel.setJustificationType(juce::Justification::horizontallyCentred);
//    mTappedGainMixSliderLabel.attachToComponent(&mTappedGainMixSlider, true);
    
    
    //attachment
    TappedGainMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "TAP_GAIN_MIX", mTappedGainMixSlider);
    
    //==============================================================================
//mix slider
    addAndMakeVisible(mMixSlider);
    mMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mMixSlider.setNumDecimalPlacesToDisplay(2);
    mMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/10)) , (getHeight()/10));
    
    //label
    addAndMakeVisible(mMixSliderLabel);
    mMixSliderLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    mMixSliderLabel.setText("Dry/Wet Mix", juce::dontSendNotification);
    mMixSliderLabel.setColour (juce::Label::textColourId, juce::Colours::cornflowerblue);
    mMixSliderLabel.setJustificationType(juce::Justification::horizontallyCentred);
//    mMixSliderLabel.attachToComponent(&mMixSlider   , true);
    
    //attachment
    MixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "MIX", mMixSlider);
    

    //==============================================================================
    
//feedback gain Slider
    addAndMakeVisible(mFeedbackGainSlider);
    mFeedbackGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mFeedbackGainSlider.setNumDecimalPlacesToDisplay(2);
    mFeedbackGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/10)) , (getHeight()/20));
    mFeedbackGainSlider.setTextValueSuffix("");
    
    //label
    addAndMakeVisible(mFeedbackGainSliderLabel);
    mFeedbackGainSliderLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    mFeedbackGainSliderLabel.setText("Feedback Gain", juce::dontSendNotification);
    mFeedbackGainSliderLabel.setColour (juce::Label::textColourId, juce::Colours::cornflowerblue);
    mFeedbackGainSliderLabel.isVisible();
    mFeedbackGainSliderLabel.setJustificationType(juce::Justification::horizontallyCentred);
    
    //attachment
    FeedbackGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "FDBK_GAIN", mFeedbackGainSlider);
    
    
   
    //==============================================================================
//total delay time slider
    addAndMakeVisible(mDelayTotalSlider);
    mDelayTotalSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDelayTotalSlider.setNumDecimalPlacesToDisplay(2);
    mDelayTotalSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/4)) , (getHeight()/16));
    mDelayTotalSlider.setTextValueSuffix("samps");
    

    //label
    addAndMakeVisible(mDelayTotalSliderLabel);
    mDelayTotalSliderLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    mDelayTotalSliderLabel.setText("Total Delay Time", juce::dontSendNotification);
    mDelayTotalSliderLabel.setColour (juce::Label::textColourId, juce::Colours::cornflowerblue);
    mDelayTotalSliderLabel.setJustificationType(juce::Justification::horizontallyCentred);

    
    //attachment
    DelayTimeTotalAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment >(audioProcessor.treeState, "DELAY_TOTAL", mDelayTotalSlider);
    
    //==============================================================================
//delay tap time slider
    
    addAndMakeVisible(mDelayTapSlider);
    mDelayTapSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDelayTapSlider.setNumDecimalPlacesToDisplay(2);
    mDelayTapSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, ((getWidth()/4)) , (getHeight()/16));
    mDelayTapSlider.setTextValueSuffix("samps");
    
    //label
    addAndMakeVisible(mDelayTapSliderLabel);
    mDelayTapSliderLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    mDelayTapSliderLabel.setText("Delay Tap Time", juce::dontSendNotification);
    mDelayTapSliderLabel.setColour (juce::Label::textColourId, juce::Colours::cornflowerblue);
    mDelayTapSliderLabel.setJustificationType(juce::Justification::centredTop);
//    mDelayTapSliderLabel.attachToComponent(&mDelayTapSlider, true);
   
    DelayTimeTapAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.treeState, "DELAY_TAP", mDelayTapSlider));
    
    addAndMakeVisible(GUI_Title);
    GUI_Title.setFont(juce::Font(28.0f, juce::Font::bold));
    GUI_Title.setText("Matt James CW3 Delay Plugin", juce::dontSendNotification);
                      GUI_Title.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    GUI_Title.setJustificationType(juce::Justification::horizontallyCentred);

}
//==============================================================================

MattJamesCW3AudioProcessorEditor::~MattJamesCW3AudioProcessorEditor()
{
}

//==============================================================================
void MattJamesCW3AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}




void MattJamesCW3AudioProcessorEditor::resized()
{
    juce::Rectangle<int>bounds = getLocalBounds();
    auto title_area = bounds.removeFromTop(bounds.getHeight()/12.0f);
    
    GUI_Title.setBounds(title_area);
    
    auto dial_area = bounds.removeFromTop(getHeight()/3.0f);
    
    auto feedback_area = dial_area.removeFromLeft(dial_area.getWidth()/3.0f);
    mFeedbackGainSliderLabel.setBounds(feedback_area.removeFromTop(feedback_area.getHeight()/4));
    mFeedbackGainSlider.setBounds(feedback_area);
    
    auto tap_area = dial_area.removeFromLeft(dial_area.getWidth()/3.0f);
    mDelayTapSliderLabel.setBounds(tap_area.removeFromTop(tap_area.getHeight()/4));
    mDelayTapSlider.setBounds(tap_area);
    
    
    mDelayTotalSliderLabel.setBounds(dial_area.removeFromTop(tap_area.getHeight()/4));
    mDelayTotalSlider.setBounds(dial_area);
    
    auto fader_area = bounds;
    
    auto tapgain_area = fader_area.removeFromTop(getHeight()/3.0f);
    mTappedGainMixSliderLabel.setBounds(tapgain_area.removeFromRight(fader_area.getWidth()/5));
    mTappedGainMixSlider.setBounds(tapgain_area);
    
    auto mix_area = fader_area;
    mMixSliderLabel.setBounds(mix_area.removeFromRight(mix_area.getWidth()/5));
    mMixSlider.setBounds(mix_area);
    
    
    
    
    
   
    
//    juce::FlexBox flexbox;
//    flexbox.flexDirection = juce::FlexBox::Direction::row;
//    flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
////    flexbox.alignContent = juce::FlexBox::AlignContent::flexStart;
//    flexbox.alignItems= juce::FlexBox::AlignItems::stretch;
//    flexbox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
//    flexbox.alignContent = juce::FlexBox::AlignContent::spaceAround;

    
  
//    juce::Array<juce::FlexItem> dials;
//    dials.add(juce::FlexItem((30.0f * dial_area.getWidth()/100.0f), (bounds.getHeight()/3), mFeedbackGainSlider));
//    dials.add(juce::FlexItem((30.0f * dial_area.getWidth()/100.0f), (bounds.getHeight()/3), mDelayTotalSlider));
//    dials.add(juce::FlexItem((30.0f * dial_area.getWidth()/100.0f), (bounds.getHeight()/3.0f), mDelayTapSlider));
//    flexbox.items = dials;
//    flexbox.performLayout(dial_area);
    
    
    
//    juce::Array<juce::FlexItem> faders;
//    faders.add(juce::FlexItem((getWidth()/3.0f), (getHeight()/3), mTappedGainMixSlider));
//    faders.add(juce::FlexItem((getWidth()/3.0f), (getHeight()/3), mMixSlider ));
//
//    faders.add(juce::FlexItem((getWidth()/3.0f), (getHeight()/3), mTappedGainMixSliderLabel));
//    faders.add(juce::FlexItem((getWidth()/3.0f), (getHeight()/3), mMixSliderLabel));
//
//
//    flexbox3.items = faders;
//    flexbox3.performLayout(bounds);
}



