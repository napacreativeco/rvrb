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
class DSPTryAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DSPTryAudioProcessorEditor (DSPTryAudioProcessor&);
    ~DSPTryAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DSPTryAudioProcessor& audioProcessor;


    juce::Slider depthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSPTryAudioProcessorEditor)
};
