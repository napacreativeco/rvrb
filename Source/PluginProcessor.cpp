/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DSPTryAudioProcessor::DSPTryAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                     apvts(*this, nullptr, "PARAMETERS", createParameters())
#endif
{

}





DSPTryAudioProcessor::~DSPTryAudioProcessor()
{
}

//==============================================================================
const juce::String DSPTryAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DSPTryAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DSPTryAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DSPTryAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DSPTryAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DSPTryAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DSPTryAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DSPTryAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DSPTryAudioProcessor::getProgramName (int index)
{
    return {};
}

void DSPTryAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DSPTryAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32> (getTotalNumOutputChannels());

    //reverb.prepare(spec);
    //chorus.prepare(spec);
    processorChain.prepare(spec);
}

void DSPTryAudioProcessor::releaseResources()
{
    processorChain.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DSPTryAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void DSPTryAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();



    // Reverb
    auto& verb = processorChain.template get<verbIndex>();

    auto dryValue = apvts.getRawParameterValue("DRY_ID");
    auto wetValue = apvts.getRawParameterValue("WET_ID");
    auto roomValue = apvts.getRawParameterValue("ROOM_ID");
    auto dampValue = apvts.getRawParameterValue("DAMP_ID");

    reverbParameters.dryLevel = dryValue->load();
    reverbParameters.wetLevel = wetValue->load();
    reverbParameters.roomSize = roomValue->load();
    reverbParameters.damping = dampValue->load();

    verb.setParameters(reverbParameters);


    // Chorus
    auto& chor = processorChain.template get<chorusIndex>();

    chor.setRate(apvts.getRawParameterValue("RATE_ID")->load());
    chor.setDepth(apvts.getRawParameterValue("DEPTH_ID")->load());
    chor.setCentreDelay(apvts.getRawParameterValue("CENTRE_ID")->load());
    chor.setFeedback(apvts.getRawParameterValue("FEEDBACK_ID")->load());
    chor.setMix(apvts.getRawParameterValue("MIX_ID")->load());


    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    //reverb.process(ctx);
    //chorus.process(ctx);

    processorChain.process(ctx);


}

//==============================================================================
bool DSPTryAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DSPTryAudioProcessor::createEditor()
{
    return new DSPTryAudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void DSPTryAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DSPTryAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DSPTryAudioProcessor();
}



juce::AudioProcessorValueTreeState::ParameterLayout DSPTryAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // parameters in here
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // push back to add a new param to the vector
    // reverb
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRY_ID", "Dry", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WET_ID", "Wet", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ROOM_ID", "Room", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DAMP_ID", "Damp", 0.0f, 1.0f, 0.5f));

    // chorus
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATE_ID", "Rate", 0.0f, 100.0f, 50.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH_ID", "Depth", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CENTRE_ID", "Centre", 0.0f, 100.0f, 50.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK_ID", "Feedback", -1.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX_ID", "Mix", 0.0f, 1.0f, 0.5f));

    return { params.begin(), params.end() };

}




