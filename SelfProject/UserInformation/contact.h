#ifndef CONTACT_H
#define CONTACT_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
class Contact : public QWidget {
  Q_OBJECT
 public:
  explicit Contact(QWidget *parent = 0);

 signals:

 public slots:
 private:
  QLabel *EmailLabel;
  QLineEdit *EmailLineEdit;
  QLabel *AddrLabel;
  QLineEdit *AddrLineEdit;
  QLabel *CodeLabel;
  QLineEdit *CodeLineEdit;
  QLabel *MoviTelLabel;
  QLineEdit *MoviTelLineEdit;
  QCheckBox *MoviTelCheckBook;
  QLabel *ProTelLabel;
  QLineEdit *ProTelLineEdit;
  QGridLayout *mainLayout;
};

#endif  // CONTACT_H
