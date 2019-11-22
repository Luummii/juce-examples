#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Utilites.h"

/* SidebarHeader */
struct SidebarHeader : public Component
{
  SidebarHeader()
  {
    label.setText(tr("Examples"), dontSendNotification);
    label.setJustificationType(Justification::centredLeft);
    addAndMakeVisible(label);
  }

  void paint(Graphics &g) override
  {
    g.fillAll(Colours::darkgoldenrod);
  }

  void resized()
  {
    auto bounds = getLocalBounds();
    label.setBounds(bounds);
  }

private:
  Label label;
};

/* SidebarContent */
struct SidebarContent : public Component, public ListBoxModel
{
  SidebarContent()
  {
    setOpaque(true);

    lbEntries.setModel(this);
    lbEntries.setRowHeight(40);
    addAndMakeVisible(lbEntries);
  };
  ~SidebarContent(){};

  int getNumRows() override
  {
    return saEntries.size();
  }

  void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
  {
    if (rowNumber < 0 || rowNumber >= getNumRows())
      return;

    Rectangle<int> array(0, 0, width, height);
    Rectangle<int> bounds(10, 0, width, height);
    auto textColour = findColour(Label::textColourId);
    g.setColour(textColour.withAlpha(0.4f));

    if (rowIsSelected)
    {
      g.setColour(findColour(TextEditor::highlightColourId).withAlpha(0.4f));
      g.fillRect(array);
      g.fillRect(bounds);
      textColour = findColour(TextEditor::highlightedTextColourId);
    }

    g.setColour(textColour);
    g.drawFittedText(saEntries[rowNumber], bounds, Justification::centredLeft, 1);
  }

  void paint(Graphics &g) override
  {
    g.fillAll(Colours::hotpink);
  }

  void resized() override
  {
    lbEntries.setBounds(getLocalBounds());
  }
  void addEntry(const String &entry)
  {
    lbEntries.deselectAllRows();
    saEntries.add(entry);
    lbEntries.updateContent();
  }

private:
  ListBox lbEntries;
  StringArray saEntries;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SidebarContent)
};