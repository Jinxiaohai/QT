#include <QGroupBox>
#include <QToolButton>
#include <QVBoxLayout>

#include "QssStyle.h"
#include "drawer.h"

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f) : QToolBox(parent, f) {
  //  QssStyle::setStyle(":/myqss.qss");
  this->setWindowTitle(tr("ToolBox example"));

  QPixmap iconHead(":/images/userInfo.png");

  toolBtn1_1 = new QToolButton;
  toolBtn1_1->setText(tr("Xiaohai"));
  toolBtn1_1->setIcon(iconHead);
  toolBtn1_1->setIconSize(iconHead.size());
  toolBtn1_1->setAutoRaise(true);
  toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  connect(toolBtn1_1, SIGNAL(clicked()), this, SLOT(close()));

  toolBtn1_2 = new QToolButton;
  toolBtn1_2->setText(tr("Jin"));
  toolBtn1_2->setIcon(iconHead);
  toolBtn1_2->setIconSize(iconHead.size());
  toolBtn1_2->setAutoRaise(true);
  toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  toolBtn1_3 = new QToolButton;
  toolBtn1_3->setText(tr("Wangqiuyu"));
  toolBtn1_3->setIcon(iconHead);
  toolBtn1_3->setIconSize(iconHead.size());
  toolBtn1_3->setAutoRaise(true);
  toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  toolBtn1_4 = new QToolButton;
  toolBtn1_4->setText(tr("xiaopangzi"));
  toolBtn1_4->setIcon(iconHead);
  toolBtn1_4->setIconSize(iconHead.size());
  toolBtn1_4->setAutoRaise(true);
  toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  toolBtn1_5 = new QToolButton;
  toolBtn1_5->setText(tr("hirg"));
  toolBtn1_5->setIcon(iconHead);
  toolBtn1_5->setIconSize(iconHead.size());
  toolBtn1_5->setAutoRaise(true);
  toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  QGroupBox *groupBox1 = new QGroupBox;
  QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);
  layout1->setMargin(10);
  layout1->setAlignment(Qt::AlignHCenter);
  layout1->addWidget(toolBtn1_1);
  layout1->addWidget(toolBtn1_2);
  layout1->addWidget(toolBtn1_3);
  layout1->addWidget(toolBtn1_4);
  layout1->addWidget(toolBtn1_5);

  /// insert a stretch
  layout1->addStretch();

  toolBtn2_1 = new QToolButton;
  toolBtn2_1->setText(tr("Xiaohai"));
  toolBtn2_1->setIcon(iconHead);
  toolBtn2_1->setIconSize(iconHead.size());
  toolBtn2_1->setAutoRaise(true);
  toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  toolBtn2_2 = new QToolButton;
  toolBtn2_2->setText(tr("Xiaohai"));
  toolBtn2_2->setIcon(iconHead);
  toolBtn2_2->setIconSize(iconHead.size());
  toolBtn2_2->setAutoRaise(true);
  toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  QGroupBox *groupBox2 = new QGroupBox;
  QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
  layout2->setMargin(10);
  layout2->setAlignment(Qt::AlignHCenter);
  layout2->addWidget(toolBtn2_1);
  layout2->addWidget(toolBtn2_2);

  toolBtn3_1 = new QToolButton;
  toolBtn3_1->setText(tr("Xiaohai"));
  toolBtn3_1->setIcon(iconHead);
  toolBtn3_1->setIconSize(iconHead.size());
  toolBtn3_1->setAutoRaise(true);
  toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  toolBtn3_2 = new QToolButton;
  toolBtn3_2->setText(tr("Xiaohai"));
  toolBtn3_2->setIcon(iconHead);
  toolBtn3_2->setIconSize(iconHead.size());
  toolBtn3_2->setAutoRaise(true);
  toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  QGroupBox *groupBox3 = new QGroupBox;
  QVBoxLayout *layout3 = new QVBoxLayout(groupBox3);
  layout3->setMargin(10);
  layout3->setAlignment(Qt::AlignHCenter);
  layout3->addWidget(toolBtn3_1);
  layout3->addWidget(toolBtn3_2);

  this->addItem(groupBox1, tr("Friends"));
  this->addItem(groupBox2, tr("Strangers"));
  this->addItem(groupBox3, tr("Others"));

  resize(300, height());
}
