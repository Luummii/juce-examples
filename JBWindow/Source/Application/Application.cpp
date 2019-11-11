#include "Application.h"
#include "../MainWindow/MainWindow.h"

Application::Application() {}
Application::~Application() {}

void Application::initialise(const String &commandLine) {
  mainWindow.reset(new MainWindow(getApplicationName()));
}

void Application::shutdown() {}

void Application::systemRequestedQuit() { quit(); }

const String Application::getApplicationName() {
  return ProjectInfo::projectName;
}

const String Application::getApplicationVersion() {
  return ProjectInfo::versionString;
}

/* COM: Запрещаем запуск более одного экземпляра приложения */
bool Application::moreThanOneInstanceAllowed() { return false; }

/* COM: Когда происходит запуск другого экземпляря приложения */
void Application::anotherInstanceStarted(const String &commandLine) {}
