#include "window.h"

///
///
/// \param parent
///
Window::Window(QWidget *parent) : QWidget(parent) {
  createSpinBoxes();
  createDateTimeEdits();
  createDoubleSpinBoxes();
  setMyStyleSheet();

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(spinBoxesGroup);
  layout->addWidget(editsGroup);
  layout->addWidget(doubleSpinBoxesGroup);
  this->setLayout(layout);

  this->setWindowTitle(tr("Spin Boxes"));
  this->setFixedSize(sizeHint());
}

/// 加载自己的表单.
/// 利用全局指针qApp进行控制.
///
void Window::setMyStyleSheet() {
  QFile file(":/qss/myqss.qss");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Open error!!!";
  }
  QString styleSheet = QString(file.readAll());
  qApp->setStyleSheet(styleSheet);
  file.close();
}

///
///
/// \param decimals
///
void Window::changePrecision(int decimals) {
  doubleSpinBox->setDecimals(decimals);
  scaleSpinBox->setDecimals(decimals);
  priceSpinBox->setDecimals(decimals);
}

///
///
/// \param formatString
///
void Window::setFormatString(const QString &formatString) {
  meetingEdit->setDisplayFormat(formatString);

  if (meetingEdit->displayedSections() & QDateTimeEdit::DateSections_Mask) {
    meetingEdit->setDateRange(QDate(2004, 11, 1), QDate(2005, 11, 30));
    meetingLabel->setText(
        tr("Meeting date (between %0 and %1)")
            .arg(meetingEdit->minimumDate().toString(Qt::ISODate))
            .arg(meetingEdit->maximumDate().toString(Qt::ISODate)));
  } else {
    meetingEdit->setTimeRange(QTime(0, 7, 20, 0), QTime(21, 0, 0, 0));
    meetingLabel->setText(
        tr("Meeting time (between %0 and %1)")
            .arg(meetingEdit->minimumTime().toString(Qt::ISODate))
            .arg(meetingEdit->maximumTime().toString(Qt::ISODate)));
  }
}

///
///
///
void Window::createSpinBoxes() {
  /// \brief spinBoxesGroup
  ///
  /// spinBoxesGroup is used to contains spinBox.
  ///
  spinBoxesGroup = new QGroupBox(tr("Spinboxes"));

  QLabel *integerLabel =
      new QLabel(tr("Enter a value between %1 and %2:").arg(0).arg(1000));
  QSpinBox *integerSpinBox = new QSpinBox;
  integerSpinBox->setRange(-20, 20);
  integerSpinBox->setSingleStep(1);
  integerSpinBox->setValue(0);

  QLabel *zoomLabel =
      new QLabel(tr("Enter a zoom value between %1 and %2:").arg(0).arg(1000));
  QSpinBox *zoomSpinBox = new QSpinBox;
  zoomSpinBox->setRange(0, 1000);
  zoomSpinBox->setSingleStep(10);
  zoomSpinBox->setSuffix("%");  ///< a suffix
  zoomSpinBox->setSpecialValueText(tr("Automatic"));
  zoomSpinBox->setValue(100);

  QLabel *priceLabel =
      new QLabel(tr("Enter a price between %1 and %2:").arg(0).arg(999));
  QSpinBox *priceSpinBox = new QSpinBox;
  priceSpinBox->setRange(0, 999);
  priceSpinBox->setPrefix("$");
  priceSpinBox->setValue(99);

  QLabel *hexLabel = new QLabel(tr("Enter a value between %1 and %2:")
                                    .arg('-' + QString::number(31, 16))
                                    .arg(QString::number(31, 16)));
  QSpinBox *hexSpinBox = new QSpinBox;
  hexSpinBox->setRange(-31, 31);
  hexSpinBox->setSingleStep(1);
  hexSpinBox->setDisplayIntegerBase(16);

  groupSeparatorSpinBox = new QSpinBox;
  groupSeparatorSpinBox->setRange(-9999999, 9999999);
  groupSeparatorSpinBox->setValue(1000);
  groupSeparatorSpinBox->setGroupSeparatorShown(true);
  QCheckBox *groupSeparatorChkBox = new QCheckBox;
  groupSeparatorChkBox->setText(tr("Show group separator"));
  groupSeparatorChkBox->setChecked(true);
  connect(groupSeparatorChkBox, &QCheckBox::toggled, groupSeparatorSpinBox,
          &QSpinBox::setGroupSeparatorShown);

  QVBoxLayout *spinBoxLayout = new QVBoxLayout;
  spinBoxLayout->addWidget(integerLabel);
  spinBoxLayout->addWidget(integerSpinBox);
  spinBoxLayout->addWidget(zoomLabel);
  spinBoxLayout->addWidget(zoomSpinBox);
  spinBoxLayout->addWidget(priceLabel);
  spinBoxLayout->addWidget(priceSpinBox);
  spinBoxLayout->addWidget(hexLabel);
  spinBoxLayout->addWidget(hexSpinBox);
  spinBoxLayout->addWidget(groupSeparatorChkBox);
  spinBoxLayout->addWidget(groupSeparatorSpinBox);
  spinBoxesGroup->setLayout(spinBoxLayout);
}

