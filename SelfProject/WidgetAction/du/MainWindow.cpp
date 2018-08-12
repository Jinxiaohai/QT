#include <QChartView>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPair>
#include <QPieSeries>
#include <QPieSlice>
#include <QProgressDialog>
#include <QPushButton>
#include <QTextStream>
#include <QVector>

#include "MainWindow.h"
#include "QssStyle.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  QssStyle::setStyle(":/qss.qss");
  this->errorMessage = tr(" ");

  pathLabel = new QLabel(tr("路径:"));
  pathLineEdit = new QLineEdit;
  pathLineEdit->setToolTip("请输入一个绝对路径，例如:/home");

  userNameLabel = new QLabel(tr("用户名:"));
  userNameLineEdit = new QLineEdit;
  userNameLineEdit->setToolTip("请输入用户名，多个用户之间用空格进行分隔。");

  centralWidget = new QWidget();
  chartView = new QChartView;
  QHBoxLayout *centralWidgetLayout = new QHBoxLayout(centralWidget);
  centralWidgetLayout->addWidget(chartView);

  startButton = new QPushButton(tr("开始"));
  closeButton = new QPushButton(tr("退出"));
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(startButton);
  buttonLayout->addWidget(closeButton);

  mainLayout = new QGridLayout(this);
  mainLayout->addWidget(pathLabel, 0, 0);
  mainLayout->addWidget(pathLineEdit, 0, 1);
  mainLayout->addWidget(userNameLabel, 1, 0);
  mainLayout->addWidget(userNameLineEdit, 1, 1);
  mainLayout->addWidget(centralWidget, 2, 0, 1, 2);
  mainLayout->addLayout(buttonLayout, 3, 0, 1, 2);
  mainLayout->setColumnStretch(0, 2);
  mainLayout->setColumnStretch(1, 9);

  connect(startButton, SIGNAL(clicked()), this, SLOT(sendError()));
  connect(this, SIGNAL(getPathError()), this, SLOT(doPathError()));
  connect(this, SIGNAL(getPathError()), this, SLOT(close()));
  connect(this, SIGNAL(getUsersNameError()), this, SLOT(doUsersError()));
  connect(this, SIGNAL(getUsersNameError()), this, SLOT(close()));
  connect(startButton, &QPushButton::clicked, this, &MainWindow::start);
  connect(closeButton, &QPushButton::clicked, this, &MainWindow::close);

  this->setFixedSize(600, 600);
  this->setWindowTitle(tr("du"));

  allUsers = getUsersName();
}

QStringList MainWindow::getUsersName() const {
  QFile file("/etc/passwd");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream in(&file);

  QStringList usersName;

  while (!in.atEnd()) {
    QString eachLine = in.readLine();
    QStringList eachLineList = eachLine.split(":");
    if (eachLineList.at(2).toInt() >= 1000) {
      usersName.append(eachLineList.at(0));
    }
  }
  file.close();
  return usersName;
}

void MainWindow::getSize(QString path) {
  QDir dir(path);
  dir.setFilter(QDir::Files);
  QFileInfoList fileList = dir.entryInfoList();

  foreach (QFileInfo fileInfo, fileList) {
    for (QVector<EachUser>::Iterator iter = allInformation.begin();
         iter != allInformation.end(); ++iter) {
      if (fileInfo.owner() == iter->first) {
        iter->second += static_cast<unsigned long int>(fileInfo.size());
        break;
      }
    }
  }

  QStringList dirList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  foreach (QString dirInfo, dirList) {
    getSize(path + QDir::separator() + dirInfo);
  }
}

void MainWindow::sendError() {
  QDir dir(this->pathLineEdit->text());
  if (!dir.exists()) {
    errorMessage = this->pathLineEdit->text();
    emit getPathError();
  }

  const QStringList allUsers = getUsersName();
  const QStringList inputUsers = this->userNameLineEdit->text().split(" ");
  foreach (QString userName, inputUsers) {
    if (!allUsers.contains(userName)) {
      errorMessage = userName;
      emit getUsersNameError();
    }
  }
}

void MainWindow::start() {
  const QStringList inputUsers = this->userNameLineEdit->text().split(" ");
  allInformation.resize(inputUsers.size());
  int i = 0;
  for (QVector<EachUser>::Iterator iter = allInformation.begin();
       iter != allInformation.end(); ++iter) {
    iter->first = inputUsers.at(i);
    iter->second = 0;
    ++i;
  }

  getSize(this->pathLineEdit->text().trimmed());

  QPieSeries *pieSeries = new QPieSeries(centralWidget);
  for (QVector<EachUser>::Iterator iter = allInformation.begin();
       iter != allInformation.end(); ++iter) {
    if (iter->second >= 1024) {
      QString unit;
      if (iter->second > 1024 * 1024 * 1024) {
        unit = QString::number(iter->second / (1024 * 1024 * 1024)) + "G" +
               QString::number((iter->second % (1024 * 1024 * 1024)) /
                               (1024 * 1024)) +
               "M";
      } else if (iter->second > 1024 * 1024) {
        unit = QString::number(iter->second / (1024 * 1024)) + "M" +
               QString::number((iter->second % (1024 * 1024)) / (1024)) + "K";
      } else if (iter->second > 1024) {
        unit = QString::number(iter->second) + "K";
      }
      pieSeries->append(iter->first + " : " + unit, iter->second);
    }
  }
  pieSeries->setLabelsVisible(true);

  QChart *chart = new QChart;
  chart->addSeries(pieSeries);
  chart->setTitle(tr("磁盘用户使用状况"));
  chart->legend()->hide();

  chartView->setChart(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  update();
}

void MainWindow::doPathError() {
  QMessageBox::critical(this, tr("路径错误"),
                        errorMessage + tr(" 不存在，请检查。"));
  this->close();
}

void MainWindow::doUsersError() {
  QMessageBox::critical(this, tr("用户错误"),
                        errorMessage + tr("不存在，请检查。"));
  this->close();
}
