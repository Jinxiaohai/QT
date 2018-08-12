#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QImage;
class QLabel;
class QMenu;
class QMenuBar;
class QAction;
class QComboBox;
class QSpinBox;
class QToolBar;
class QFontComboBox;
class QToolButton;
class QTextCharFormat;
class QActionGroup;

QT_END_NAMESPACE

class ShowWidget;

class ImageProcessor : public QMainWindow {
  Q_OBJECT

 public:
  ImageProcessor(QWidget *parent = 0);
  ~ImageProcessor();

  void createActions();
  void createMenus();
  void createToolBars();

  void loadFile(QString fileName);
  void mergeFormat(QTextCharFormat);

 protected slots:
  void showNewFile();
  void showOpenFile();
  void showPrintText();
  void showPrintImage();
  void showZoomIn();
  void showZoomOut();
  void showRotate90();
  void showRotate180();
  void showRotate270();
  void showMirrorVertical();
  void showMirrorHorizontal();

  void showFontComboBox(QString comboStr);
  void showSizeSpinBox(QString spinValue);
  void showBoldBtn();
  void showItalicBtn();
  void showUnderlineBtn();
  void showColorBtn();
  void showCurrentFormatChanged(const QTextCharFormat &fmt);

  void showList(int);
  void showAlignment(QAction *act);
  void showCursorPositionChanged();

 private:
  /// menu
  QMenu *fileMenu;
  QMenu *zoomMenu;
  QMenu *rotateMenu;
  QMenu *mirrorMenu;

  QImage img;
  QString fileName;
  ShowWidget *showWidget;

  /// file
  QAction *openFileAction;
  QAction *newFileAction;
  QAction *printTextAction;
  QAction *printImageAction;
  QAction *exitAction;

  /// edit
  QAction *copyAction;
  QAction *cutAction;
  QAction *pasteAction;
  QAction *aboutAction;
  QAction *zoomInAction;
  QAction *zoomOutAction;

  /// rotate
  QAction *rotate90Action;
  QAction *rotate180Action;
  QAction *rotate270Action;

  /// mirror
  QAction *mirrorVerticalAction;
  QAction *mirrorHirizontalAction;

  /// undo and redo
  QAction *undoAction;
  QAction *redoAction;

  /// ToolBar
  QToolBar *fileTool;
  QToolBar *zoomTool;
  QToolBar *rotateTool;
  QToolBar *mirrorTool;

  QToolBar *doToolBar;

  QLabel *fontLabel1;
  QFontComboBox *fontComboBox;
  QLabel *fontLabel2;
  QComboBox *sizeComboBox;
  QToolButton *boldBtn;
  QToolButton *italicBtn;
  QToolButton *underlineBtn;
  QToolButton *colorBtn;

  QToolBar *fontToolBar;

  QLabel *listLabel;
  QComboBox *listComboBox;
  QActionGroup *actGrp;
  QAction *leftAction;
  QAction *rightAction;
  QAction *centerAction;
  QAction *justifyAction;

  QToolBar *listToolBar;
};

#endif  // IMAGEPROCESSOR_H
