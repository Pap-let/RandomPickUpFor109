/*
  ==============================================================================

    MainMenu.cpp
    Created: 18 Nov 2022 11:29:37pm
    Author:  Paplet

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainMenu.h"

//==============================================================================
MainMenu::MainMenu()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MainMenu::~MainMenu()
{
}

void MainMenu::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::transparentWhite);

    g.setFont(juce::Font(getWidth()/30.0));
    g.setColour(juce::Colours::black);

    g.drawText(L"\x5185\x8499\x53E4\x7164\x7530\x5730\x8D28\x52D8\x67E5\xFF08\x96C6\x56E2\xFF09\x4E00\x96F6\x4E5D\x6709\x9650\x516C\x53F8", juce::Rectangle<float>(0, 0, getWidth() * 1.0, getHeight() * 0.42), juce::Justification::centredBottom, true);
    //g.drawText(L"\x4E13\x4E1A\x6280\x672F\x8BC4\x5BA1\x4E13\x5BB6\x7EC4", juce::Rectangle<float>(0, getHeight() * 0.5, getWidth() * 1.0, getHeight() * 0.5), juce::Justification::centredTop, true);
}

void MainMenu::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
