#ifndef FILEINFO_H
#define FILEINFO_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
QT_END_NAMESPACE

class FileInfo : public QDialog {
  Q_OBJECT

 public:
  FileInfo(QWidget *parent = 0);
  ~FileInfo();

 public slots:
  void slotFile();
  void slotGet();

 private:
  QLabel *fileNameLabel;
  QLineEdit *fileNameLineEdit;
  QPushButton *fileBtn;

  QLabel *sizeLabel;
  QLineEdit *sizeLineEdit;

  QLabel *createTimeLabel;
  QLineEdit *createTimeLineEdit;

  QLabel *lastModifiedTimeLabel;
  QLineEdit *lastModifiedTimeLineEdit;

  QLabel *lastReadLabel;
  QLineEdit *lastReadLineEdit;

  QLabel *propertyLabel;
  QCheckBox *isDirCheckBox;
  QCheckBox *isFileCheckBox;
  QCheckBox *isSymLinkCheckBox;
  QCheckBox *isHiddenCheckBox;
  QCheckBox *isReadableCheckBox;
  QCheckBox *isWritableCheckBox;
  QCheckBox *isExecutableCheckBox;

  QPushButton *getBtn;
};

#endif  // FILEINFO_H
