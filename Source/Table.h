/*
  ==============================================================================

    Table.h
    Created: 22 Nov 2022 4:55:20pm
    Author:  Paplet

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Table  : public juce::Component, public juce::TableListBoxModel,public juce::Timer
{
public:
    Table(int* ptr);
    ~Table() override;
    void resized() override;
    void importdata(juce::Array<juce::File> filenames);
    void exportdata();
    void readRecordData(int);
    void makeRecordData(int);
    int getNumRows() override;
    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    void timerCallback() override;
    //int getColumnAutoSizeWidth(int columnId) override;

    void clearData();
    void start();
    void end();
    void setshow(int x,bool state);
    void reset();

    juce::String Table::IdToName(int x);
    int NameToId(juce::String x);

private:
    juce::TableListBox table{ {}, this };
    
    struct Data
    {
        int id;
        juce::String name;
        juce::String major;
        juce::String level;
        juce::String phonenumber;
        juce::String company;
        int category = 0;
        juce::String operator[](int x)
        {
            switch (x)
            {
            case 1: return juce::String(id);
            case 2: return name;
            case 3: return major;
            case 4: return level;
            case 5: return phonenumber;
            case 6: return company;
            case 7: return juce::String(category);
            default:
                break;
            }
        }

        bool operator ==(const Data& other)
        {
            return this->id == other.id && this->name == other.name && this->major == other.major && this->level == other.level && this->phonenumber == other.phonenumber && this->company == other.company && this->category == other.category;
        }
        bool operator<(const Data& other)
        {
            return id > other.id;
        }
    };
    int num;
    int* numptr = nullptr;
    void ReId(std::vector<Data>& ToReId);
    std::vector<Data> OrgData;
    std::vector<Data> AllData;
    std::vector<Data> DataToPick;
    std::vector<Data> DataToShow;
    std::vector<Data> DataPicked;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Table)
};