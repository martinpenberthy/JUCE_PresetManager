/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

PresetManagerAudioProcessorEditor::PresetManagerAudioProcessorEditor (PresetManagerAudioProcessor& p) :
    AudioProcessorEditor(&p),
    genericAudioProcessorEditor(p),
    presetPanel(p.getPresetManager()),
    audioProcessor(p)
{
    addAndMakeVisible(genericAudioProcessorEditor);
    addAndMakeVisible(presetPanel);
    
    setResizable(true, true);
    setSize (600, 500);
}

PresetManagerAudioProcessorEditor::~PresetManagerAudioProcessorEditor()
{
}

void PresetManagerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PresetManagerAudioProcessorEditor::resized()
{
    genericAudioProcessorEditor.setBounds(getLocalBounds()
        .withSizeKeepingCentre(getLocalBounds().proportionOfWidth(0.9f), getLocalBounds().proportionOfHeight(0.5f)));
    
    presetPanel.setBounds(getLocalBounds().removeFromTop(proportionOfHeight(0.1f)));
}
