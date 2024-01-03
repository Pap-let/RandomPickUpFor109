#pragma once

#include <JuceHeader.h>
#include "All.h"
#include "Select.h"
#include "MainMenu.h"
#include "Buttons.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                       public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(juce::Button* button) override;
    void close();

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton All_Button;
    juce::TextButton Select_Button;
    juce::TextButton Back;
    juce::Image Logo;
    juce::Image bg;
    All all;
    Select select;
    MainMenu mainmenu;
    Buttons buttons;
    int buttonLength,buttonHeight;
    int mode=0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
