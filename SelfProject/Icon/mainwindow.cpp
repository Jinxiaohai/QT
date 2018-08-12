#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QWindow>
#include <QScreen>
#include <QStandardPaths>

#include "mainwindow.h"
#include "iconpreviewarea.h"
#include "iconsizespinbox.h"
#include "imagedelegate.h"

enum {
  OtherSize = QStyle::PM_CustomBase
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  createActions();

  QGridLayout *mainLayout = new QGridLayout(centralWidget);

  QGroupBox *previewGroupBox = new QGroupBox(tr("Preview"));
  previewArea = new IconPreviewArea(previewGroupBox);
  QVBoxLayout *previewLayout = new QVBoxLayout(previewGroupBox);
  previewLayout->addWidget(previewArea);

  mainLayout->addWidget(previewGroupBox, 0, 0, 1, 2);
  mainLayout->addWidget(createImagesGroupBox(), 1, 0);
  QVBoxLayout *vBox = new QVBoxLayout;
  vBox->addWidget(createIconSizeGroupBox());
  vBox->addWidget(createHighDpiIconSizeGroupBox());
  vBox->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored,
                                QSizePolicy::MinimumExpanding));
  mainLayout->addLayout(vBox, 1, 1);
  createContextMenu();

  setWindowTitle(tr("Icons"));
  checkCurrentStyle();
  sizeButtonGroup->button(OtherSize)->click();
}

MainWindow::~MainWindow() {}

void MainWindow::loadImages(const QStringList &fileNames) {
  foreach(const QString & fileName, fileNames) {
    const int row = imagesTable->rowCount();
    imagesTable->setRowCount(row + 1);

    const QFileInfo fileInfo(fileName);
    const QString imageName = fileInfo.baseName();
    const QString fileName2x = fileInfo.absolutePath() + QLatin1Char('/') +
                               imageName + QLatin1String("@2x.") +
                               fileInfo.suffix();
    const QFileInfo fileInfo2x(fileName2x);
    const QImage image(fileName);
    const QString toolTip =
        tr("Directory: %1\nFile: %2\nFile@2x: %3Size: %4x%5")
            .arg(QDir::toNativeSeparators(fileInfo.absoluteFilePath()),
                 fileInfo.fileName())
            .arg(fileInfo2x.exists() ? fileInfo2x.fileName() : tr("None"))
            .arg(image.width())
            .arg(image.height());

    QTableWidgetItem *fileItem = new QTableWidgetItem(imageName);
    fileItem->setData(Qt::UserRole, fileName);
    fileItem->setIcon(QPixmap::fromImage(image));
    fileItem->setFlags((fileItem->flags() | Qt::ItemIsUserCheckable) &
                       ~Qt::ItemIsEditable);
    fileItem->setToolTip(toolTip);

    QIcon::Mode mode = QIcon::Normal;

    QIcon::State state = QIcon::Off;
    if (guessModeStateAct->isChecked()) {
      if (imageName.contains(QLatin1String("_act"), Qt::CaseInsensitive)) {
        mode = QIcon::Active;
      } else if (imageName.contains(QLatin1String("_dis"),
                                    Qt::CaseInsensitive)) {
        mode = QIcon::Disabled;
      } else if (imageName.contains(QLatin1String("_sel"),
                                    Qt::CaseInsensitive)) {
        mode = QIcon::Selected;
      }
      if (imageName.contains(QLatin1String("_on"), Qt::CaseInsensitive)) {
        state = QIcon::On;
      }

      imagesTable->setItem(row, 0, fileItem);

      QTableWidgetItem *modeItem =
          new QTableWidgetItem(IconPreviewArea::iconStateNames().at(
              IconPreviewArea::iconModes().indexOf(mode)));
      modeItem->setToolTip(toolTip);
      imagesTable->setItem(row, 1, modeItem);
      QTableWidgetItem *stateItem =
          new QTableWidgetItem(IconPreviewArea::iconStateNames().at(
              IconPreviewArea::iconStates().indexOf(state)));
      stateItem->setToolTip(toolTip);
      imagesTable->setItem(row, 2, stateItem);
      imagesTable->openPersistentEditor(modeItem);
      imagesTable->openPersistentEditor(stateItem);

      fileItem->setCheckState(Qt::Checked);
    }
  }
}

void MainWindow::show() {
  QMainWindow::show();
  connect(windowHandle(), &QWindow::screenChanged, this,
          &MainWindow::screenChanged);
  screenChanged();
}

void MainWindow::about() {
  QMessageBox::about(this, tr("About Icons"),
                     tr("The <b>Icons</b> example was created by xiaohai."));
}

