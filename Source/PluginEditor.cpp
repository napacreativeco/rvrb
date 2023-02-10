/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DSPTryAudioProcessorEditor::DSPTryAudioProcessorEditor (DSPTryAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);

    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEPTH_ID", depthSlider);

    addAndMakeVisible(depthSlider);
}

DSPTryAudioProcessorEditor::~DSPTryAudioProcessorEditor()
{
}

//==============================================================================
void DSPTryAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DSPTryAudioProcessorEditor::resized()
{
    depthSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 50, 200, 100);
}
