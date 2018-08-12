#include <QCheckBox>
#include <QDateTime>
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "QssStyle.h"
#include "fileinfo.h"

FileInfo::FileInfo(QWidget *parent) : QDialog(parent) {
  QssStyle::setStyle(":/myqss.qss");
  fileNameLabel = new QLabel(tr("file name: "));
  fileNameLineEdit = new QLineEdit;
  fileBtn = new QPushButton(tr("file"));

  sizeLabel = new QLabel(tr("size: "));
  sizeLineEdit = new QLineEdit;

  createTimeLabel = new QLabel(tr("create time: "));
  createTimeLineEdit = new QLineEdit;

  lastModifiedTimeLabel = new QLabel(tr("last modified time: "));
  lastModifiedTimeLineEdit = new QLineEdit;

  lastReadLabel = new QLabel(tr("last read time: "));
  lastReadLineEdit = new QLineEdit;

  propertyLabel = new QLabel(tr("properties: "));
  isDirCheckBox = new QCheckBox(tr("Dir"));
  isFileCheckBox = new QCheckBox(tr("File"));
  isSymLinkCheckBox = new QCheckBox(tr("Symlink"));
  isHiddenCheckBox = new QCheckBox(tr("Hidden"));
  isReadableCheckBox = new QCheckBox(tr("Readable"));
  isWritableCheckBox = new QCheckBox(tr("Wirtable"));
  isExecutableCheckBox = new QCheckBox(tr("Exectable"));

  getBtn = new QPushButton(tr("Get File Information"));

  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(fileNameLabel, 0, 0);
  gridLayout->addWidget(fileNameLineEdit, 0, 1);
  gridLayout->addWidget(fileBtn, 0, 2);
  gridLayout->addWidget(sizeLabel, 1, 0);
  gridLayout->addWidget(sizeLineEdit, 1, 1, 1, 2);
  gridLayout->addWidget(createTimeLabel, 2, 0);
  gridLayout->addWidget(createTimeLineEdit, 2, 1, 1, 2);
  gridLayout->addWidget(lastModifiedTimeLabel, 3, 0);
  gridLayout->addWidget(lastModifiedTimeLineEdit, 3, 1, 1, 2);
  gridLayout->addWidget(lastReadLabel, 4, 0);
  gridLayout->addWidget(lastReadLineEdit, 4, 1, 1, 2);

  QHBoxLayout *layout2 = new QHBoxLayout;
  layout2->addWidget(propertyLabel);
  layout2->addStretch();

  QHBoxLayout *layout3 = new QHBoxLayout;
  layout3->addWidget(isDirCheckBox);
  layout3->addWidget(isFileCheckBox);
  layout3->addWidget(isSymLinkCheckBox);
  layout3->addWidget(isHiddenCheckBox);
  layout3->addWidget(isReadableCheckBox);
  layout3->addWidget(isWritableCheckBox);
  layout3->addWidget(isExecutableCheckBox);

  QHBoxLayout *layout4 = new QHBoxLayout;
  layout4->addWidget(getBtn);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addLayout(gridLayout);
  mainLayout->addLayout(layout2);
  mainLayout->addLayout(layout3);
  mainLayout->addLayout(layout4);

  connect(fileBtn, SIGNAL(clicked()), this, SLOT(slotFile()));
  connect(getBtn, SIGNAL(clicked()), this, SLOT(slotGet()));
}

FileInfo::~FileInfo() {}

void FileInfo::slotFile() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "open", QDir::homePath(), "files (*)");
  fileNameLineEdit->setText(fileName.toLatin1());
}

void FileInfo::slotGet() {
  QString file = fileNameLineEdit->text();
  QFileInfo info(file);

  qint64 size = info.size();
  QDateTime created = info.birthTime();
  QDateTime lastModified = info.lastModified();
  QDateTime lastRead = info.lastRead();

  bool isDir = info.isDir();
  bool isFile = info.isFile();
  bool isSymLink = info.isSymLink();
  bool isHidden = info.isHidden();
  bool isReadable = info.isReadable();
  bool isWritable = info.isWritable();
  bool isExecutable = info.isExecutable();

  sizeLineEdit->setText(QString::number(size));
  createTimeLineEdit->setText(created.toString());
  lastModifiedTimeLineEdit->setText(lastModified.toString());
  lastReadLineEdit->setText(lastRead.toString());

  isDirCheckBox->setCheckState(isDir ? Qt::Checked : Qt::Unchecked);
  isFileCheckBox->setCheckState(isFile ? Qt::Checked : Qt::Unchecked);
  isSymLinkCheckBox->setCheckState(isSymLink ? Qt::Checked : Qt::Unchecked);
  isHiddenCheckBox->setCheckState(isHidden ? Qt::Checked : Qt::Unchecked);
  isReadableCheckBox->setCheckState(isReadable ? Qt::Checked : Qt::Unchecked);
  isWritableCheckBox->setCheckState(isWritable ? Qt::Checked : Qt::Unchecked);
  isExecutableCheckBox->setCheckState(isExecutable ? Qt::Checked
                                                   : Qt::Unchecked);
}
