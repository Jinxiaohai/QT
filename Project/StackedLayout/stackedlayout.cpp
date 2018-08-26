#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QStackedLayout>

#include "stackedlayout.h"

StackedLayout::StackedLayout(QWidget *parent) : QDialog(parent) {
  createAppearancePge();
  createWebBrowserPage();
  createMailAndNewsPage();
  createAdvancedPage();

  okPushButton = new QPushButton(tr("确定"));
  cancelPushButton = new QPushButton(tr("取消"));
  /*! clicked信号的相连 */
  connect(okPushButton, &QPushButton::clicked, this, &StackedLayout::accept);
  connect(cancelPushButton, &QPushButton::clicked, this, &StackedLayout::reject);
  QHBoxLayout *buttonsHBoxLayout = new QHBoxLayout;
  /*! 添加一个占据空白的伸缩弹簧 */
  buttonsHBoxLayout->addStretch();
  buttonsHBoxLayout->addWidget(okPushButton);
  buttonsHBoxLayout->addWidget(cancelPushButton);

  /*! QListWidget部件使用addItem进行项的添加 */
  listWidget = new QListWidget;
  listWidget->addItem(tr("外表"));
  listWidget->addItem(tr("浏览器"));
  listWidget->addItem(tr("邮件和新闻"));
  listWidget->addItem(tr("高级"));

  stackedLayout = new QStackedLayout;
  stackedLayout->addWidget(appearancePage);
  stackedLayout->addWidget(webBrowerPage);
  stackedLayout->addWidget(mailAndNewsPage);
  stackedLayout->addWidget(advancedPage);
  /*! 将QListWidget的当前项和QStackedLayout需要展示的页面进行相联系 */
  connect(listWidget, &QListWidget::currentRowChanged, stackedLayout, &QStackedLayout::setCurrentIndex);

  QGridLayout *mainLayout = new QGridLayout;
  /*! 设置第一列的伸缩强度宽1，设置第二列的伸缩强度宽为3. 实际的效果是两列的跨度为1：3 */
  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(1, 3);
  mainLayout->addWidget(listWidget, 0, 0);
  mainLayout->addLayout(stackedLayout, 0, 1);
  mainLayout->addLayout(buttonsHBoxLayout, 1, 0, 1, 2);
  this->setLayout(mainLayout);
 
  this->resize(800, 600);
  this->setWindowTitle(tr("堆叠布局"));
  /*! 将第一个页面作为缺省的页面 */
  listWidget->setCurrentRow(0);
}

StackedLayout::~StackedLayout() {}

void StackedLayout::createAppearancePge() {
  appearancePage = new QWidget;

  /*! 创建一个组合的框，用来安放其它的部件。 */
  openGroupBox = new QGroupBox(tr("打开初始化"));
  webBrowserCheckBox = new QCheckBox(tr("网络浏览器"));
  mailEditorCheckBox = new QCheckBox(tr("邮件编辑器"));
  newsGroupCheckBox = new QCheckBox(tr("新闻组"));

  toolbarsGroupBox = new QGroupBox(tr("显示工具栏"));
  picturesAndTextRadioButton = new QRadioButton(tr("图片和文字"));
  picturesOnlyRadioButton = new QRadioButton(tr("只有图片"));
  textOnlyRadioButton = new QRadioButton(tr("只有文字"));

  tooltipsCheckBox = new QCheckBox(tr("显示工具提示"));
  webSizeIconsCheckBox = new QCheckBox(tr("显示工具图标"));
  resizeImagesCheckBox = new QCheckBox(tr("重设图片的大小以适配窗口"));

  QVBoxLayout *openLayout = new QVBoxLayout;
  openLayout->addWidget(webBrowserCheckBox);
  openLayout->addWidget(mailEditorCheckBox);
  openLayout->addWidget(newsGroupCheckBox);
  /*! 将该布局安装到需要安装的部件中 */
  openGroupBox->setLayout(openLayout);

  QVBoxLayout *toolbarsLayout = new QVBoxLayout;
  toolbarsLayout->addWidget(picturesAndTextRadioButton);
  toolbarsLayout->addWidget(picturesOnlyRadioButton);
  toolbarsLayout->addWidget(textOnlyRadioButton);
  toolbarsGroupBox->setLayout(toolbarsLayout);

  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(openGroupBox);
  pageLayout->addWidget(toolbarsGroupBox);
  pageLayout->addWidget(tooltipsCheckBox);
  pageLayout->addWidget(webSizeIconsCheckBox);
  pageLayout->addWidget(resizeImagesCheckBox);
  pageLayout->addStretch();
  appearancePage->setLayout(pageLayout);

  /*! 将QCheckBox对象和QRadioButton进行选中 */
  webBrowserCheckBox->setChecked(true);
  mailEditorCheckBox->setChecked(true);
  picturesAndTextRadioButton->setChecked(true);
  tooltipsCheckBox->setChecked(true);
  webSizeIconsCheckBox->setChecked(true);
}