void MainWindow::changeStyle(bool checked) {
  if (!checked) {
    return;
  }

  const QAction *action = qobject_cast<QAction *>(sender());

  QStyle *style = QStyleFactory::create(action->data().toString());

  Q_ASSERT(style);
  QApplication::setStyle(style);

  foreach(QAbstractButton * button, sizeButtonGroup->buttons()) {
    const QStyle::PixelMetric metric =
        static_cast<QStyle::PixelMetric>(sizeButtonGroup->id(button));
    const int value = style->pixelMetric(metric);
    switch (metric) {
      case QStyle::PM_SmallIconSize: {
        button->setText(tr("Small (%1 x %1)").arg(value));
        break;
      }
      case QStyle::PM_LargeIconSize: {
        button->setText(tr("Large (%1 x %1)").arg(value));
        break;
      }
      case QStyle::PM_ToolBarIconSize: {
        button->setText(tr("Toolbars (%1 x %1)").arg(value));
        break;
      }
      case QStyle::PM_ListViewIconSize: {
        button->setText(tr("List views (%1 x %1)").arg(value));
        break;
      }
      case QStyle::PM_IconViewIconSize: {
        button->setText(tr("Icon views (%1 x %1)").arg(value));
        break;
      }
      case QStyle::PM_TabBarIconSize: {
        button->setText(tr("Tab bars (%1 x %1)").arg(value));
        break;
      }
      default:
        break;
    }
  }
  triggerChangeSize();
}

void MainWindow::changeSize(int id, bool checked) {
  if (!checked) {
    return;
  }

  const bool other = id == int(OtherSize);
  const int extent =
      other ? otherSpinBox->value() : QApplication::style()->pixelMetric(
                                          static_cast<QStyle::PixelMetric>(id));

  previewArea->setSize(QSize(extent, extent));
  otherSpinBox->setEnabled(other);
}

void MainWindow::triggerChangeSize() {
  changeSize(sizeButtonGroup->checkedId(), true);
}

void MainWindow::changeIcon() {
  QIcon icon;
  for (int row = 0; row != imagesTable->rowCount(); ++row) {
    const QTableWidgetItem *fileItem = imagesTable->item(row, 0);
    const QTableWidgetItem *modeItem = imagesTable->item(row, 1);
    const QTableWidgetItem *stateItem = imagesTable->item(row, 2);

    if (fileItem->checkState() == Qt::Checked) {
      const int modeIndex =
          IconPreviewArea::iconModelNames().indexOf(modeItem->text());
      Q_ASSERT(modeIndex >= 0);
      const int stateIndex =
          IconPreviewArea::iconStateNames().indexOf(stateItem->text());
      Q_ASSERT(stateIndex >= 0);
      const QIcon::Mode mode = IconPreviewArea::iconModes().at(modeIndex);
      const QIcon::State state = IconPreviewArea::iconStates().at(stateIndex);

      const QString fileName = fileItem->data(Qt::UserRole).toString();
      QImage image(fileName);
      if (!image.isNull()) {
        icon.addPixmap(QPixmap::fromImage(image), mode, state);
      }

      previewArea->setIcon(icon);
    }
  }
}

void MainWindow::addSampleImages() {
  addImages(QLatin1String(SRCDIR) + QLatin1String("images"));
}

void MainWindow::addOtherImages() {
  static bool firstInvocation = true;
  QString directory;
  if (firstInvocation) {
    directory = QStandardPaths::standardLocations(
        QStandardPaths::PicturesLocation).value(0, QString());
  }
  addImages(directory);
}

void MainWindow::removeAllImages() {
  imagesTable->setRowCount(0);
  changeIcon();
}

void MainWindow::useHighDpiPixmapsChanged(int checkState) {
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps,
                                 checkState == Qt::Checked);
  changeIcon();
}

void MainWindow::screenChanged() {
  devicePixelRatioLabel->setText(QString::number(devicePixelRatioF()));
  if (const QWindow *window = windowHandle()) {
    const QScreen *screen = window->screen();
    const QString screenDescription = tr("\"%1\" (%2x%3)")
                                          .arg(screen->name())
                                          .arg(screen->geometry().width())
                                          .arg(screen->geometry().height());
    screenNameLabel->setText(screenDescription);
  }
  changeIcon();
}

QWidget *MainWindow::createImagesGroupBox() {
  QGroupBox *imagesGroupBox = new QGroupBox(tr("Images"));

  imagesTable = new QTableWidget;
  imagesTable->setSelectionMode(QAbstractItemView::NoSelection);
  imagesTable->setItemDelegate(new ImageDelegate(this));

  QStringList labels;
  labels << tr("Image") << tr("Mode") << tr("State");
  imagesTable->horizontalHeader()->setDefaultSectionSize(90);
  imagesTable->setColumnCount(3);
  imagesTable->setHorizontalHeaderLabels(labels);
  imagesTable->horizontalHeader()->setSectionResizeMode(0,
                                                        QHeaderView::Stretch);
  imagesTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
  imagesTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
  imagesTable->verticalHeader()->hide();

  connect(imagesTable, &QTableWidget::itemChanged, this,
          &MainWindow::changeIcon);
  QVBoxLayout *layout = new QVBoxLayout(imagesGroupBox);
  layout->addWidget(imagesTable);
  return imagesGroupBox;
}

QWidget *MainWindow::createIconSizeGroupBox() {}
