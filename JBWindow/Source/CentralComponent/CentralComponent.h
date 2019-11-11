#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class CentralComponent : public Component,
                         public Button::Listener {
public:
  CentralComponent();
  ~CentralComponent();

  void paint(Graphics &) override;
  void resized() override;

  void buttonClicked(Button *);

private:
  Label *pHelloLabel;
  TextButton *pCloseButton;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CentralComponent)
};
