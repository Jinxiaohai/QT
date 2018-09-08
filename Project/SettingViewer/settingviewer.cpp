#include <QHeaderView>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDialogButtonBox>
#include <QSettings>

#include "settingviewer.h"

/*!
  \brief 该函数用来初始化界面
  \param parent
*/
SettingViewer::SettingViewer(QWidget *parent) : QDialog(parent) {
  organization = "Trolltech"; /*!< 公司名称 */
  application = "Designer";   /*!< 软件名称 */

  treeWidget = new QTreeWidget;
  treeWidget->setColumnCount(2); /*!< 设为两列 */
  treeWidget->setHeaderLabels(QStringList() << tr("Key") << tr("Value")); /*!< 添加头 */
  treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
  treeWidget->header()->setSectionResizeMode(1, QHeaderView::Stretch);

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Close);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(open()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(treeWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);

  setWindowTitle(tr("Settings Viewer"));
  readSettings();
}

SettingViewer::~SettingViewer() {}

void SettingViewer::open() {
  QDialog dialog(this);
  QLabel *orgLabel = new QLabel(tr("&Organization:"));
  QLineEdit *orgLineEdit = new QLineEdit(organization);
  orgLabel->setBuddy(orgLineEdit);

  QLabel *appLabel = new QLabel(tr("&Application:"));
  QLineEdit *appLineEdit = new QLineEdit(application);
  appLabel->setBuddy(appLineEdit);

  QDialogButtonBox *buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(orgLabel, 0, 0);
  gridLayout->addWidget(orgLineEdit, 0, 1);
  gridLayout->addWidget(appLabel, 1, 0);
  gridLayout->addWidget(appLineEdit, 1, 1);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(gridLayout);
  mainLayout->addWidget(buttonBox);
  dialog.setLayout(mainLayout);

  dialog.setWindowTitle(tr("Choose Settings"));

  if (dialog.exec()) {
    organization = orgLineEdit->text();
    application = appLineEdit->text();
    readSettings();
  }
}

void SettingViewer::readSettings() {
  /*! organization name and application name */
  QSettings settints(organization, application);
  treeWidget->clear();
  addChildSettings(settints, 0, "");

  treeWidget->sortByColumn(0);
  treeWidget->setFocus();
  setWindowTitle(tr("Setting Viewer - %1 by %2").arg(application).arg(organization));
}

void SettingViewer::addChildSettings(QSettings &settings, QTreeWidgetItem *parent,
                                     const QString &group) {
  if (!parent) {
    parent = treeWidget->invisibleRootItem();
  }
  QTreeWidgetItem *item;

  settings.beginGroup(group);
  foreach(QString key, settings.childKeys()) {
    item = new QTreeWidgetItem(parent);
    item->setText(0, key);
    item->setText(1, settings.value(key).toString());
  }

  foreach(QString group, settings.childGroups()) {
    item = new QTreeWidgetItem(parent);
    item->setText(0, group);
    addChildSettings(settings, item, group);
  }

  settings.endGroup();
}
