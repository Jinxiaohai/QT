#ifndef WIDGETACTION_H
#define WIDGETACTION_H

#include <QtCore/qglobal.h>
#include <QWidgetAction>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class WidgetAction : public QWidgetAction {
  Q_OBJECT

 public:
  explicit WidgetAction(QWidget *parent = nullptr);

 protected:
  QWidget *createWidget(QWidget *parent);

 signals:
  void getText(const QString &string);

 private slots:
  void sendText();

 private:
  QLineEdit *lineEdit;
};

#endif  // WIDGETACTION_H
