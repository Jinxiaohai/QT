#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QtCore/qglobal.h>
#include <QTableWidget>

class Cell;
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget {
  Q_OBJECT

 public:
  Spreadsheet(QWidget *parent = 0);

  bool autoRecalculate() const {}

 private:
  enum { MagicNumber = 0x7F51C883, RowCoutn = 999, ColumnCount = 26 };
};

#endif  // SPREADSHEET_H
