/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MattJamesCW3AudioProcessor::MattJamesCW3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::mono(), true)
                     #endif
                       ) , treeState(*this, nullptr, "Parameters" , createParameters()),
                        mMaxDelaySamples(176400),
                        mDelay (mMaxDelaySamples)
#endif
{
    mTapGain.setTargetValue(0.0f);
    mFdbkGain.setTargetValue(0.0f);
    mMix.setTargetValue(0.0f);
    mDelayTot.setTargetValue(0);
    mDelayTap.setTargetValue(0);
}

MattJamesCW3AudioProcessor::~MattJamesCW3AudioProcessor()
{
}

//==============================================================================
const juce::String MattJamesCW3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MattJamesCW3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MattJamesCW3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MattJamesCW3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MattJamesCW3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MattJamesCW3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MattJamesCW3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void MattJamesCW3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MattJamesCW3AudioProcessor::getProgramName (int index)
{
    return {};
}

void MattJamesCW3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MattJamesCW3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mTapGain.reset(sampleRate, 0.1);
    mFdbkGain.reset(sampleRate, 0.1);
    mMix.reset(sampleRate, 0.1);
    mDelayTap.reset(sampleRate, 0.1);
    mDelayTot.reset(sampleRate, 0.1);
    
    mDelay.setSampleRate(sampleRate);
//    mDelay.setBufferSize(sampleRate,mMaxDelayTime);
   
//    mDelay.setMaxDelayTime(3.0f, sampleRate);
    
    //set filter specs
    mTotFilter.setSampleRate(sampleRate);
    mTotFilter.calcCoeffs();
    mTotFilter.windowFunction(HAMMING);
    mTotFilter.normalise();
    
    mTapFilter.setSampleRate(sampleRate);
    mTapFilter.calcCoeffs();
    mTapFilter.windowFunction(HAMMING);
    mTapFilter.normalise();
    
}


void MattJamesCW3AudioProcessor::releaseResources()
{
  
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MattJamesCW3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MattJamesCW3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // channel loop to clear outputs
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // channel loop (should be mono only)
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* audioBuffer = buffer.getWritePointer (channel);
        
        
//==========================================================================================================
//loop through block of samples
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        auto sample_branch0 = audioBuffer[sample];
        
        mDelay.update_WritePos();
        
    //Read 1st delay branch out
        auto delayTapValue = treeState.getRawParameterValue("DELAY_TAP");
        setDelayTimeTap(*delayTapValue);
        
        int delayTap = mDelayTap.getNextValue();
        
        mDelay.update_delayTimeTap(delayTap);
        
        mDelay.update_ReadPos1();
        
        auto sample_branch3 = mDelay.process_delayTap();
        
    //LP_FILTER BOTTOM BRANCH
        auto sample_branch5 = mTapFilter.processSample(sample_branch3);
        
    //DELAY_TOT
        auto delayTotValue = treeState.getRawParameterValue("DELAY_TOTAL");
        setDelayTimeTotal(*delayTotValue);
        int delayTot = mDelayTot.getNextValue();
        mDelay.update_delayTimeTot(delayTot);
        
        mDelay.update_ReadPos2();
        auto sample_branch4 = mDelay.process_delayTot();

    //LP FILTER
        auto sample_branch6 = mTotFilter.processSample(sample_branch4);
        
    //TAP_GAIN
        auto tapGainValue = treeState.getRawParameterValue("TAP_GAIN_MIX");
        setTapGainMix(*tapGainValue);
        auto tapMixGain = mTapGain.getNextValue();

        
        auto sample_branch7 = sample_branch6 * (1.0f - (tapMixGain));

        auto sample_branch8 = sample_branch5 * tapMixGain;

        auto sample_branch9 = sample_branch7 + sample_branch8;
        
        


    //FEEDBACK LOOP
       auto fdbkGainValue = treeState.getRawParameterValue("FDBK_GAIN");
       setFeedbackGain(*fdbkGainValue);

        auto fdbkGain = mFdbkGain.getNextValue();
        auto sample_branch2 = sample_branch0 + (fdbkGain * sample_branch6);

        mDelay.fillDelayBuffer(sample_branch2);
        

    //MIX
        auto mixValue = treeState.getRawParameterValue("MIX");
        setMix(*mixValue);
        auto mixGain = mMix.getNextValue();
            
        auto sample_branch1 = sample_branch0 * (1.0f - mixGain);
        
        auto sample_branch10 = sample_branch9 * mixGain;
        
        auto sample_branch11 = sample_branch1 + sample_branch10;
        
        audioBuffer[sample] = sample_branch11;
        
        }
    }
}


//==============================================================================
bool MattJamesCW3AudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* MattJamesCW3AudioProcessor::createEditor()
{
    return new MattJamesCW3AudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void MattJamesCW3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
 
}

void MattJamesCW3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MattJamesCW3AudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout MattJamesCW3AudioProcessor:: createParameters()
{
    
    //creating a vector of ranged audio parameters to store user controlled parameters in
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    //Storing parameters
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("TAP_GAIN_MIX","Tapped Gain Mix",0.0f,1.0f,0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FDBK_GAIN", "Feedback Gain",0.0f,1.0f,0.4f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Dry/Wet Mix",0.0f,1.0f, 0.5f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterInt>("DELAY_TOTAL", "Total delay time (N+M samps)",0,441000,1200.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterInt>("DELAY_TAP", " delay tap time (N samps)",0,220500,400.0f));

    
    return {parameters.begin(), parameters.end()};
}

