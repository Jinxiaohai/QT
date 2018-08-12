#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSessionManager>
#include <QStatusBar>
#include <QTextStream>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  textEdit = new QPlainTextEdit(this);
  this->setCentralWidget(textEdit);

  createActions();
  createStatusBar();

  readSettings();

  connect(textEdit->document(), &QTextDocument::contentsChanged, this,
          &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANGER
  QGuiApplication::setFallbackSessionManagementEnabled(false);
  connect(qApp, &QGuiApplication::commitDataRequest, this,
          &MainWindow::commitData);
#endif

  setCurrentFile(QString());
}

MainWindow::~MainWindow() {}

/// QDir::toNativeSeparators() transfer the separator to native separator
/// \brief read fileName contents and set it as the current file.
void MainWindow::loadFile(const QString &fileName) {
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
        this, tr("Application"),
        tr("Cannot read file %1:\n%2")
            .arg(QDir::toNativeSeparators(fileName), file.errorString()));
    return;
  }

  QTextStream in(&file);
#ifndef QT_NO_CURSOR
  /// Application override cursors are intended for showing the user that the
  /// application is in a special state, for example during an operation that
  /// might take some time.
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
  textEdit->setPlainText(in.readAll());

#ifndef QT_NO_CURSOR
  /// Undoes the last setOverrideCursor().
  QApplication::restoreOverrideCursor();
#endif

  setCurrentFile(fileName);

  /// Hides the normal status indications and displays the given message for the
  /// specified number of milli-seconds (timeout). If timeout is 0 (default),
  /// the message remains displayed until the clearMessage() slot is called or
  /// until the showMessage() slot is called again to change the message.
  statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (maybeSave()) {
    /// save the settings before close the window.
    writeSettings();
    event->accept();
  } else {
    /// 事件是先传递给指定框口部件，确切地说应该是先传递给获得焦点的窗口部件。
    /// 但是如果该部件忽略掉该事件，那么这个事件就会传递给这个部件的父部件。
    /// 重新实现事件处理函数时，一般要调用父类的相应事件处理函数来实现默认的操作。
    event->ignore();
  }
}

void MainWindow::newFile() {
  if (maybeSave()) {
    textEdit->clear();
    setCurrentFile(QString());
  }
}

void MainWindow::open() {
  if (maybeSave()) {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
      loadFile(fileName);
    }
  }
}

bool MainWindow::save() {
  if (curFile.isEmpty()) {
    return saveAs();
  } else {
    return saveFile(curFile);
  }
}

bool MainWindow::saveAs() {
  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if (dialog.exec() != QDialog::Accepted) {
    return false;
  } else {
    return saveFile(dialog.selectedFiles().first());
  }
}

void MainWindow::about() {
  QMessageBox::about(
      this, tr("About Application"),
      tr("The <b>Application</b> example demonstrates how to write modern GUI "
         "application using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::documentWasModified() {
  setWindowModified(textEdit->document()->isModified());
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager) {
  if (manager.allowsInteraction()) {
    if (!maybeSave()) {
      manager.cancel();
    }
  } else {
    if (textEdit->document()->isModified()) {
      save();
    }
  }
}

void MainWindow::createActions() {
  /// fileMenu and fileToolBar
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  QToolBar *fileToolBar = this->addToolBar(tr("File"));
  const QIcon newIcon =
      QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
}
#endif

/// \brief 如果内容未修改或者修改的内容已经保存好了，
///        则返回true，否则返回false.
///
/// @return
///
bool MainWindow::maybeSave() {
  /// textEdit->document() return the QTextDocument
  /// The QTextDocument class holds formatted text.
  /// QTextDocument is a container for structured rich text documents, providing
  /// support for styled text and various types of document elements, such as
  /// lists, tables, frames, and images. They can be created for use in a
  /// QTextEdit, or used independently.
  // Each document element is described by an associated format object. Each
  // format object is treated as a unique object by QTextDocuments, and can be
  // passed to objectForFormat() to obtain the document element that it is
  // applied to.
  /// not modified, return true.
  if (!textEdit->document()->isModified()) {
    return true;
  }

  const QMessageBox::StandardButton ret = QMessageBox::warning(
      this, tr("Application"),
      tr("The document has been modified.\n Do you want to save your changes?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Save:
      return save();
    case QMessageBox::Cancel:
      return false;
    default:
      break;
  }
  /// why return true as the default the value ?????
  return true;
}
