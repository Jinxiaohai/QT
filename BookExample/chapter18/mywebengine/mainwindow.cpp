#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  view = new QWebEngineView(this);
  view->load(QUrl("http://www.jinxiaohai.cn"));
  setCentralWidget(view);
  resize(1020, 680);

  progress = 0;
  connect(view, &QWebEngineView::loadProgress, this, &MainWindow::setProgress);
  connect(view, &QWebEngineView::titleChanged, this, &MainWindow::adjustTitle);
  connect(view, &QWebEngineView::loadFinished, this,
          &MainWindow::finishLoading);

  locationEdit = new QLineEdit(this);
  locationEdit->setText("http://www.qter.org");
  connect(locationEdit, &QLineEdit::returnPressed, this,
          &MainWindow::changeLocation);

  ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Back));
  ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Forward));
  ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Reload));
  ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Stop));
  ui->mainToolBar->addWidget(locationEdit);
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

void MainWindow::changeLocation() {
  QUrl url = QUrl(locationEdit->text());
  view->load(url);
  view->setFocus();
}

void MainWindow::setProgress(int p) {
  progress = p;
  adjustTitle();
}

void MainWindow::adjustTitle() {
  if (progress <= 0 || progress >= 100) {
    setWindowTitle(view->title());
  } else {
    setWindowTitle(QString("%1 ( %2 )").arg(view->title()).arg(progress));
  }
}

void MainWindow::finishLoading(bool finished) {
  if (finished) {
    progress = 100;
    setWindowTitle(view->title());
  } else {
    setWindowTitle("Web page loading error.");
  }
}
