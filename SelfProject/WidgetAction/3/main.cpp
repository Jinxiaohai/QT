#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget *window = new QWidget;

  QSpinBox *spinBox = new QSpinBox;
  spinBox->setRange(0, 130);
  spinBox->setValue(28);
  QSlider *slider = new QSlider(Qt::Horizontal);
  slider->setRange(0, 130);
  slider->setValue(28);

  QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider,
                   SLOT(setValue(int)));
  QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox,
                   SLOT(setValue(int)));

  QHBoxLayout *hLayout = new QHBoxLayout;
  hLayout->addWidget(spinBox);
  hLayout->addWidget(slider);

  window->resize(300, 20);
  window->setWindowTitle("xiaohai project");
  window->setLayout(hLayout);
  window->show();
  return a.exec();
}
