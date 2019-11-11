#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class Application : public JUCEApplication {
  public:
    Application();
    ~Application();

    const String getApplicationName() override;
    const String getApplicationVersion() override;
    bool moreThanOneInstanceAllowed() override;

    void initialise(const String &commandLine) override;
    void anotherInstanceStarted(const String &commandLine) override;
    void shutdown() override;
    void systemRequestedQuit() override;

  private:
    std::unique_ptr<class MainWindow> mainWindow;
};
