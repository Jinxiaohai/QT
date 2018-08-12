#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
QT_END_MOC_NAMESPACE

class FindDialog;
class Spreadsheet;

class mainwindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit mainwindow(QWidget *parent = nullptr);

 signals:

 protected:
  void closeEvent(QCloseEvent *event);

  /// menu slots
 private slots:
  void newFile();
  void open();
  void save();
  void saveAs();
  void find();
  void goToCell();
  void sort();
  void about();
  void openRecentFile();
  void updateStatusBar();
  void spreadsheetModified();

  /// create UI
 private:
  void createActions();
  void createMenus();
  void createContextMenu();
  void createToolBars();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool okToContinue();
  bool loadFile(const QString &fileName);
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  void updateRecentFileActions();
  QString strippedName(const QString &fullFileName);

  /// UI contents
  Spreadsheet *spreadsheet;
  FindDialog *findDialog;
  QLabel *locationLabel;
  QLabel *formulaLabel;
  QStringList recentFiles;
  QString curFile;

  enum { MaxRecentFiles = 5 };

  QAction *recentFileActions[MaxRecentFiles];
  QAction *separatorAction;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *selectSubMenu;
  QMenu *toolsMenu;
  QMenu *optionsMenu;
  QMenu *helpMenu;
  QToolBar *fileToolBar;
  QToolBar *edtiToolBar;

  QAction *newAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *saveAsAction;
  QAction *exitAction;
  QAction *cutAction;
  QAction *copyAction;
  QAction *pasteAction;
  QAction *deleteAction;
  QAction *selectRowAction;
  QAction *selectColumnAction;
  QAction *selectAllAction;
  QAction *findAction;
  QAction *goToCellAction;
  QAction *recalculateAction;
  QAction *sortAction;
  QAction *showGridAction;
  QAction *autoRecalcAction;
  QAction *aboutAction;
  QAction *aboutQtAction;
};

#endif  // MAINWINDOW_H
