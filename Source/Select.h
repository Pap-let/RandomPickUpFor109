/*
  ==============================================================================

    Select.h
    Created: 18 Nov 2022 11:09:28pm
    Author:  Paplet

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Select  : public juce::Component
{
public:
    Select();
    ~Select() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Image Logo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Select)
};
