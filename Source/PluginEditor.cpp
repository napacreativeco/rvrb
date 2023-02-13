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
    setSize(600, 400);


    //================================================================
    // REVERB
    //================================================================
 
    // DRY
    drySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    drySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    drySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY_ID", drySlider);

    // WET
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    wetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    wetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WET_ID", wetSlider);

    // ROOM
    roomSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    roomSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    roomSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROOM_ID", roomSlider);

    // DAMP
    dampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    dampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DAMP_ID", dampSlider);

    addAndMakeVisible(drySlider);
    addAndMakeVisible(wetSlider);
    addAndMakeVisible(roomSlider);
    addAndMakeVisible(dampSlider);

    //================================================================
    // CHORUS
    //================================================================

    // RATE
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    rateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RATE_ID", rateSlider);

    // DEPTH
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEPTH_ID", depthSlider);

    // CENTRE
    //centreSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //centreSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    //centreSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "CENTRE_ID", centreSlider);

    // FEEDBACK
    //feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    //feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FEEDBACK_ID", feedbackSlider);

    // MIX
    //mixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    //mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX_ID", mixSlider);

    addAndMakeVisible(rateSlider);
    addAndMakeVisible(depthSlider);
    // addAndMakeVisible(centreSlider);
    // addAndMakeVisible(feedbackSlider);
    // addAndMakeVisible(mixSlider);

}

DSPTryAudioProcessorEditor::~DSPTryAudioProcessorEditor()
{
}

//================================================================
// paint
//================================================================
void DSPTryAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //juce::File bgImageFile = juce::File::getCurrentWorkingDirectory().getChildFile("./UI/faceplate-idea.png");
    //background = juce::ImageCache::getFromFile(bgImageFile);

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::faceplateidea_png, BinaryData::faceplateidea_pngSize);
    g.drawImageAt(background, 0, 0);

}

void DSPTryAudioProcessorEditor::resized()
{
    wetSlider.setBounds(170, 48, 100, 100);
    drySlider.setBounds(58, 130, 100, 100);
    roomSlider.setBounds(334, 48, 100, 100);
    dampSlider.setBounds(448, 130, 100, 100);

    rateSlider.setBounds(100, 258, 64, 64);
    depthSlider.setBounds(440, 258, 64, 64);
    // centreSlider.setBounds(200, 110, 100, 100);
    // feedbackSlider.setBounds(300, 110, 100, 100);
    // mixSlider.setBounds(400, 100, 110, 100);

    // scene.setBounds(210, 172, 186, 114);

    
}
