#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFontComboBox>
#include <QLabel>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextEdit>
#include <QTextList>
#include <QTextStream>
#include <QToolButton>

#include "imageprocessor.h"
#include "showwidget.h"

ImageProcessor::ImageProcessor(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle(tr("Fake Word"));

  showWidget = new ShowWidget(this);
  this->setCentralWidget(showWidget);

  fontLabel1 = new QLabel(tr("Font:"));
  fontComboBox = new QFontComboBox;
  fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

  fontLabel2 = new QLabel(tr("Size of Font:"));
  sizeComboBox = new QComboBox;
  QFontDatabase db;
  foreach (int size, db.standardSizes()) {
    sizeComboBox->addItem(QString::number(size));
  }

  boldBtn = new QToolButton;
  boldBtn->setIcon(QIcon(":/images/bold.png"));
  boldBtn->setCheckable(true);

  italicBtn = new QToolButton;
  italicBtn->setIcon(QIcon(":/images/italic.png"));
  italicBtn->setCheckable(true);

  underlineBtn = new QToolButton;
  underlineBtn->setIcon(QIcon(":/images/underline.png"));
  underlineBtn->setCheckable(true);

  colorBtn = new QToolButton;
  colorBtn->setIcon(QIcon(":/images/color.png"));
  colorBtn->setCheckable(true);

  listLabel = new QLabel(tr("Sort"));
  listComboBox = new QComboBox;
  listComboBox->addItem(tr("Standard"));
  listComboBox->addItem(tr("QTextListFormat::ListDisc"));
  listComboBox->addItem(tr("QTextListFormat::ListCircle"));
  listComboBox->addItem(tr("QTextListFormat::ListSquare"));
  listComboBox->addItem(tr("QTextListFormat::ListDecimal"));
  listComboBox->addItem(tr("QTextListFormat::ListLowerAlpha"));
  listComboBox->addItem(tr("QTextListFormat::ListUpperAlpha"));
  listComboBox->addItem(tr("QTextListFormat::ListLowerRoman"));
  listComboBox->addItem(tr("QTextListFormat::ListUpperRoman"));

  this->createActions();
  this->createMenus();
  this->createToolBars();

  if (img.load(":/images/images.png")) {
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
  }

  connect(fontComboBox, SIGNAL(activated(QString)), this,
          SLOT(showFontComboBox(QString)));
  connect(sizeComboBox, SIGNAL(activated(QString)), this,
          SLOT(showSizeSpinBox(QString)));
  connect(boldBtn, SIGNAL(clicked()), this, SLOT(showBoldBtn()));
  connect(italicBtn, SIGNAL(clicked()), this, SLOT(showItalicBtn()));
  connect(underlineBtn, SIGNAL(clicked()), this, SLOT(showUnderlineBtn()));
  connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColorBtn()));
  connect(showWidget->text, SIGNAL(currentCharFormatChanged(QTextCharFormat &)),
          this, SLOT(showCurrentFormatChanged(QTextCharFormat &)));
  connect(listComboBox, SIGNAL(activated(int)), this, SLOT(showList(int)));
  connect(showWidget->text->document(), SIGNAL(undoAvailable(bool)), undoAction,
          SLOT(setEnabled(bool)));
  connect(showWidget->text->document(), SIGNAL(redoAvailable(bool)), redoAction,
          SLOT(setEnabled(bool)));
  connect(showWidget->tex, SIGNAL(cursorPositionChanged()), this,
          SLOT(showCursorPositionChanged()));
}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::createActions() {
  /// open
  openFileAction = new QAction(QIcon(":/images/open.png"), tr("Open"), this);
  openFileAction->setShortcut(tr("Ctrl+O"));
  openFileAction->setStatusTip(tr("Open a file"));
  connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));

  /// new
  newFileAction = new QAction(QIcon(":/images/new.png"), tr("New"), this);
  newFileAction->setShortcut(tr("Ctrl+N"));
  newFileAction->setStatusTip(tr("New"));
  connect(newFileAction, SIGNAL(triggered()), this, SLOT(showNewFile()));
}
