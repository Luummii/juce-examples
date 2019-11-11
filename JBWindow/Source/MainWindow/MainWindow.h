#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class CentralComponent;

class MainWindow : public DocumentWindow {
public:
  MainWindow(String name);
  ~MainWindow();

  void closeButtonPressed() override;

private:
  Label *pHelloLabel;
  CentralComponent *pCentralComponent;
};