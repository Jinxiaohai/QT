#include <QSplitter>
#include <QTextEdit>

#include "splitter.h"

Splitter::Splitter(QWidget *parent) : QWidget(parent) {
  QSplitter *splitterMain = new QSplitter(Qt::Horizontal, this);

  QTextEdit *textLeft = new QTextEdit(tr("left widget"), splitterMain);
  textLeft->setAlignment(Qt::AlignCenter);

  QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
  splitterRight->setOpaqueResize(false);

  QTextEdit *textUp = new QTextEdit(tr("right up"), splitterRight);
  textUp->setAlignment(Qt::AlignCenter);
  QTextEdit *textBottom = new QTextEdit(tr("right bottom"), splitterRight);
  textBottom->setAlignment(Qt::AlignCenter);

  splitterMain->setStretchFactor(1, 1);
  resize(600, 400);
  setWindowTitle(tr("QSplitter..."));
}

Splitter::~Splitter() {}
