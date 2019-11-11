#include "MainWindow.h"
#include "../CentralComponent/CentralComponent.h"

#define tr(s) String::fromUTF8(s)

MainWindow::MainWindow(String name)
    : DocumentWindow(name,
                     Desktop::getInstance().getDefaultLookAndFeel().findColour(
                         ResizableWindow::backgroundColourId),
                     DocumentWindow::allButtons) {
  centreWithSize(getWidth(), getHeight());
  setResizable(true, true);
  setVisible(true);
  /* COM: Если включено, тогда все нижние методы не актуальны */
  // setUsingNativeTitleBar(true);
  setTitleBarTextCentred(false);
  setTitleBarButtonsRequired(allButtons, false);
  LookAndFeel_V3 Look2;
  setLookAndFeel(&Look2);

  /* COM: Динамически создаём ярлык */
  pHelloLabel = new Label("Hello Label", tr("Привет, мир!"));

  /* COM: Задаём размер ярлыка, равный размеру главного окна */
  pHelloLabel->setSize(400, 300);

  /* COM: Устанавливаем размер и гарнитуру шрифта */
  pHelloLabel->setFont(Font(18.0000f, Font::bold));

  /* COM: Устанавливаем выравнивание текста */
  pHelloLabel->setJustificationType(Justification::centred);

  /* COM: Запрещаем редактирование текста ярлыка */
  pHelloLabel->setEditable(false, false, false);

  /* COM: Устанавливаем цвет фона ярлыка */
  pHelloLabel->setColour(Label::backgroundColourId, Colours::lightblue);

  /* COM: Устанавливаем цвет текста надписи */
  pHelloLabel->setColour(Label::textColourId, Colours::black);

  /* COM: Устанавливаем ярлык в качестве компонента содержимого */
  setContentOwned(pHelloLabel, true);

  // Динамически создаём экземпляр класса нашего компонента
  pCentralComponent = new CentralComponent();
  // Устанавливаем его в качестве компонента содержимого
  setContentOwned(pCentralComponent, true);
}

MainWindow::~MainWindow() {}

void MainWindow::closeButtonPressed() {
  JUCEApplication::getInstance()->systemRequestedQuit();
  Logger::outputDebugString("Close");
}
