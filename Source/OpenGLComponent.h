/*
  ==============================================================================

    OpenGLComponent.h
    Created: 10 Feb 2023 7:20:10am
    Author:  james

  ==============================================================================
*/

#pragma once
#include "PluginEditor.h"
#include "PluginProcessor.h"

SceneComponent::SceneComponent() {}

SceneComponent::~SceneComponent() {}

void SceneComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
    g.drawFittedText("Reverb", getLocalBounds(), juce::Justification::centred, 1);
}

void SceneComponent::resized()
{

}