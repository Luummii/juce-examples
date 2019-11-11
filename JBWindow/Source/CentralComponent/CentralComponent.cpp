#include "CentralComponent.h"
#include "../../JuceLibraryCode/JuceHeader.h"

#define tr(s) String::fromUTF8(s)

CentralComponent::CentralComponent() : Component("Central Component") {
  pHelloLabel = new Label("Hello Label", tr("Привет, мир!"));
  addAndMakeVisible(pHelloLabel);
  pHelloLabel->setFont(Font(38.0000f, Font::bold));
  // Ориентация текста ярлыка - по центру виджета
  pHelloLabel->setJustificationType(Justification::centred);
  // Запрет на редактирование содержимого ярлыка
  pHelloLabel->setEditable(false, false, false);
  // Синий цвет шрифта
  pHelloLabel->setColour(Label::textColourId, Colours::blue);
  pHelloLabel->setColour(TextEditor::backgroundColourId, Colours::azure);
  pCloseButton = new TextButton("Close Button");
  addAndMakeVisible(pCloseButton);
  pCloseButton->setButtonText(tr("Закрыть"));
  // Устанавливаем в качестве слушателя кнопки
  // сам компонент-контейнер
  pCloseButton->addListener(this);
  setSize(400, 200);
}

CentralComponent::~CentralComponent() {
  // Удаляем дочерние виджеты
  // и обнуляем их указатели
  deleteAndZero(pHelloLabel);
  deleteAndZero(pCloseButton);
}

void CentralComponent::paint(Graphics &g) {
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

  g.setColour(Colours::grey);
  g.drawRect(getLocalBounds(), 1);

  g.setColour(Colours::white);
  g.setFont(14.0f);
  g.drawText("CentralComponent", getLocalBounds(), Justification::centred,
             true);
}

void CentralComponent::resized() {
  pHelloLabel->setBounds(0, 0, proportionOfWidth(1.0000f),
                         proportionOfHeight(0.9000f));
  pCloseButton->setBounds(getWidth() - 20 - 100, getHeight() - 35, 100, 25);
}

void CentralComponent::buttonClicked(Button *pButton) {
  // Если нажата кнопка "Закрыть"...
  if (pButton == pCloseButton) {
    Logger::outputDebugString("Click");
  }
}
