#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QScrollArea>

#include "donewdialog.h"
#include "mainwindow.h"
#include "paintarea.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->resize(700, 500);
  area = new PaintArea;
  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(area);
  scrollArea->widget()->setMinimumSize(800, 600);

  this->setCentralWidget(scrollArea);

  isSaved = false;
  curFile = tr("unknown.png");

  createColorComboBox(ui->penColorCombBox);
  createColorComboBox(ui->brushColorComboBox);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::doNew() {
  if (maybeSave()) {
    DoNewDialog dlg;
    if (dlg.exec() == QDialog::Accepted) {
      int width = dlg.getWidth();
      int height = dlg.getHeight();
      area->setImageSize(width, height);
      scrollArea->widget()->resize(width, height);
      area->setImageColor(dlg.getBackColor());
      isSaved = false;
    }
  }
}

void MainWindow::doOpen() {
  if (maybeSave()) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::currentPath());
    if (!fileName.isEmpty()) {
      area->openImage(fileName);
      scrollArea->widget()->resize(area->getImageSize());
      isSaved = true;
      curFile = fileName;
    }
  }
}

bool MainWindow::doFileSave() {
  if (isSaved) {
    return saveFile(curFile);
  } else {
    return doFileSaveAs();
  }
}

bool MainWindow::doFileSaveAs() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("save as"), curFile);
  if (fileName.isEmpty()) {
    return false;
  } else {
    saveFile(fileName);
  }
  return false;
}

void MainWindow::createColorComboBox(QComboBox *comboBox) {
  QPixmap pix(16, 16);
  QPainter painter(&pix);
  painter.fillRect(0, 0, 16, 16, Qt::black);
  comboBox->addItem(QIcon(pix), tr("black"), tr("black"));
  painter.fillRect(0, 0, 16, 16, Qt::white);
  comboBox->addItem(QIcon(pix), tr("black"), tr("white"));
  painter.fillRect(0, 0, 16, 16, Qt::red);
  comboBox->addItem(QIcon(pix), tr("black"), tr("red"));
  painter.fillRect(0, 0, 16, 16, Qt::green);
  comboBox->addItem(QIcon(pix), tr("black"), tr("green"));
  painter.fillRect(0, 0, 16, 16, Qt::blue);
  comboBox->addItem(QIcon(pix), tr("black"), tr("blue"));
  painter.fillRect(0, 0, 16, 16, Qt::yellow);
  comboBox->addItem(QIcon(pix), tr("black"), tr("yellow"));
  comboBox->addItem(tr("transparent"), tr("transparent"));
}

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

void MainWindow::on_action_N_triggered() {
  //  DoNewDialog dlg(this);
  //  if (dlg.exec() == QDialog::Accepted) {
  //    int width = dlg.getWidth();
  //    int height = dlg.getHeight();
  //    area->setImageSize(width, height);
  //    scrollArea->widget()->resize(width, height);
  //    area->setImageColor(dlg.getBackColor());
  //  }
  doNew();
}

bool MainWindow::maybeSave() {
  if (area->isModified()) {
    QMessageBox::StandardButton box = QMessageBox::warning(
        this, tr("save file"), tr("the file is changed, do you want save it?"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (box == QMessageBox::Yes) {
      return doFileSave();
    } else if (box == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}

bool MainWindow::saveFile(QString fileName) {
  if (area->saveImage(fileName, "png")) {
    isSaved = true;
    return false;
  } else
    return false;
}

void MainWindow::on_action_O_triggered() { doOpen(); }

void MainWindow::on_action_S_triggered() { doFileSave(); }

void MainWindow::on_action_A_triggered() { doFileSaveAs(); }

void MainWindow::on_action_X_triggered() {
  if (maybeSave()) {
    qApp->quit();
  }
}

void MainWindow::on_action_P_triggered() { area->doPrint(); }

void MainWindow::on_action_4_triggered() {
  area->zoomIn();
  scrollArea->widget()->resize(area->getImageSize());
}

void MainWindow::on_action_5_triggered() { area->zoomOut(); }

void MainWindow::on_action_6_triggered() { area->zoom_1(); }

void MainWindow::on_action_7_triggered() { area->doRotate(); }

void MainWindow::on_action_8_triggered() { area->doShear(); }

void MainWindow::on_action_10_triggered() { area->doClear(); }

void MainWindow::on_action_11_triggered() { ui->dockWidget_2->show(); }

void MainWindow::on_shapeComboBox_currentIndexChanged(const QString &shape) {
  if (shape == tr("wu")) {
    area->setShape(PaintArea::None);
  } else if (shape == tr("juxing")) {
    area->setShape(PaintArea::Rectangle);
  } else if (shape == tr("line")) {
    area->setShape(PaintArea::Line);
  } else if (shape == tr("tuoyuan")) {
    area->setShape(PaintArea::Ellipse);
  }
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(const QString &style) {
  if (style == tr("shixian")) {
    area->setPenStyle(Qt::SolidLine);
  } else if (style == tr("dianxian")) {
    area->setPenStyle(Qt::DotLine);
  }
}

void MainWindow::on_penWidthSpinBox_valueChanged(int width) {
  area->setPenWidth(width);
}

void MainWindow::on_penColorCombBox_currentIndexChanged(int index) {
  QColor color =
      ui->penColorCombBox->itemData(index, Qt::UserRole).value<QColor>();
  area->setPenColor(color);
}

void MainWindow::on_brushColorComboBox_currentIndexChanged(int index) {
  QColor color =
      ui->brushColorComboBox->itemData(index, Qt::UserRole).value<QColor>();
  area->setBrushColor(color);
}
