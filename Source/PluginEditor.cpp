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

    setLookAndFeel(&otherLookAndFeel);

    addAndMakeVisible(audioProcessor.waveViewer);

    chorusBypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    chorusBypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    chorusBypassButton.setToggleable(true);
    chorusBypassButton.setClickingTogglesState(true);

    chorusBypassButton.onClick = [this]()
    { 
        auto state = chorusBypassButton.getToggleState();
        if (state == true)
        {
            audioProcessor.processorChain.setBypassed<1>(true);
        }
        if (state == false)
        {
            audioProcessor.processorChain.setBypassed<1>(false);
        }
        repaint();
    };
    addAndMakeVisible(chorusBypassButton);

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

    // BYPASS
    chorusBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "MOTION_BYPASS", chorusBypassButton);

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
    setLookAndFeel(nullptr);
    chorusBypassButton.removeListener(this);
}

//================================================================
// paint
//================================================================
void DSPTryAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //juce::File bgImageFile = juce::File::getCurrentWorkingDirectory().getChildFile("./UI/faceplate-idea.png");
    //background = juce::ImageCache::getFromFile(bgImageFile);




    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::reverbfaceplate_png, BinaryData::reverbfaceplate_pngSize);
    juce::Image dotActive = juce::ImageCache::getFromMemory(BinaryData::activedot_png, BinaryData::activedot_pngSize);
    juce::Image dotInactive = juce::ImageCache::getFromMemory(BinaryData::inactivedot_png, BinaryData::inactivedot_pngSize);

    g.drawImageAt(background, 0, 0);

    g.setColour(juce::Colours::slategrey);
    g.drawEllipse(295.0, 286.0, 10.0, 10.0, 1.0);

    glow.setGlowProperties(5.0, juce::Colours::red, {293,284});
  

    auto state = chorusBypassButton.getToggleState();

    if (state == true)
    {
        g.drawImageAt(dotInactive, 293, 284);
    }
    if (state == false)
    {
        g.drawImageAt(dotActive, 293, 284);
        glow.applyEffect(dotActive, g, 0.9, 0.2);
    }

}

void DSPTryAudioProcessorEditor::resized()
{

    drySlider.setBounds(57, 123, 110, 110);
    wetSlider.setBounds(157, 20, 110, 110);
    roomSlider.setBounds(332, 20, 110, 110);
    dampSlider.setBounds(434, 123, 110, 110);


    depthSlider.setBounds(129, 258, 84, 84);
    rateSlider.setBounds(385, 258, 84, 84);
    // centreSlider.setBounds(200, 110, 100, 100);
    // feedbackSlider.setBounds(300, 110, 100, 100);
    // mixSlider.setBounds(400, 100, 110, 100);

    // scene.setBounds(210, 172, 186, 114);

   audioProcessor.waveViewer.setBounds(220, 211, 159, 64);
   chorusBypassButton.setBounds(281, 299, 38, 38);
}



void DSPTryAudioProcessorEditor::buttonClicked(juce::Button* button) // [2]
{
    auto state = button->getToggleState();
    if (state == true)
    {
        audioProcessor.processorChain.setBypassed<1>(false);
    }
    else {
        audioProcessor.processorChain.setBypassed<1>(true);
    }
}