#include <QFileDialog>
#include <QFileInfo>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>

#include "Printer.h"
#include "QssStyle.h"
#include "ui_printer.h"

Printer::Printer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Printer) {
  ui->setupUi(this);

  QssStyle::setStyle(":/myqss.qss");
  QAction *actionPrint = new QAction(tr("print"), this);
  QAction *actionPrintPreview = new QAction(tr("print preview"), this);
  QAction *actionPdf = new QAction(tr("generate pdf"), this);

  connect(actionPrint, SIGNAL(triggered()), this, SLOT(doPrint()));
  connect(actionPrintPreview, SIGNAL(triggered()), this,
          SLOT(doPrintPreview()));
  connect(actionPdf, SIGNAL(triggered()), this, SLOT(createPdf()));

  ui->mainToolBar->addAction(actionPrint);
  ui->mainToolBar->addAction(actionPrintPreview);
  ui->mainToolBar->addAction(actionPdf);
}

Printer::~Printer() { delete ui; }

void Printer::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Printer::doPrint() {
  QPrinter printer;
  QPrintDialog dlg(&printer, this);
  if (ui->textEdit->textCursor().hasSelection()) {
    dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
  }
  if (dlg.exec() == QDialog::Accepted) {
    ui->textEdit->print(&printer);
  }
}

void Printer::doPrintPreview() {
  QPrinter printer;
  QPrintPreviewDialog preview(&printer, this);
  connect(&preview, &QPrintPreviewDialog::paintRequested, this,
          &Printer::printPreview);
  preview.exec();
}

void Printer::printPreview(QPrinter *printer) { ui->textEdit->print(printer); }

void Printer::createPdf() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("export pdf file"),
                                                  QString(), "* .pdf");
  if (!fileName.isEmpty()) {
    if (QFileInfo(fileName).suffix().isEmpty()) {
      fileName.append(".pdf");
    }
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    ui->textEdit->print(&printer);
  }
}
