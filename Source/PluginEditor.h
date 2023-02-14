/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class DSPTryAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                    public juce::Button::Listener

{
public:
    DSPTryAudioProcessorEditor (DSPTryAudioProcessor&);
    ~DSPTryAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DSPTryAudioProcessor& audioProcessor;

    OtherLookAndFeel otherLookAndFeel;

    // Reverb
    juce::Slider drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;

    juce::Slider wetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;

    juce::Slider roomSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSliderAttachment;

    juce::Slider dampSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampSliderAttachment;

    // Chorus
    juce::Slider rateSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;

    juce::Slider depthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;

    juce::Slider centreSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centreSliderAttachment;

    juce::Slider feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;

    juce::Slider mixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    //Bypass
    juce::TextButton chorusBypassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> chorusBypassAttachment;

    juce::Image background;
    juce::Image dotActive;
    juce::Image dotInactive;

    juce::GlowEffect glow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSPTryAudioProcessorEditor)
};


