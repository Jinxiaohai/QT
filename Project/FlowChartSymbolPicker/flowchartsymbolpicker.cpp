#include <QDebug>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidgetItem>
#include <QListWidget>
#include <QIcon>

#include "flowchartsymbolpicker.h"

/*!
 * \brief FlowChartSymbolPicker::FlowChartSymbolPicker
 * \param symbolMap a map include the id and text.
 * \param parent parent object
 */
FlowChartSymbolPicker::FlowChartSymbolPicker(const QMap<int, QString> &symbolMap,
                                             QWidget *parent)
    : QDialog(parent) {
  id = -1;
  listWidget = new QListWidget;
  //! set the icon size
  listWidget->setIconSize(QSize(60, 60));

  //! a java style iterator
  QMapIterator<int, QString> i(symbolMap);
  while (i.hasNext()) {
    i.next();
    QListWidgetItem *item = new QListWidgetItem(i.value(), listWidget);
    item->setIcon(iconForSymbol(i.value()));
    //! the data is the key number
    item->setData(Qt::UserRole, i.key());
  }

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(listWidget);
  mainLayout->addWidget(buttonBox);

  setLayout(mainLayout);
  setWindowTitle(tr("FlowChart Symbol Picker"));
}

FlowChartSymbolPicker::~FlowChartSymbolPicker() {}

int FlowChartSymbolPicker::selectedId() const { return id; }

void FlowChartSymbolPicker::done(int result) {
  id = -1;
  if (result == QDialog::Accepted) {
    QListWidgetItem *item = listWidget->currentItem();
    if (item) {
      id = item->data(Qt::UserRole).toInt();
    }
  }
  QDialog::done(result);
}

/*!
 * \brief FlowChartSymbolPicker::iconForSymbol
 * \param symbolMap symbol name
 * \return a icon
 */
QIcon FlowChartSymbolPicker::iconForSymbol(const QString &symbolMap) {
  QString fileName = ":/images/" + symbolMap.toLower();
  fileName.replace(' ', '-');
  return QIcon(fileName);
}
