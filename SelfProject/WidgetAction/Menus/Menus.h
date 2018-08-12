#ifndef Menus_H
#define Menus_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE

class Menus : public QMainWindow {
  Q_OBJECT

 public:
  explicit Menus(QWidget *parent = 0);
  ~Menus();

 public slots:
  /// menu file
  void fileOpen();
  void fileSave();

  /// menu edit
  void editNormal();
  void editBold();
  void editUnderline();

  /// menu edit
  void editAdvancedFont();
  void editAdvancedStyle();
  void editAdvancedUnderline();

  /// menu help
  void helpAbout();
  void helpAboutQt();

 private:
  void createFileMenu();
  void createEditMenu();
  void createHelpMenu();

  QTextEdit *m_editor;
};

#endif  // Menus_H
