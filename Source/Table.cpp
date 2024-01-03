/*
  ==============================================================================

    Table.cpp
    Created: 22 Nov 2022 4:55:20pm
    Author:  Paplet

  ==============================================================================
*/

#include <JuceHeader.h>
#include <direct.h>
#include "Table.h"
#include "OpenXLSX.Library/include/OpenXLSX/OpenXLSX.hpp"
#pragma comment( lib, "OpenXLSX.lib" )

//==============================================================================
Table::Table(int* ptr)
{
    numptr = ptr;
    addAndMakeVisible(table);
    table.getHeader().addColumn(L"\x5E8F\x53F7", 1, 10);                    //ÐòºÅ
    table.getHeader().addColumn(L"\x59D3\x540D", 2, 10);                    //ÐÕÃû
    table.getHeader().addColumn(L"\x4E13\x4E1A", 3, 10);                    //×¨Òµ
    table.getHeader().addColumn(L"\x804C\x79F0\x7B49\x7EA7", 4, 10);        //Ö°³ÆµÈ¼¶
    table.getHeader().addColumn(L"\x7535\x8BDD", 5, 10);                    //µç»°
    table.getHeader().addColumn(L"\x5355\x4F4D", 6, 10);                    //µ¥Î»

    table.setColour(juce::ListBox::outlineColourId, juce::Colours::black);
    table.setColour(juce::ListBox::backgroundColourId, juce::Colours::white);
    table.setOutlineThickness(1);
    table.getHeader().setSortColumnId(1, true);
    table.setMultipleSelectionEnabled(true);
    resized();
}

Table::~Table()
{

}

void Table::importdata(juce::Array<juce::File> filenames)
{
    for (auto filename : filenames)
    {
        OpenXLSX::XLDocument doc;
        doc.open(filename.getFullPathName().toStdString());
        auto wks = doc.workbook().worksheet(doc.workbook().worksheetNames()[0]);
        int cate = NameToId(filename.getFileNameWithoutExtension()),maxrows=wks.rowCount();
        if (cate != -1)
        {
            std::vector<OpenXLSX::XLCellValue> readValues;
            for (int i = 2; i <= maxrows; i++)
            {
                bool flag = true;
                for (int j = 1; j <= 6; j++)
                {
                    if (wks.cell(i, j).value().type() == OpenXLSX::XLValueType::Empty)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    int id = wks.cell(i, 1).value();
                    std::string name = wks.cell(i, 2).value();
                    std::string major = wks.cell(i, 3).value();
                    std::string level = wks.cell(i, 4).value();
                    std::string phonenumber;
                    OpenXLSX::XLCellValue pcell = wks.cell(i, 5).value();
                    if (pcell.type() == OpenXLSX::XLValueType::String) phonenumber = pcell.get<std::string>();
                    else if(pcell.type()==OpenXLSX::XLValueType::Integer) phonenumber = juce::String(long long(pcell)).toStdString();
                    else if(pcell.type() == OpenXLSX::XLValueType::Float) phonenumber = juce::String(float(pcell)).toStdString();
                    std::string company = wks.cell(i, 6).value();
                    OrgData.push_back({ id,name,major,level,phonenumber,company,cate });
                    
                }
            }
        }
        doc.close();
    }
    ReId(OrgData);
    AllData = OrgData;
    for (auto tmp : DataPicked) AllData.erase(std::find(AllData.begin(), AllData.end(), tmp));
}

