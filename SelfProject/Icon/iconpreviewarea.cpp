#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "iconpreviewarea.h"

///
/// \brief IconPreviewArea::IconPreviewArea
/// \param parent
///
/// -------------------------------------------------
/// |      | Normal | Active | Disabled | Selected |
/// -------------------------------------------------
/// | Off  | pic    | pic    | pic      | pic      |
/// -------------------------------------------------
/// | On   | pic    | pic    | pic      | pic      |
/// -------------------------------------------------
IconPreviewArea::IconPreviewArea(QWidget* parent) : QWidget(parent) {
  QGridLayout* mainLayout = new QGridLayout(this);

  /// NumStates is 2, add OFF and ON in layout.
  for (int row = 0; row != NumStates; ++row) {
    stateLabels[row] =
        createHeaderLabel(IconPreviewArea::iconStateNames().at(row));
    mainLayout->addWidget(stateLabels[row], row + 1, 0);
  }
  Q_ASSERT(NumStates == 2);

  /// NumModes is 4, add Normal, Active, Disabled and Selected in layout.
  for (int column = 0; column != NumModes; ++column) {
    modeLabels[column] =
        createHeaderLabel(IconPreviewArea::iconModelNames().at(column));
    mainLayout->addWidget(modeLabels[column], 0, column + 1);
  }
  Q_ASSERT(NumModes == 4);

  /// add label in area.
  for (int column = 0; column != NumModes; ++column) {
    for (int row = 0; row != NumStates; ++row) {
      pixmapLabels[column][row] = createPixmapLabel();
      mainLayout->addWidget(pixmapLabels[column][row], row + 1, column + 1);
    }  /// for
  }    /// for
}

///
/// \brief IconPreviewArea::setIcon
/// \param icon
///
void IconPreviewArea::setIcon(const QIcon& icon) {
  this->icon = icon;
  updatePixmapLabels();
}

///
/// \brief IconPreviewArea::setSize
/// \param size
///
void IconPreviewArea::setSize(const QSize& size) {
  if (size != this->size) {
    this->size = size;
    updatePixmapLabels();
  }
}

#ifdef Q_COMPILER_INITIALIZER_LISTS

///
/// \brief IconPreviewArea::iconModes
/// \return
///
QVector<QIcon::Mode> IconPreviewArea::iconModes() {
  static const QVector<QIcon::Mode> result = {QIcon::Normal,   QIcon::Active,
                                              QIcon::Disabled, QIcon::Selected};
  return result;
}

///
/// \brief IconPreviewArea::iconStates
/// \return
///
QVector<QIcon::State> IconPreviewArea::iconStates() {
  static const QVector<QIcon::State> result = {QIcon::Off, QIcon::On};
  return result;
}

///
/// \brief IconPreviewArea::iconModelNames
/// \return
///
QStringList IconPreviewArea::iconModelNames() {
  static const QStringList result = {tr("Normal"),   tr("Active"),
                                     tr("Disabled"), tr("Selected")};
  return result;
}

///
/// \brief IconPreviewArea::iconStateNames
/// \return
///
QStringList IconPreviewArea::iconStateNames() {
  static const QStringList result = {tr("Off"), tr("On")};
  return result;
}

#else

QVector<QIcon::Mode> IconPreviewArea::iconModes() {
  static QVector<QIcon::Mode> result;
  if (result.isEmpty()) {
    result << QIcon::Normal << QIcon::Active << QIcon::Disabled
           << QIcon::Selected;
  }
  return result;
}

QVector<QIcon::State> IconPreviewArea::iconStates() {
  static QVector<QIcon::State> result;
  if (result.isEmpty()) {
    result << QIcon::Off << QIcon::On;
  }
  return result;
}

QStringList IconPreviewArea::iconModelNames() {
  static QStringList result;
  if (result.isEmpty()) {
    result << tr("Normal") << tr("Active") << tr("Disabled") << tr("Selected");
  }
  return result;
}

QStringList IconPreviewArea::iconStateNames() {
  static QStringList result;
  if (result.isEmpty()) {
    result << tr("Off") << tr("On");
  }
  return result;
}

#endif  /// Q_COMPILER_INITIALIZER_LISTS

///
/// \brief IconPreviewArea::createHeaderLabel
/// \param text
/// \return
///
QLabel* IconPreviewArea::createHeaderLabel(const QString& text) {
  QLabel* label = new QLabel(tr("<b>%1</b>").arg(text));
  label->setAlignment(Qt::AlignCenter);
}

///
/// \brief IconPreviewArea::createPixmapLabel
/// \return
///
QLabel* IconPreviewArea::createPixmapLabel() {
  QLabel* label = new QLabel;
  label->setEnabled(false);
  label->setAlignment(Qt::AlignCenter);
  label->setFrameShape(QFrame::Box);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  label->setBackgroundRole(QPalette::Base);
  label->setAutoFillBackground(true);
  label->setMinimumSize(132, 132);
  return label;
}

///
/// \brief IconPreviewArea::updatePixmapLabels
///
void IconPreviewArea::updatePixmapLabels() {
  QWindow* window = Q_NULLPTR;
  if (const QWidget* nativeParent = nativeParentWidget()) {
    window = nativeParent->windowHandle();
  }
  for (int column = 0; column != NumModes; ++column) {
    for (int row = 0; row != NumStates; ++row) {
      const QPixmap pixmap =
          icon.pixmap(window, size, IconPreviewArea::iconModes().at(column),
                      IconPreviewArea::iconStates().at(row));
      QLabel* pixmapLabel = pixmapLabel[column][row];
      pixmapLabel->setPixmap(pixmap);
      pixmapLabel->setEnabled(!pixmap.isNull());
      QString toolTip;
      if (!pixmap.isNull()) {
        const QSize actualSize = icon.actualSize(size);
        toolTip = tr("Size: %1x%2\nActual size: 3%x4%\nDevice pixel ratio: 5%")
                      .arg(size.width())
                      .arg(size.height())
                      .arg(actualSize.width())
                      .arg(actualSize.height())
                      .arg(pixmap.devicePixelRatioF());
      }
      pixmapLabel->setToolTip(toolTip);
    }
  }
}
