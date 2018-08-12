#include <QGridLayout>
#include <QLabel>

#include "QssStyle.h"
#include "geometry.h"

Geometry::Geometry(QWidget *parent) : QDialog(parent) {
  this->setWindowTitle(tr("Geometry"));
  QssStyle::setStyle(":/qss/myqss.qss");

  xLabel = new QLabel(tr("x(): "));
  xValueLabel = new QLabel;

  yLabel = new QLabel(tr("y(): "));
  yValueLabel = new QLabel;

  posLabel = new QLabel(tr("pos(): "));
  posValueLabel = new QLabel;

  FrmLabel = new QLabel(tr("Frame: "));
  FrmValueLabel = new QLabel;

  geoLabel = new QLabel(tr("geometry(): "));
  geoValueLabel = new QLabel;

  widthLabel = new QLabel(tr("width(): "));
  widthValueLabel = new QLabel;

  heightLabel = new QLabel(tr("height(): "));
  heightValueLabel = new QLabel;

  rectLabel = new QLabel(tr("rect(): "));
  rectValueLabel = new QLabel;

  sizeLabel = new QLabel(tr("size(): "));
  sizeValueLabel = new QLabel;

  mainLayout = new QGridLayout(this);
  mainLayout->addWidget(xLabel, 0, 0);
  mainLayout->addWidget(xValueLabel, 0, 1);
  mainLayout->addWidget(yLabel, 1, 0);
  mainLayout->addWidget(yValueLabel, 1, 1);
  mainLayout->addWidget(posLabel, 2, 0);
  mainLayout->addWidget(posValueLabel, 2, 1);
  mainLayout->addWidget(FrmLabel, 3, 0);
  mainLayout->addWidget(FrmValueLabel, 3, 1);
  mainLayout->addWidget(geoLabel, 4, 0);
  mainLayout->addWidget(geoValueLabel, 4, 1);
  mainLayout->addWidget(widthLabel, 5, 0);
  mainLayout->addWidget(widthValueLabel, 5, 1);
  mainLayout->addWidget(heightLabel, 6, 0);
  mainLayout->addWidget(heightValueLabel, 6, 1);
  mainLayout->addWidget(rectLabel, 7, 0);
  mainLayout->addWidget(rectValueLabel, 7, 1);
  mainLayout->addWidget(sizeLabel, 8, 0);
  mainLayout->addWidget(sizeValueLabel, 8, 1);

  this->updateLabel();
}

Geometry::~Geometry() {}

void Geometry::updateLabel() {
  QString xStr;
  xValueLabel->setText(xStr.setNum(x()));
  QString yStr;
  yValueLabel->setText(yStr.setNum(y()));

  QString frameStr;
  QString tempStr[4];
  frameStr = tempStr[0].setNum(frameGeometry().x()) + "," +
             tempStr[1].setNum(frameGeometry().y()) + "," +
             tempStr[2].setNum(frameGeometry().width()) + "," +
             tempStr[3].setNum(frameGeometry().height());
  FrmValueLabel->setText(frameStr);

  QString positionStr;
  QString tempStr1, tempStr2;
  positionStr = tempStr1.setNum(pos().x()) + "," + tempStr2.setNum(pos().y());
  posValueLabel->setText(positionStr);

  QString geoStr;
  QString tempS[4];
  geoStr = tempS[0].setNum(geometry().x()) + "," +
           tempS[1].setNum(geometry().y()) + "," +
           tempS[2].setNum(geometry().width()) + "," +
           tempS[3].setNum(geometry().height());
  geoValueLabel->setText(geoStr);

  QString wStr, hStr;
  widthValueLabel->setText(QString::number(width()));
  heightValueLabel->setText(QString::number(height()));

  QString rectStr;
  rectStr = QString::number(rect().x()) + "," + QString::number(rect().y()) +
            "," + QString::number(rect().width()) + "," +
            QString::number(rect().height());
  rectValueLabel->setText(rectStr);

  QString sizeStr;
  sizeStr =
      QString::number(size().width()) + "," + QString::number(size().height());
  sizeValueLabel->setText(sizeStr);
}

void Geometry::moveEvent(QMoveEvent *event) { updateLabel(); }

void Geometry::resizeEvent(QResizeEvent *event) { updateLabel(); }