void Table:: exportdata()
{
    OpenXLSX::XLDocument doc;
    doc.create("./Result.xlsx");
    auto wks = doc.workbook().worksheet("Sheet1");
    wks.cell("A1").value() = juce::String{ L"\x5E8F\x53F7" }.toStdString();
    wks.cell("B1").value() = juce::String{ L"\x59D3\x540D" }.toStdString();
    wks.cell("C1").value() = juce::String{ L"\x4E13\x4E1A" }.toStdString();
    wks.cell("D1").value() = juce::String{ L"\x804C\x79F0\x7B49\x7EA7" }.toStdString();
    wks.cell("E1").value() = juce::String{ L"\x7535\x8BDD" }.toStdString();
    wks.cell("F1").value() = juce::String{ L"\x5355\x4F4D" }.toStdString();
    wks.cell("G1").value() = juce::String{ L"\x7C7B\x522B" }.toStdString();
    for (int i=1;i<=DataToShow.size();i++)
    {
        wks.cell(i + 1, 1).value() = DataToShow[i - 1].id;
        for (int j = 2; j <= 6; j++)
        {
            wks.cell(i + 1, j).value() = DataToShow[i - 1][j].toStdString();
        }
        wks.cell(i + 1, 7).value() = IdToName(DataToShow[i - 1].category).toStdString();
    }
    doc.save();
    doc.close();

    for (auto data : DataToShow)
    {
        DataPicked.push_back(data);
        auto it = find(AllData.begin(), AllData.end(), data);
        if (it != AllData.end())
            AllData.erase(it);
    }
}

void Table::resized()
{
    table.setBounds(juce::Rectangle<int>(0,0,getWidth()*0.9,getHeight()));
    table.getHeader().setColumnWidth(1, getWidth() * 0.9 * 0.1 > 0 ? getWidth() * 0.9 * 0.1 : 1);
    table.getHeader().setColumnWidth(2, getWidth() * 0.9 * 0.1 > 0 ? getWidth() * 0.9 * 0.1 : 1);
    table.getHeader().setColumnWidth(3, getWidth() * 0.9 * 0.1 > 0 ? getWidth() * 0.9 * 0.1 : 1);
    table.getHeader().setColumnWidth(4, getWidth() * 0.9 * 0.2 > 0 ? getWidth() * 0.9 * 0.2 : 1);
    table.getHeader().setColumnWidth(5, getWidth() * 0.9 * 0.2 > 0 ? getWidth() * 0.9 * 0.2 : 1);
    table.getHeader().setColumnWidth(6, getWidth() * 0.9 * 0.3 > 0 ? getWidth() * 0.9 * 0.3 : 1);
}

int Table::getNumRows()
{
    return DataToShow.size();
}

