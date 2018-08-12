#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QStackedLayout>

#include "preferencedialog.h"

PreferenceDialog::PreferenceDialog(QWidget *parent) : QDialog(parent) {
/// @{
  /// 创建组合页
  createAppearancePage();
  createWebBrowserPage();
  createMailAndNewsPage();
  createAdvancedPage();
/// @}
  
  buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  /// 左边的布局内容
  listWidget = new QListWidget;
  listWidget->addItem(tr("Appearance"));
  listWidget->addItem(tr("Web Browser"));
  listWidget->addItem(tr("Mail & News"));
  listWidget->addItem(tr("Advanced"));

  /// 右边的布局内容
  stackedLayout = new QStackedLayout;
  stackedLayout->addWidget(appearancePage);
  stackedLayout->addWidget(webBrowserPage);
  stackedLayout->addWidget(mailAndNewsPage);
  stackedLayout->addWidget(advancedPage);
  connect(listWidget, SIGNAL(currentRowChanged(int)), stackedLayout,
          SLOT(setCurrentIndex(int)));

  /// 总的布局
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(1, 3);
  mainLayout->addWidget(listWidget, 0, 0);
  mainLayout->addLayout(stackedLayout, 0, 1);
  mainLayout->addWidget(buttonBox, 1, 0, 1, 2);
  this->setLayout(mainLayout);

  /// 连接信号和槽
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  this->setWindowTitle(tr("Preference Dialog"));
  listWidget->setCurrentRow(0);
}

PreferenceDialog::~PreferenceDialog() {}

void PreferenceDialog::createAppearancePage() {
  /// main page
  appearancePage = new QWidget;

  /// create contents
  openGroupBox = new QGroupBox(tr("Open at startup"));
  webBrowserCheckBox = new QCheckBox(tr("Web browser"));
  mailEditorCheckBox = new QCheckBox(tr("Mail editor"));
  newsgroupCheckBox = new QCheckBox(tr("Newsgroups"));

  toolbarsGroupBox = new QGroupBox(tr("Show toolbars as"));
  picturesAndTextRadioButton = new QRadioButton(tr("Pictures and text"));
  picturesOnlyRadioButton = new QRadioButton(tr("Pictures only"));
  textOnlyRadioButton = new QRadioButton(tr("Text only"));

  tooltipsCheckBox = new QCheckBox(tr("Show tooltips"));
  webSiteIconsCheckBox = new QCheckBox(tr("Show web site icons"));
  resizeImagesCheckBox =
      new QCheckBox(tr("Resize large images to fit in the window"));

  /// layout 1
  QVBoxLayout *openLayout = new QVBoxLayout;
  openLayout->addWidget(webBrowserCheckBox);
  openLayout->addWidget(mailEditorCheckBox);
  openLayout->addWidget(newsgroupCheckBox);
  openGroupBox->setLayout(openLayout);

  /// layout 2
  QVBoxLayout *toolbarsLayout = new QVBoxLayout;
  toolbarsLayout->addWidget(picturesAndTextRadioButton);
  toolbarsLayout->addWidget(picturesOnlyRadioButton);
  toolbarsLayout->addWidget(textOnlyRadioButton);
  toolbarsGroupBox->setLayout(toolbarsLayout);

  /// main layout
  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(openGroupBox);
  pageLayout->addWidget(toolbarsGroupBox);
  pageLayout->addWidget(tooltipsCheckBox);
  pageLayout->addWidget(webSiteIconsCheckBox);
  pageLayout->addWidget(resizeImagesCheckBox);
  pageLayout->addStretch();
  appearancePage->setLayout(pageLayout);

  /// set status
  webBrowserCheckBox->setChecked(true);
  mailEditorCheckBox->setChecked(true);
  picturesAndTextRadioButton->setChecked(true);
  tooltipsCheckBox->setChecked(true);
  webSiteIconsCheckBox->setChecked(true);
}

