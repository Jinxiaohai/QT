#include <QAction>
#include <QFileDialog>
#include <QWidget>

#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent) {
  action = new QAction(this);
  action->setCheckable(true);
  connect(action, SIGNAL(triggered()), this, SLOT(show()));
  connect(action, SIGNAL(triggered()), this, SLOT(setFocus()));

  isUntitled = true;

  connect(document(), SIGNAL(contentsChanged()), this,
          SLOT(documentWasModified()));
  setWindowIcon(QPixmap(":/images/document.png"));
  setWindowTitle(tr("[*]"));
  setAttribute(Qt::WA_DeleteOnClose);
}

void Editor::newFile() {
  static int documentNumber = 1;
  curFile = tr("document%1.txt").arg(documentNumber);
  setWindowTitle(curFile + "[*]");
  action->setText(curFile);
  isUntitled = true;
  ++documentNumber;
}

bool Editor::save() {
  if (isUntitled) {
    return saveAs();
  } else {
    return saveFile(curFile);
  }
}

bool Editor::saveAs() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);
  if (fileName.isEmpty()) {
    return false;
  } else {
    saveFile(fileName);
  }
}

QSize Editor::sizeHint() const {
  return QSize(72 * fontMetrics().width('x'), 25 * fontMetrics().lineSpacing());
}

Editor *Editor::open(QWidget *parent) {
  QString fileName = QFileDialog::getOpenFileName(parent, tr("Open"), ".");
  if (fileName.isEmpty()) {
    return 0;
  }
  return openFile(fileName, parent);
}
