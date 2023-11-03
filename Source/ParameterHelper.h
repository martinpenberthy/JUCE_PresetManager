/*
  ==============================================================================

    ParameterHelper.h
    Created: 8 Aug 2023 3:48:51pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Utility
{
    class ParameterHelper
    {
    public:
        ParameterHelper() = delete;

        static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
        {
            return juce::AudioProcessorValueTreeState::ParameterLayout{
                std::make_unique<juce::AudioParameterFloat>("time", "Time", juce::NormalisableRange<float>{30.f, 3000.f, 0.01f}, 200.f),
                std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", juce::NormalisableRange<float>{0.0f, 0.95f, 0.01f}, 0.3f),
                std::make_unique<juce::AudioParameterFloat>("mix", "Mix", juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f}, 0.5f),
                std::make_unique<juce::AudioParameterChoice>("type", "Delay Type", juce::StringArray{ "Tape", "Digital", "Ping Pong", "Reverse" }, 0),
                std::make_unique<juce::AudioParameterBool>("sync", "Sync To BPM", false)
            };
        }
    };
}
