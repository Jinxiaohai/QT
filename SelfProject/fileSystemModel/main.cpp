#include <QApplication>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFileSystemModel model;
  model.setRootPath(QDir::currentPath());

  QTreeView treeView;
  treeView.setModel(&model);
  treeView.setRootIndex(model.index(QDir::currentPath()));

  QListView listView;
  listView.setModel(&model);
  listView.setRootIndex(model.index(QDir::currentPath()));

  treeView.setWindowTitle(QObject::tr("treeView"));
  treeView.show();
  listView.setWindowTitle(QObject::tr("listView"));
  listView.show();

  return a.exec();
}
