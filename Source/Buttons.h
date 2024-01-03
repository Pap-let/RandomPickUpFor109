/*
  ==============================================================================

    Buttons.h
    Created: 22 Nov 2022 4:33:11pm
    Author:  Paplet

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Table.h"
//==============================================================================
/*
*/

class Buttons  : public juce::Component,
                 public juce::Button::Listener
{
public:
    Buttons();
    ~Buttons() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void allclicked();
    void selectclicked();
    void cleartable();
    void open(int mode);
    void close(int mode);
private:
    juce::TextButton Reset;
    juce::TextButton SetNum;
    juce::TextButton Start;
    juce::TextButton End;
    juce::TextButton Import;
    juce::TextButton Export;

    juce::TextButton GongCheng;
    juce::TextButton HuoWu;
    juce::TextButton FuWu;
    juce::TextButton DiZhiKuangChan;
    juce::TextButton ShuiGongHuan;
    juce::TextButton CeHui;
    juce::TextButton WuHuaTan;
    juce::TextButton ZuanTan;
    juce::TextButton JianCe;
    juce::TextButton JingJi;
    juce::TextButton ShiZhengGongCheng;
    juce::TextButton QiTa;

    std::vector<juce::TextButton*> buttons;
    int Num = 0;
    int buttonWidth;
    int buttonHeight;
    Table table{&Num};
    juce::FileChooser fileChooser{ L"\x9009\x62E9\x4E00\x4E2A\x8868\x683C", juce::File::getCurrentWorkingDirectory(),"*.xlsx,*.xls"};
    juce::FileChooser fileExport{ L"\x9009\x62E9\x5BFC\x51FA\x4F4D\x7F6E",juce::File::getCurrentWorkingDirectory(),"*"};
    class NumsetWindow :public juce::DialogWindow
    {
    public:
        NumsetWindow(juce::String name,int* numptr) :juce::DialogWindow(name, juce::Colours::white, juce::DialogWindow::allButtons)
        {
            setResizable(false, false);
            centreWithSize(300, 200);
            Component::addAndMakeVisible(&text);
            Component::addAndMakeVisible(&confirm);
            confirm.setButtonText(L"\x786E\x8BA4");
            confirm.onClick = [this] {confirmButtonPressed(); };
            text.setEditable(true);
            text.setText("", juce::NotificationType::dontSendNotification);
            text.setColour(juce::Label::textColourId, juce::Colours::black);
            text.setColour(juce::Label::textWhenEditingColourId, juce::Colours::grey);
            text.setColour(juce::Label::outlineColourId, juce::Colours::black);
            text.setBounds(100, 50, 100, 25);
            confirm.setBounds(125, 100, 50, 25);
            num = numptr;
        }
        void closeButtonPressed() override
        {
            setVisible(false);
        }
        void confirmButtonPressed()
        {
            *num = text.getText().getIntValue();
            setVisible(false);
        }
    private:
        int* num = nullptr;
        juce::Label text;
        juce::TextButton confirm;
    };
    NumsetWindow numsetWindow{ L"\x8BF7\x8F93\x5165\x4EBA\x6570" ,&Num };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Buttons)
};

