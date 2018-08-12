#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QTextEdit>

#include "showwidget.h"

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent) {
  imageLabel = new QLabel;
  imageLabel->setScaledContents(true);
  text = new QTextEdit;
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(imageLabel);
  mainLayout->addWidget(text);
}
