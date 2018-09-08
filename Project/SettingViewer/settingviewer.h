#ifndef SETTINGVIEWER_H
#define SETTINGVIEWER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QSettings;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class SettingViewer : public QDialog {
  Q_OBJECT

 public:
  SettingViewer(QWidget *parent = 0);
  ~SettingViewer();

 private
slots:
  void open();

 private:
  void readSettings();
  void addChildSettings(QSettings &settings, QTreeWidgetItem *item, const QString &group);

  QTreeWidget *treeWidget;
  QDialogButtonBox *buttonBox;

  QString organization;
  QString application;
};

#endif  // SETTINGVIEWER_H
