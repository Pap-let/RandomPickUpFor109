/*
  ==============================================================================

    MainMenu.h
    Created: 18 Nov 2022 11:29:37pm
    Author:  Paplet

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MainMenu  : public juce::Component
{
public:
    MainMenu();
    ~MainMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenu)
};