///
///
///
void Window::createDateTimeEdits() {
  editsGroup = new QGroupBox(tr("Date and time spin boxes"));

  QLabel *dateLabel = new QLabel;
  QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
  dateEdit->setDateRange(QDate(2005, 1, 1), QDate(2020, 12, 31));
  dateLabel->setText(tr("Appointment date (between %0 and %1):")
                         .arg(dateEdit->minimumDate().toString(Qt::ISODate))
                         .arg(dateEdit->maximumDate().toString(Qt::ISODate)));

  QLabel *timeLabel = new QLabel;
  QTimeEdit *timeEdit = new QTimeEdit(QTime::currentTime());
  timeEdit->setTimeRange(QTime(9, 0, 0, 0), QTime(16, 30, 0, 0));
  timeLabel->setText(tr("Appointment time (between %0 and %1):")
                         .arg(timeEdit->minimumTime().toString(Qt::ISODate))
                         .arg(timeEdit->maximumTime().toString(Qt::ISODate)));

  meetingLabel = new QLabel;
  meetingEdit = new QDateTimeEdit(QDateTime::currentDateTime());
  QLabel *formatLabel =
      new QLabel(tr("Format string for the meeting date and time:"));
  QComboBox *formatComboBox = new QComboBox;
  formatComboBox->addItem("yyyy-MM-dd hh:mm:ss (zzz 'ms')");
  formatComboBox->addItem("hh:mm:ss MM/dd/yyyy");
  formatComboBox->addItem("hh:mm:ss dd/MM/yyyy");
  formatComboBox->addItem("hh:mm:ss");
  formatComboBox->addItem("hh:mm ap");
  connect(formatComboBox, SIGNAL(activated(QString)), this,
          SLOT(setFormatString(QString)));

  setFormatString(formatComboBox->currentText());

  QVBoxLayout *editsLayout = new QVBoxLayout;
  editsLayout->addWidget(dateLabel);
  editsLayout->addWidget(dateEdit);
  editsLayout->addWidget(timeLabel);
  editsLayout->addWidget(timeEdit);
  editsLayout->addWidget(meetingLabel);
  editsLayout->addWidget(meetingEdit);
  editsLayout->addWidget(formatLabel);
  editsLayout->addWidget(formatComboBox);
  editsGroup->setLayout(editsLayout);
}

///
///
///
void Window::createDoubleSpinBoxes() {
  doubleSpinBoxesGroup = new QGroupBox(tr("Double precision spinboxes"));

  QLabel *precisionLabel = new QLabel(tr("Number of decimal places to show:"));
  QSpinBox *precisionSpinBox = new QSpinBox;
  precisionSpinBox->setRange(0, 100);
  precisionSpinBox->setValue(2);

  QLabel *doubleLabel =
      new QLabel(tr("Enter a value between %1 and %2:").arg(-20).arg(20));
  doubleSpinBox = new QDoubleSpinBox;
  doubleSpinBox->setRange(-20.0, 20.0);
  doubleSpinBox->setSingleStep(1.0);
  doubleSpinBox->setValue(0.0);

  QLabel *scaleLabel = new QLabel(
      tr("Enter a scale factor between %1 and %2:").arg(0).arg(1000.0));
  scaleSpinBox = new QDoubleSpinBox;
  scaleSpinBox->setRange(0.0, 1000.0);
  scaleSpinBox->setSingleStep(10.0);
  scaleSpinBox->setSuffix("%");
  scaleSpinBox->setSpecialValueText(tr("No scaling"));
  scaleSpinBox->setValue(100.0);

  QLabel *priceLabel =
      new QLabel(tr("Enter a price between %1 and %2:").arg(0).arg(1000));
  priceSpinBox = new QDoubleSpinBox;
  priceSpinBox->setRange(0.0, 1000.0);
  priceSpinBox->setSingleStep(1.0);
  priceSpinBox->setPrefix(tr("$"));
  priceSpinBox->setValue(99.99);
  connect(precisionSpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(changePrecision(int)));

  groupSeparatorSpinBox_d = new QDoubleSpinBox;
  groupSeparatorSpinBox_d->setRange(-99999999, 99999999);
  groupSeparatorSpinBox_d->setDecimals(2);
  groupSeparatorSpinBox_d->setValue(1000.00);
  groupSeparatorSpinBox_d->setGroupSeparatorShown(true);
  QCheckBox *groupSeparatorChkBox = new QCheckBox;
  groupSeparatorChkBox->setText(tr("Show group separator"));
  groupSeparatorChkBox->setChecked(true);
  connect(groupSeparatorChkBox, &QCheckBox::toggled, groupSeparatorSpinBox_d,
          &QDoubleSpinBox::setGroupSeparatorShown);

  QVBoxLayout *spinBoxLayout = new QVBoxLayout;
  spinBoxLayout->addWidget(precisionLabel);
  spinBoxLayout->addWidget(precisionSpinBox);
  spinBoxLayout->addWidget(doubleLabel);
  spinBoxLayout->addWidget(doubleSpinBox);
  spinBoxLayout->addWidget(scaleLabel);
  spinBoxLayout->addWidget(scaleSpinBox);
  spinBoxLayout->addWidget(priceLabel);
  spinBoxLayout->addWidget(priceSpinBox);
  spinBoxLayout->addWidget(groupSeparatorChkBox);
  spinBoxLayout->addWidget(groupSeparatorSpinBox_d);
  doubleSpinBoxesGroup->setLayout(spinBoxLayout);
}
