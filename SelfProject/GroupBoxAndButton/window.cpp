#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QMenu>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include "QssStyle.h"
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  /// 使用样式表
  QssStyle::setStyle(tr(":/qss/myqss.qss"));
  /// 创建总体布局并添加部件--组合框
  QGridLayout *grid = new QGridLayout;
  /// 第一个参数是部件指针
  grid->addWidget(createFirstExclusiveGroup(), 0, 0);
  grid->addWidget(createSecondExclusiveGroup(), 1, 0);
  grid->addWidget(createNonExclusiveGroup(), 0, 1);
  grid->addWidget(createPushButtonGroup(), 1, 1);
  setLayout(grid);
  setWindowTitle(tr("Group Boxes"));
  setFixedSize(480, 320);
}

QGroupBox *Window::createFirstExclusiveGroup() {
  /// 创建组合框(左上角的)
  QGroupBox *groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));

  QRadioButton *radio1 = new QRadioButton(tr("&Radio Button 1"));
  QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
  QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));
  /// 使radio1处于选中的状态
  radio1->setChecked(true);

  /// 创建组合框的内部布局
  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(radio1);
  vbox->addWidget(radio2);
  vbox->addWidget(radio3);
  /// 添加空白，把所有的三个部件给顶上去。
  vbox->addStretch(1);
  groupBox->setLayout(vbox);

  return groupBox;
}

QGroupBox *Window::createSecondExclusiveGroup() {
  QGroupBox *groupBox = new QGroupBox(tr("E&xclusive Radio Buttons"));
  /// 可以被复选的
  groupBox->setCheckable(true);
  /// 但是又没有选中的
  groupBox->setChecked(false);

  QRadioButton *radio1 = new QRadioButton(tr("Rad&io button 1"));
  QRadioButton *radio2 = new QRadioButton(tr("Radi&o button 2"));
  QRadioButton *radio3 = new QRadioButton(tr("Radio &button 3"));
  radio1->setChecked(true);
  QCheckBox *checkBox = new QCheckBox(tr("Ind&ependent checkbox"));
  checkBox->setChecked(true);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(radio1);
  vbox->addWidget(radio2);
  vbox->addWidget(radio3);
  vbox->addWidget(checkBox);
  vbox->addStretch(1);
  groupBox->setLayout(vbox);

  return groupBox;
}

QGroupBox *Window::createNonExclusiveGroup() {
  QGroupBox *groupBox = new QGroupBox(tr("Non-Exclusive Checkboxes"));
  /// 隐藏垂直边框
  groupBox->setFlat(true);

  QCheckBox *checkBox1 = new QCheckBox(tr("&Checkbox 1"));
  QCheckBox *checkBox2 = new QCheckBox(tr("C&heckbox 2"));
  checkBox2->setChecked(true);
  QCheckBox *tristateBox = new QCheckBox(tr("Tri-&state button"));
  /// 打开checkbox的三种状态，默认只有两种状态。
  tristateBox->setTristate(true);
  /// 设定checkbox的check状态。
  tristateBox->setCheckState(Qt::PartiallyChecked);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(checkBox1);
  vbox->addWidget(checkBox2);
  vbox->addWidget(tristateBox);
  vbox->addStretch(1);
  groupBox->setLayout(vbox);

  return groupBox;
}

QGroupBox *Window::createPushButtonGroup() {
  QGroupBox *groupBox = new QGroupBox(tr("&Push Buttons"));
  groupBox->setCheckable(true);
  groupBox->setChecked(true);

  QPushButton *pushButton = new QPushButton(tr("&Normal Button"));
  QPushButton *toggleButton = new QPushButton(tr("&Toggle Button"));
  /// 设置为只有开和关两种状态。
  toggleButton->setCheckable(true);
  toggleButton->setChecked(true);
  QPushButton *flatButton = new QPushButton(tr("&Flat Button"));
  /// 去掉垂直边框。
  flatButton->setFlat(true);

  QPushButton *popupButton = new QPushButton(tr("Pop&up Button"));
  /// 创建一个menu.
  QMenu *menu = new QMenu(this);
  /// 添加动作.
  menu->addAction(tr("&First Item"));
  menu->addAction(tr("&Second Item"));
  menu->addAction(tr("Third item"));
  menu->addAction(tr("Fourth Item"));
  /// 为部件设定menu.
  popupButton->setMenu(menu);

  QAction *newAction = menu->addAction(tr("Submenu"));
  QMenu *subMenu = new QMenu(tr("Popop Submenu"));
  subMenu->addAction(tr("Item 1"));
  subMenu->addAction(tr("Item 2"));
  subMenu->addAction(tr("Item 3"));
  /// 为action添加menu.
  newAction->setMenu(subMenu);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(pushButton);
  vbox->addWidget(toggleButton);
  vbox->addWidget(flatButton);
  vbox->addWidget(popupButton);
  vbox->addStretch(1);
  groupBox->setLayout(vbox);

  return groupBox;
}
