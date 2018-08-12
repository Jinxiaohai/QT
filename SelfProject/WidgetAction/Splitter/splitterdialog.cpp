#include <QHBoxLayout>
#include <QSplitter>
#include <QTextEdit>

#include "splitterdialog.h"

SplitterDialog::SplitterDialog(QWidget *parent) : QDialog(parent) {
  QTextEdit *editor1 = new QTextEdit;  /// the parent is splitter
  editor1->setPlainText(
      "Mon enfant, ma soeur,\n"
      "Songe  la douceur\n"
      "D'aller l-bas vivre ensemble,\n"
      "Aimer  loisir,\n"
      "Aimer et mourir\n"
      "Au pays qui te ressemble.");

  QTextEdit *editor2 = new QTextEdit;  /// the parent is splitter
  editor2->setPlainText(
      "My child, my sister,\n"
      "think of the sweetness\n"
      "of going there to live together!\n"
      "To love at leisure,\n"
      "to love and to die\n"
      "in a country that is the image of you!");

  QTextEdit *editor3 = new QTextEdit;  /// the parent is splitter
  editor3->setPlainText(
      "Mein Kind, meine Schwester,\n"
      "denke an den Traum\n"
      "dort hin(unter) zu gehen um zusammen\n"
      "zu leben und in aller Ruhe zu lieben,\n"
      "Zu lieben und zu sterben\n"
      "in dem Land, das dir gleicht.");

  splitter = new QSplitter(Qt::Horizontal);
  splitter->addWidget(editor1);
  splitter->addWidget(editor2);
  splitter->addWidget(editor3);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(splitter);
  mainLayout->setMargin(0);

  this->setLayout(mainLayout);
}

SplitterDialog::~SplitterDialog() {}
