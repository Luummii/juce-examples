/*
  ==============================================================================

    RoofComponent.h
    Created: 11 Nov 2019 9:34:10pm
    Author:  luummii

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RoofComponent    : public Component
{
public:
    RoofComponent();
    ~RoofComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoofComponent)
};
