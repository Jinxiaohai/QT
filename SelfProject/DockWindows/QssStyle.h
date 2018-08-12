#include <QFile>
#include <QApplication>

class QssStyle
{
public:
  static void setStyle(const QString &style) {
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
  }
};
