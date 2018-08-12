#include <QApplication>

#include <window.h>


int main(int argc, char **argv) {
  ///
  ///
  /// \param argc
  /// \param argv
  ///
  /// \return
  ///
  QApplication app(argc, argv);

  ///
  Window w;
  w.show();

  ///
  return app.exec();
}