void StackedLayout::createWebBrowserPage() {
  webBrowerPage = new QWidget;

  displayGroupBox = new QGroupBox(tr("展示"));
  blankRadioButton = new QRadioButton(tr("空白页"));
  homeRadioButton = new QRadioButton(tr("空白页"));
  lastRadioButton = new QRadioButton(tr("最后访问的页面"));

  homeGroupBox = new QGroupBox(tr("主页："));
  locationLabel = new QLabel(tr("网址："));
  locationLineEdit = new QLineEdit;

  webButtonsGroupBox = new QGroupBox(tr("选择要在工具栏展示的按钮"));
  bookmarksCheckBox = new QCheckBox(tr("书签"));
  goCheckBox = new QCheckBox(tr("前往"));
  homeCheckBox = new QCheckBox(tr("主页"));
  searchCheckBox = new QCheckBox(tr("搜索"));
  printCheckBox = new QCheckBox(tr("打印"));

  QVBoxLayout *displayLayout = new QVBoxLayout;
  displayLayout->addWidget(blankRadioButton);
  displayLayout->addWidget(homeRadioButton);
  displayLayout->addWidget(lastRadioButton);
  displayGroupBox->setLayout(displayLayout);

  QHBoxLayout *homeLayout = new QHBoxLayout;
  homeLayout->addWidget(locationLabel);
  homeLayout->addWidget(locationLineEdit);
  homeGroupBox->setLayout(homeLayout);

  QGridLayout *webButtonsLayout = new QGridLayout;
  webButtonsLayout->addWidget(bookmarksCheckBox, 0, 0);
  webButtonsLayout->addWidget(goCheckBox, 1, 0);
  webButtonsLayout->addWidget(homeCheckBox, 2, 0);
  webButtonsLayout->addWidget(searchCheckBox, 0, 1);
  webButtonsLayout->addWidget(printCheckBox, 1, 1);
  webButtonsGroupBox->setLayout(webButtonsLayout);

  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(displayGroupBox);
  pageLayout->addWidget(homeGroupBox);
  pageLayout->addWidget(webButtonsGroupBox);
  pageLayout->addStretch();
  webBrowerPage->setLayout(pageLayout);

  homeRadioButton->setChecked(true);
  locationLineEdit->setText(tr("https://www.jinxiaohai.cn"));
  bookmarksCheckBox->setChecked(true);
  homeCheckBox->setChecked(true);
  searchCheckBox->setChecked(true);
  printCheckBox->setChecked(true);
}

void StackedLayout::createMailAndNewsPage() {
  mailAndNewsPage = new QWidget;
  generalGroupBox = new QGroupBox(tr("通用设置"));
  confirmCheckBox = new QCheckBox(tr("删除文件时进行警告"));
  rememberCheckBox = new QCheckBox(tr("记住最后选择的文件"));

  mailButtonsGroupBox = new QGroupBox(tr("选择要在工具栏展示的按钮"));
  fileCheckBox = new QCheckBox(tr("文件"));
  nextCheckBox = new QCheckBox(tr("下一个"));
  stopCheckBox = new QCheckBox(tr("停止"));
  junkCheckBox = new QCheckBox(tr("跳过"));

  QVBoxLayout *generalLayout = new QVBoxLayout;
  generalLayout->addWidget(confirmCheckBox);
  generalLayout->addWidget(rememberCheckBox);
  generalGroupBox->setLayout(generalLayout);

  QGridLayout *mailButtonsLayout = new QGridLayout;
  mailButtonsLayout->addWidget(fileCheckBox, 0, 0);
  mailButtonsLayout->addWidget(nextCheckBox, 1, 0);
  mailButtonsLayout->addWidget(stopCheckBox, 0, 1);
  mailButtonsLayout->addWidget(junkCheckBox, 1, 1);
  mailButtonsGroupBox->setLayout(mailButtonsLayout);

  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(generalGroupBox);
  pageLayout->addWidget(mailButtonsGroupBox);
  pageLayout->addStretch();
  mailAndNewsPage->setLayout(pageLayout);

  confirmCheckBox->setChecked(true);
  rememberCheckBox->setChecked(true);
  nextCheckBox->setChecked(true);
  junkCheckBox->setChecked(true);
}

void StackedLayout::createAdvancedPage() {
  advancedPage = new QWidget;

  featuresGroupBox = new QGroupBox(tr("特征"));
  javaCheckBox = new QCheckBox(tr("激活Java"));
  ftpCheckBox = new QCheckBox(tr("使用邮箱作为匿名FTP:"));
  ftpLineEdit = new QLineEdit;

  /*! QCheckbox的勾选使用的是toggled信号进行发射。 */
  connect(ftpCheckBox, &QCheckBox::toggled, ftpLineEdit, &QLineEdit::setEnabled);

  QGridLayout *featuresLayout = new QGridLayout;
  featuresLayout->addWidget(javaCheckBox, 0, 0, 1, 2);
  featuresLayout->addWidget(ftpCheckBox, 1, 0, 1, 2);
  featuresLayout->addWidget(ftpLineEdit, 2, 1);
  featuresGroupBox->setLayout(featuresLayout);

  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(featuresGroupBox);
  pageLayout->addStretch();
  advancedPage->setLayout(pageLayout);

  javaCheckBox->setChecked(true);
  ftpLineEdit->setEnabled(false);
}
