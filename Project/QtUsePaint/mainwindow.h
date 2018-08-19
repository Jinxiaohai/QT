#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QScrollArea;
class QComboBox;
QT_END_NAMESPACE

class PaintArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void doNew();
  void doOpen();
  bool doFileSave();
  bool doFileSaveAs();

  void createColorComboBox(QComboBox *comboBox);

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void on_action_N_triggered();

  void on_action_O_triggered();

  void on_action_S_triggered();

  void on_action_A_triggered();

  void on_action_X_triggered();

  void on_action_P_triggered();

  void on_action_4_triggered();

  void on_action_5_triggered();

  void on_action_6_triggered();

  void on_action_7_triggered();

  void on_action_8_triggered();

  void on_action_10_triggered();

  void on_action_11_triggered();

  void on_shapeComboBox_currentIndexChanged(const QString &arg1);

  void on_penStyleComboBox_currentIndexChanged(const QString &arg1);

  void on_penWidthSpinBox_valueChanged(int arg1);

  void on_penColorCombBox_currentIndexChanged(int index);

  void on_brushColorComboBox_currentIndexChanged(int index);

 private:
  Ui::MainWindow *ui;

  PaintArea *area;
  QScrollArea *scrollArea;

  bool isSaved;
  QString curFile;
  bool maybeSave();

  bool saveFile(QString fileName);
};

#endif  // MAINWINDOW_H
