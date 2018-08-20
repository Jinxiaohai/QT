/*!
  \file   flowchartsymbolpicker.h
  \author jinxiaohai <xiaohaijin@outlook.com>
  \date   Sun Aug 19 22:25:06 2018
  
  \brief  该练习主要用来学习QListWidget类.
    
*/

#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QDialog>
#include <QMap>

/*! 前向声明 */
QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QIcon;
class QListWidget;
QT_END_NAMESPACE

/*!  */
class FlowChartSymbolPicker : public QDialog {
  Q_OBJECT

 public:
  FlowChartSymbolPicker(const QMap<int, QString> &symbolMap,
                        QWidget *parent = 0);
  ~FlowChartSymbolPicker();

  int selectedId() const;
  void done(int result);

 private:
  QIcon iconForSymbol(const QString &symbolName);

  QListWidget *listWidget;
  QDialogButtonBox *buttonBox;
  int id;
};

#endif  // FLOWCHARTSYMBOLPICKER_H
