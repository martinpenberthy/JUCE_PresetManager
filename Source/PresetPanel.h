/*
  ==============================================================================

    PresetPanel.h
    Created: 8 Aug 2023 4:05:58pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

namespace Gui
{
    class PresetPanel : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
    {
    public:
        PresetPanel(Service::PresetManager& pm) : presetManager(pm){
            configureButton(saveButton, "Save");
            configureButton(deleteButton, "Delete");
            configureButton(previousPresetButton, "<");
            configureButton(nextPresetButton, ">");

            presetList.setTextWhenNothingSelected("No Preset Selected");
            presetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
            addAndMakeVisible(presetList);
            presetList.addListener(this);

            loadPresetList();
        }
        
        ~PresetPanel(){
            saveButton.removeListener(this);
            deleteButton.removeListener(this);
            nextPresetButton.removeListener(this);
            previousPresetButton.removeListener(this);
            
            presetList.removeListener(this);
        }
        
        void resized() override
        {
            const auto container = getLocalBounds().reduced(4);
            auto bounds = container;
            saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(4));
            previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
            presetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).reduced(4));
            nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
            deleteButton.setBounds(bounds.reduced(4));
        }
        
    private:
        void buttonClicked(juce::Button* button) override
        {
            if(button == &saveButton)
            {
                fileChooser = std::make_unique<juce::FileChooser>(
                    "Please enter the name of the preset to save",
                    Service::PresetManager::defaultDirectory,
                    "*." + Service::PresetManager::extension
                );
                
                fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser & chooser)
                {
                    const auto resultFile = chooser.getResult();
                    presetManager.savePreset(resultFile.getFileNameWithoutExtension());
                    loadPresetList();
                });
            }
            
            if(button == &previousPresetButton)
            {
                const auto index = presetManager.loadPreviousPreset();
                presetList.setSelectedItemIndex(index, juce::dontSendNotification);
            }
            
            if(button == &nextPresetButton)
            {
                const auto index = presetManager.loadNextPreset();
                presetList.setSelectedItemIndex(index, juce::dontSendNotification);
            }

            if(button == &deleteButton)
            {
                presetManager.deletePreset(presetManager.getCurrentPreset());
                loadPresetList();
            }
        }
        void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override
        {
            if(comboBoxThatHasChanged == &presetList)
                presetManager.loadPreset(presetList.getItemText(presetList.getSelectedItemIndex()));
        }
        
        void configureButton(juce::Button& button, const juce::String& buttonText)
        {
            button.setButtonText(buttonText);
            button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
            addAndMakeVisible(button);
            button.addListener(this);
        }
        
        void loadPresetList()
        {
            presetList.clear(juce::dontSendNotification);
            const auto allPresets = presetManager.getAllPresets();
            const auto currentPreset = presetManager.getCurrentPreset();
            presetList.addItemList(allPresets, 1);
            presetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), juce::dontSendNotification);

        }
        
        Service::PresetManager& presetManager;
        juce::TextButton saveButton, deleteButton, previousPresetButton, nextPresetButton;
        juce::ComboBox presetList;
        std::unique_ptr<juce::FileChooser> fileChooser;
        
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetPanel);

    };

}
