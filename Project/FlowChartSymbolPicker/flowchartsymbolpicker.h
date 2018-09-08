#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QIcon;
class QListWidget;
QT_END_NAMESPACE

class FlowChartSymbolPicker : public QDialog {
  Q_OBJECT

 public:
  FlowChartSymbolPicker(const QMap<int, QString> &symbolMap, QWidget *parent = 0);
  ~FlowChartSymbolPicker();

  int selectedId() const;
  void done(int result);

 private:
  QIcon iconForSymbol(const QString &symbolMap);

  QListWidget *listWidget;
  QDialogButtonBox *buttonBox;
  int id;
};

#endif  // FLOWCHARTSYMBOLPICKER_H
