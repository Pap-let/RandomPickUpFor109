#include "MainComponent.h"
//==============================================================================
MainComponent::MainComponent()
{
    bg = juce::ImageFileFormat::loadFrom(juce::File::getCurrentWorkingDirectory().getChildFile("LocalSrc/bg.png"));
    
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    getLookAndFeel().setColour(juce::TextButton::textColourOffId, juce::Colours::black);

    setSize (1600, 900);
    All_Button.setButtonText(L"\x968F\x673A\x62BD\x53D6"); 
    Select_Button.setButtonText(L"\x9009\x62E9\x6027\x62BD\x53D6"); 
    Back.setButtonText(L"\x8FD4\x56DE");
    All_Button.addListener(this);
    Select_Button.addListener(this);
    Back.addListener(this);

    addAndMakeVisible(All_Button);
    addAndMakeVisible(Select_Button);
    addAndMakeVisible(mainmenu);
    addChildComponent(all);
    addChildComponent(select);
    addChildComponent(buttons);
    addChildComponent(Back);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);
    g.drawImage(bg, juce::Rectangle<float>(0, 0, getWidth(), getHeight()), juce::RectanglePlacement::fillDestination, false);
    All_Button.setBounds(juce::Rectangle<int>(getWidth() * 0.25 - buttonLength / 2, getHeight() * 0.7 - buttonHeight / 2, buttonLength, buttonHeight));
    Select_Button.setBounds(juce::Rectangle<int>(getWidth() * 0.75 - buttonLength / 2, getHeight() * 0.7 - buttonHeight / 2, buttonLength, buttonHeight));
    Back.setBounds(juce::Rectangle<int>(getWidth() * 0.95 - buttonLength/2, getHeight() * 0.95 - buttonHeight/2, buttonLength/2, buttonHeight/2));
}

void MainComponent::resized()
{
    mainmenu.setBounds(0, 0, getWidth(), getHeight() * 0.7);
    all.setBounds(0, 0, getWidth(), getHeight());
    select.setBounds(0, 0, getWidth(), getHeight());
    buttons.setBounds(0, getHeight() * 0.2, getWidth(), getHeight() * 0.8);
    buttonHeight = getHeight() / 8;
    buttonLength = getWidth() / 8;
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &All_Button)
    {
        mode = 1;
        All_Button.setVisible(false);
        Select_Button.setVisible(false);
        mainmenu.setVisible(false);
        all.setVisible(true);
        buttons.setVisible(true);
        buttons.allclicked();
        Back.setVisible(true);
        buttons.open(mode);
    }
    else if (button == &Select_Button)
    {
        mode = 2;
        All_Button.setVisible(false);
        Select_Button.setVisible(false);
        mainmenu.setVisible(false);
        select.setVisible(true);
        buttons.setVisible(true);
        buttons.selectclicked();
        Back.setVisible(true);
        buttons.open(mode);
    }
    else if (button == &Back)
    {
        buttons.close(mode);
        All_Button.setVisible(true);
        Select_Button.setVisible(true);
        mainmenu.setVisible(true);
        all.setVisible(false);
        select.setVisible(false);
        buttons.setVisible(false);
        Back.setVisible(false);
        buttons.cleartable();
        mode = 0;
    }
}

void MainComponent::close()
{
    buttons.close(mode);
}