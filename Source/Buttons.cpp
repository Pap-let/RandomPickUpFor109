/*
  ==============================================================================

    Buttons.cpp
    Created: 22 Nov 2022 4:33:11pm
    Author:  Paplet

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Buttons.h"

//==============================================================================
Buttons::Buttons()
{
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    getLookAndFeel().setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    addAndMakeVisible(table);

    Reset.setButtonText(L"\x91CD\x7F6E");
    SetNum.setButtonText(L"\x4EBA\x6570");
    Start.setButtonText(L"\x5F00\x59CB");
    End.setButtonText(L"\x7ED3\x675F");
    Import.setButtonText(L"\x5BFC\x5165");
    Export.setButtonText(L"\x5BFC\x51FA");
    Start.setEnabled(true);
    End.setEnabled(false);
    Reset.addListener(this);
    SetNum.addListener(this);
    Start.addListener(this);
    End.addListener(this);
    Import.addListener(this);
    Export.addListener(this);
    addAndMakeVisible(Reset);
    addAndMakeVisible(SetNum);
    addAndMakeVisible(Start);
    addAndMakeVisible(End);
    addAndMakeVisible(Import);
    addAndMakeVisible(Export);

    GongCheng.setButtonText(L"\x5DE5\x7A0B\x7C7B");
    HuoWu.setButtonText(L"\x8D27\x7269\x7C7B");
    FuWu.setButtonText(L"\x670D\x52A1\x7C7B");
    DiZhiKuangChan.setButtonText(L"\x5730\x8D28\x77FF\x4EA7\x7C7B");
    ShuiGongHuan.setButtonText(L"\x6C34\x5DE5\x73AF\x7C7B");
    CeHui.setButtonText(L"\x6D4B\x7ED8\x5DE5\x7A0B\x7C7B");
    WuHuaTan.setButtonText(L"\x7269\x5316\x63A2\x7C7B");
    ZuanTan.setButtonText(L"\x94BB\x63A2\x5DE5\x7A0B\x7C7B");
    JingJi.setButtonText(L"\x7ECF\x6D4E\x7C7B");
    ShiZhengGongCheng.setButtonText(L"\x5E02\x653F\x5DE5\x7A0B\x7C7B");
    JianCe.setButtonText(L"\x68C0\x6D4B\x7C7B");
    QiTa.setButtonText(L"\x5176\x4ED6\x7C7B");

    buttons.push_back(&GongCheng);
    buttons.push_back(&HuoWu);
    buttons.push_back(&FuWu);
    buttons.push_back(&DiZhiKuangChan);
    buttons.push_back(&ShuiGongHuan);
    buttons.push_back(&CeHui);
    buttons.push_back(&WuHuaTan);
    buttons.push_back(&ZuanTan);
    buttons.push_back(&JingJi);
    buttons.push_back(&ShiZhengGongCheng);
    buttons.push_back(&JianCe);
    buttons.push_back(&QiTa);
    for (auto button : buttons)
    {
        button->setToggleable(true);
        button->setClickingTogglesState(true);
        button->addListener(this);
        addChildComponent(button);
    }
}

Buttons::~Buttons()
{
}

void Buttons::buttonClicked(juce::Button* button)
{
    if (button == &Reset)
    {
        for (auto button : buttons)
        {
            if (button->getToggleState())
                button->setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        table.reset();
    }
    else if (button == &SetNum)
    {
        numsetWindow.setVisible(true);
    }
    else if (button == &Start)
    {
        for (auto button : buttons)
        {
            button->setEnabled(false);
        }
        Start.setEnabled(false);
        End.setEnabled(true);
        table.start();
    }
    else if (button == &End)
    {
        for (auto button : buttons)
        {
            button->setEnabled(true);
        }
        Start.setEnabled(true);
        End.setEnabled(false);
        table.end();
    }
    else if (button == &Import)
    {
        for (auto button : buttons)
        {
            if (button->getToggleState())
                button->setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        const auto callbackimport = [this](const juce::FileChooser& chooser)
        {
            table.importdata(chooser.getResults());
        };
        fileChooser.launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,callbackimport);
    }
    else if (button == &Export)
    {
        table.exportdata();
    }
    else if (std::find(buttons.begin(), buttons.end(), button) != buttons.end())
    {
        table.setshow(std::find(buttons.begin(), buttons.end(), button) - buttons.begin(),button->getToggleState());
    }
}

void Buttons::paint (juce::Graphics& g)
{

}

void Buttons::resized()
{
    buttonWidth = getWidth() / 20;
    buttonHeight = getHeight() / 20;
    int controlwidth = getWidth() * 0.75,controlheight= getHeight() * 0.6,d=getHeight()*0.02;
    table.setBounds(juce::Rectangle<int>(getWidth() * 0.05, 0, getWidth(), getHeight() * 0.5));
    Reset.setBounds(juce::Rectangle<int>(controlwidth, controlheight, buttonWidth, buttonHeight));
    SetNum.setBounds(juce::Rectangle<int>(controlwidth + buttonWidth + d, controlheight, buttonWidth, buttonHeight));
    Start.setBounds(juce::Rectangle<int>(controlwidth, controlheight + buttonHeight + d, buttonWidth, buttonHeight));
    End.setBounds(juce::Rectangle<int>(controlwidth + buttonWidth + d, controlheight + buttonHeight + d, buttonWidth, buttonHeight));
    Import.setBounds(juce::Rectangle<int>(controlwidth, controlheight + 2 * (buttonHeight + d), buttonWidth, buttonHeight));
    Export.setBounds(juce::Rectangle<int>(controlwidth + buttonWidth + d, controlheight + 2 * (buttonHeight + d), buttonWidth, buttonHeight));

    buttonWidth = getWidth() / 15;
    buttonHeight = getHeight() / 15;
    int xbegin = getWidth() * 0.22, ybegin = getHeight() * 0.55, dx = buttonWidth + d, dy = buttonHeight + d;
    for (int i=0;i<3;i++)
    {
        buttons[i]->setBounds(xbegin + dx * (i % 3), ybegin + dy * (i / 3 + 1), buttonWidth, buttonHeight);
    }
    for (int i = 3; i < buttons.size(); i++)
    {
        buttons[i]->setBounds(xbegin + dx * (i % 3), ybegin + dy * (i / 3 - 1), buttonWidth, buttonHeight);
    }
}
void Buttons::allclicked()
{
    for (int i = 0; i < 3; i++) buttons[i]->setVisible(true);
    for (int i = 3; i < buttons.size(); i++) buttons[i]->setVisible(false);
}

void Buttons::selectclicked()
{
    for (int i = 0; i < 3; i++) buttons[i]->setVisible(false);
    for (int i = 3; i < buttons.size(); i++) buttons[i]->setVisible(true);
}

void Buttons::cleartable()
{
    for (int i = 0; i < buttons.size(); i++) buttons[i]->setToggleState(false, juce::dontSendNotification);
    table.clearData();
}

void Buttons::open(int mode)
{
    table.readRecordData(mode);
}

void Buttons::close(int mode)
{
    table.makeRecordData(mode);
}