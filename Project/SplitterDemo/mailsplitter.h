#ifndef MAILSPLITTER_H
#define MAILSPLITTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QIcon;
class QSplitter;
class QTextEdit;
class QTreeWidget;
QT_END_NAMESPACE

class MailSplitter : public QMainWindow {
  Q_OBJECT

 public:
  MailSplitter(QWidget *parent = 0);
  ~MailSplitter();

 protected:
  void closeEvent(QCloseEvent *event);

 private:
  void addFolder(const QIcon &icon, const QString &name);
  void addMessage(const QString &subject, const QString &from, const QString &date);
  void readSettings();
  void writeSettings();

  QSplitter *mainSplitter;
  QSplitter *rightSplitter;
  QTreeWidget *foldersTreeWidget;
  QTreeWidget *messagesTreeWidget;
  QTextEdit *textEdit;
};

#endif  // MAILSPLITTER_H
