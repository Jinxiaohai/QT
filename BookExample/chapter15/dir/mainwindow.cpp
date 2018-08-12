#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  qssFile = new QFile(":/qss/myqss.qss", this);
  qssFile->open(QFile::ReadOnly);
  QString styleSheet = QString(qssFile->readAll());
  qApp->setStyleSheet(styleSheet);
  qssFile->close();

  connect(&myWatcher, &QFileSystemWatcher::directoryChanged, this,
          &MainWindow::showMessage);
  connect(&myWatcher, &QFileSystemWatcher::fileChanged, this,
          &MainWindow::showMessage);
  QDir myDir(QDir::currentPath());
  myDir.setNameFilters(QStringList("*.h"));
  ui->listWidget->addItem(myDir.absolutePath() +
                          tr("files which suffix name is .h: "));
  ui->listWidget->addItems(myDir.entryList());

  myDir.mkdir("mydir");
  myDir.cd("mydir");
  ui->listWidget->addItem(tr("wathc dir is: ") + myDir.absolutePath());
  myWatcher.addPath(myDir.absolutePath());

  QFile file(myDir.absolutePath() + "/file.txt");
  if (file.open(QIODevice::WriteOnly)) {
    QFileInfo info(file);
    ui->listWidget->addItem(tr("watch file is: ") + info.absoluteFilePath());
    myWatcher.addPath(info.absoluteFilePath());
    file.close();
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MainWindow::showMessage(const QString &path) {
  QDir dir(QDir::currentPath() + "/mydir");

  if (path == dir.absolutePath()) {
    ui->listWidget->addItem(dir.dirName() + tr("dir changed: "));
    ui->listWidget->addItems(dir.entryList());
  } else {
    ui->listWidget->addItem(path + tr("file changed!!!!!"));
  }
}
