#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
/// 添加一个组合框按钮
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
/// list形状的widget
class QListWidget;
class QRadioButton;
/// 层叠式的布局
class QStackedLayout;
QT_END_NAMESPACE

class PreferenceDialog : public QDialog {
  Q_OBJECT

 public:
  PreferenceDialog(QWidget *parent = 0);
  ~PreferenceDialog();

 private:
  /// 创建四个主要的page.
  void createAppearancePage();
  void createWebBrowserPage();
  void createMailAndNewsPage();
  void createAdvancedPage();

  /// 右边和左边的布局部件
  QStackedLayout *stackedLayout;
  QListWidget *listWidget;

  /// 四个主页的名字
  QWidget *appearancePage;
  QWidget *webBrowserPage;
  QWidget *mailAndNewsPage;
  QWidget *advancedPage;

  /// 左下方的按钮部件
  QDialogButtonBox *buttonBox;

  /// 第一个主页
  QGroupBox *openGroupBox;
  QCheckBox *webBrowserCheckBox;
  QCheckBox *mailEditorCheckBox;
  QCheckBox *newsgroupCheckBox;
  QGroupBox *toolbarsGroupBox;
  QRadioButton *picturesAndTextRadioButton;
  QRadioButton *picturesOnlyRadioButton;
  QRadioButton *textOnlyRadioButton;
  QCheckBox *tooltipsCheckBox;
  QCheckBox *webSiteIconsCheckBox;
  QCheckBox *resizeImagesCheckBox;

  /// 第二个主页
  QGroupBox *displayGroupBox;
  QRadioButton *blankRadioButton;
  QRadioButton *homeRadioButton;
  QRadioButton *lastRadioButton;
  QGroupBox *homeGroupBox;
  QLabel *locationLabel;
  QLineEdit *locationLineEdit;
  QGroupBox *webButtonsGroupBox;
  QCheckBox *bookmarksCheckBox;
  QCheckBox *goCheckBox;
  QCheckBox *homeCheckBox;
  QCheckBox *searchCheckBox;
  QCheckBox *printCheckBox;

  /// 第三个主页
  QGroupBox *generalGroupBox;
  QCheckBox *confirmCheckBox;
  QCheckBox *rememberCheckBox;
  QGroupBox *mailButtonsGroupBox;
  QCheckBox *fileCheckBox;
  QCheckBox *nextCheckBox;
  QCheckBox *stopCheckBox;
  QCheckBox *junkCheckBox;

  /// 第四个主页
  QGroupBox *featuresGroupBox;
  QCheckBox *javaCheckBox;
  QCheckBox *ftpCheckBox;
  QLineEdit *ftpLineEdit;
};

#endif  // PREFERENCEDIALOG_H