void Table::paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected)
{
    auto alternateColour = juce::Colours::lightgrey;
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void Table::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(rowIsSelected ? juce::Colours::darkblue : juce::Colours::black);
    g.setFont(20.0f);

    g.drawText(DataToShow[rowNumber][columnId], 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    
    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

void Table::timerCallback()
{
    DataToShow.clear();
    std::vector<Data> tmp = DataToPick;
    juce::Random rand;
    for (int i = 0; i < num; i++)
    {
        int idx = rand.nextInt() % tmp.size();
        DataToShow.push_back(tmp[idx]);
        tmp.erase(tmp.begin() + idx);
    }
    setSize(getWidth() - 1, getHeight());
    setSize(getWidth() + 1, getHeight());
}

void Table::clearData()
{
    OrgData.clear();
    AllData.clear();
    DataToPick.clear();
    DataToShow.clear();
    DataPicked.clear();
    setSize(getWidth() - 1, getHeight());
    setSize(getWidth() + 1, getHeight());
}

void Table::start()
{
    if (*numptr == 0) num = DataToPick.size();
    else num = *numptr > DataToPick.size() ? DataToPick.size() : *numptr;
    startTimer(100);
}

void Table::end()
{
    stopTimer();
}

void Table::setshow(int x,bool state)
{
    if (state)
    {
        for (auto data : AllData)
        {
            if (data.category == x)
                DataToPick.push_back(data);
        }
    }
    else
    {
        int i = 0;
        while (i<DataToPick.size())
        {
            if (DataToPick[i].category == x)
            {
                DataToPick.erase(DataToPick.begin()+i);
            }
            else i++;
        }
    }
    DataToShow = DataToPick;
    setSize(getWidth() - 1, getHeight());
    setSize(getWidth() + 1, getHeight());
}

juce::String Table::IdToName(int x)
{
    switch (x)
    {
    case 0: return L"\x5DE5\x7A0B\x7C7B";
    case 1: return L"\x8D27\x7269\x7C7B";
    case 2: return L"\x670D\x52A1\x7C7B";
    case 3: return L"\x5730\x8D28\x77FF\x4EA7\x7C7B";
    case 4: return L"\x6C34\x5DE5\x73AF\x7C7B";
    case 5: return L"\x6D4B\x7ED8\x5DE5\x7A0B\x7C7B";
    case 6: return L"\x7269\x5316\x63A2\x7C7B";
    case 7: return L"\x94BB\x63A2\x5DE5\x7A0B\x7C7B";
    case 8: return L"\x7ECF\x6D4E\x7C7B";
    case 9: return L"\x5E02\x653F\x5DE5\x7A0B\x7C7B";
    case 10: return L"\x68C0\x6D4B\x7C7B";
    case 11: return L"\x5176\x4ED6\x7C7B";
    default: return L"";
    }
}

int Table::NameToId(juce::String x)
{
    if (x == L"\x5DE5\x7A0B\x7C7B") return 0;
    else if (x == L"\x8D27\x7269\x7C7B") return 1;
    else if (x == L"\x670D\x52A1\x7C7B") return 2;
    else if (x == L"\x5730\x8D28\x77FF\x4EA7\x7C7B") return 3;
    else if (x == L"\x6C34\x5DE5\x73AF\x7C7B") return 4;
    else if (x == L"\x6D4B\x7ED8\x5DE5\x7A0B\x7C7B") return 5;
    else if (x == L"\x7269\x5316\x63A2\x7C7B") return 6;
    else if (x == L"\x94BB\x63A2\x5DE5\x7A0B\x7C7B") return 7;
    else if (x == L"\x7ECF\x6D4E\x7C7B") return 8;
    else if (x == L"\x5E02\x653F\x5DE5\x7A0B\x7C7B") return 9;
    else if (x == L"\x68C0\x6D4B\x7C7B") return 10;
    else if (x == L"\x5176\x4ED6\x7C7B") return 11;
    else return -1;
}

void Table::ReId(std::vector<Data>& ToReId)
{
    for (int i = 0; i < ToReId.size(); i++)
    {
        ToReId[i].id = i+1;
    }
}

void Table::reset()
{
    DataToPick.clear();
    DataToShow.clear();
    setSize(getWidth() - 1, getHeight());
    setSize(getWidth() + 1, getHeight());
}

void Table::readRecordData(int mode)
{
    juce::File path;
    if (mode == 1) path = juce::File::getCurrentWorkingDirectory().getChildFile("data\\all");
    else if (mode == 2) path = juce::File::getCurrentWorkingDirectory().getChildFile("data\\select");
    if (path.exists())
    {
        auto fin = path.createInputStream();
        while (!fin->isExhausted())
        {
            Data tmpdata;
            tmpdata.id = fin->readNextLine().getIntValue();
            tmpdata.name = fin->readNextLine();
            tmpdata.major = fin->readNextLine();
            tmpdata.level = fin->readNextLine();
            tmpdata.phonenumber = fin->readNextLine();
            tmpdata.company = fin->readNextLine();
            tmpdata.category = fin->readNextLine().getIntValue();
            OrgData.push_back(tmpdata);
        }
    }
    AllData = OrgData;
}

void Table::makeRecordData(int mode)
{
    juce::File path;
    if (mode == 1) path = juce::File::getCurrentWorkingDirectory().getChildFile("data\\all");
    else if (mode == 2) path = juce::File::getCurrentWorkingDirectory().getChildFile("data\\select");
    if (path.exists()) path.deleteFile();
    path.create();
    auto of = path.createOutputStream();

    for (int i = 1; i <= OrgData.size(); i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            *of << OrgData[i - 1][j] << "\n";
        }
    }
}