void PreferenceDialog::createWebBrowserPage() {
  /// page widget
  webBrowserPage = new QWidget;

  /// create contents
  displayGroupBox = new QGroupBox(tr("Display on startup"));
  blankRadioButton = new QRadioButton(tr("Blank page"));
  homeRadioButton = new QRadioButton(tr("Home page"));
  lastRadioButton = new QRadioButton(tr("Lat page visited"));

  homeGroupBox = new QGroupBox(tr("Home Page"));
  locationLabel = new QLabel(tr("Location"));
  locationLineEdit = new QLineEdit;

  webButtonsGroupBox =
      new QGroupBox(tr("Select the buttons you want in the toolbar"));
  bookmarksCheckBox = new QCheckBox(tr("Bookmarks"));
  goCheckBox = new QCheckBox(tr("Go"));
  homeCheckBox = new QCheckBox(tr("Home"));
  searchCheckBox = new QCheckBox(tr("Search"));
  printCheckBox = new QCheckBox(tr("Print"));

  /// layout 1
  QVBoxLayout *displayLayout = new QVBoxLayout;
  displayLayout->addWidget(blankRadioButton);
  displayLayout->addWidget(homeRadioButton);
  displayLayout->addWidget(lastRadioButton);
  displayGroupBox->setLayout(displayLayout);

  /// layout 2
  QHBoxLayout *homeLayout = new QHBoxLayout;
  homeLayout->addWidget(locationLabel);
  homeLayout->addWidget(locationLineEdit);
  homeGroupBox->setLayout(homeLayout);

  /// layout 3
  QGridLayout *webButtonLayout = new QGridLayout;
  webButtonLayout->addWidget(bookmarksCheckBox, 0, 0);
  webButtonLayout->addWidget(goCheckBox, 1, 0);
  webButtonLayout->addWidget(homeCheckBox, 2, 0);
  webButtonLayout->addWidget(searchCheckBox, 0, 1);
  webButtonLayout->addWidget(printCheckBox, 1, 1);
  webButtonsGroupBox->setLayout(webButtonLayout);

  /// layout
  QVBoxLayout *pageLayout = new QVBoxLayout;
  pageLayout->setMargin(0);
  pageLayout->addWidget(displayGroupBox);
  pageLayout->addWidget(homeGroupBox);
  pageLayout->addWidget(webButtonsGroupBox);
  pageLayout->addStretch();
  webBrowserPage->setLayout(pageLayout);

  homeRadioButton->setChecked(true);
  locationLineEdit->setText("http://www.jinxiaohai.cn");
  bookmarksCheckBox->setChecked(true);
  homeCheckBox->setChecked(true);
  searchCheckBox->setChecked(true);
  printCheckBox->setChecked(true);
}

void PreferenceDialog::createMailAndNewsPage() {
  /// create page
  mailAndNewsPage = new QWidget;

  generalGroupBox = new QGroupBox(tr("General settings"));
  confirmCheckBox = new QCheckBox(tr("Warn when moving folders to the Trash"));
  rememberCheckBox = new QCheckBox(tr("Remember the last selected message"));

  mailButtonsGroupBox =
      new QGroupBox(tr("Select the buttons you want in the toolbar"));
  fileCheckBox = new QCheckBox(tr("File"));
  nextCheckBox = new QCheckBox(tr("Next"));
  stopCheckBox = new QCheckBox(tr("Stop"));
  junkCheckBox = new QCheckBox(tr("Junk"));

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

void PreferenceDialog::createAdvancedPage() {
  advancedPage = new QWidget;

  featuresGroupBox =
      new QGroupBox(tr("Features that help interpret web pages"));
  javaCheckBox = new QCheckBox(tr("Enable Java"));
  ftpCheckBox = new QCheckBox(tr("Use this e-mail address for anoymous FTP:"));

  ftpLineEdit = new QLineEdit;
  connect(ftpCheckBox, SIGNAL(toggled(bool)), ftpLineEdit,
          SLOT(setEnabled(bool)));
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
