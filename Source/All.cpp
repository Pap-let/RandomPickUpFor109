/*
  ==============================================================================

    All.cpp
    Created: 18 Nov 2022 11:09:16pm
    Author:  Paplet

  ==============================================================================
*/

#include <JuceHeader.h>
#include "All.h"

//==============================================================================
All::All()
{
    Logo = juce::ImageFileFormat::loadFrom(juce::File::getCurrentWorkingDirectory().getChildFile("LocalSrc/LOGO.jpg"));
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

All::~All()
{
}

void All::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::transparentWhite);
    g.drawImage(Logo, juce::Rectangle<float>(getWidth() * 0.02, 0, getWidth() * 0.05, getHeight() * 0.2), juce::RectanglePlacement::centred, false);
    
    g.setColour(juce::Colours::black);
    g.setFont (getWidth()/30.0);
    g.drawText(L"\x5185\x8499\x53E4\x7164\x7530\x5730\x8D28\x52D8\x67E5\xFF08\x96C6\x56E2\xFF09\x4E00\x96F6\x4E5D\x6709\x9650\x516C\x53F8", juce::Rectangle<float>(getWidth() * 0.05, 0, getWidth() * 0.95, getHeight() * 0.2),juce::Justification::centred, true);
}

void All::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
