#include <QPainter>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Widget::paintEvent(QPaintEvent *event) {
  //  QPainter painter(this);
  //  QRectF rect(10.0, 10.0, 380.0, 280.0);
  //  painter.setPen(Qt::red);
  //  painter.drawRect(rect);
  //  painter.setPen(Qt::blue);
  //  painter.drawText(rect, Qt::AlignHCenter, tr("AlignHCenter"));
  //  painter.drawText(rect, Qt::AlignLeft, tr("AlignLeft"));
  //  painter.drawText(rect, Qt::AlignRight, tr("AlignRight"));
  //  painter.drawText(rect, Qt::AlignVCenter, tr("AlignVCenter"));
  //  painter.drawText(rect, Qt::AlignBottom, tr("AlignBottom"));
  //  painter.drawText(rect, Qt::AlignCenter, tr("AlignCenter"));
  //  painter.drawText(rect, Qt::AlignBottom | Qt::AlignRight,
  //                   tr("AlignBottom\nAlignRight"));

  //  QFont font("song", 15, QFont::Bold, true);
  //  font.setUnderline(true);
  //  font.setOverline(true);
  //  font.setCapitalization(QFont::SmallCaps);
  //  font.setLetterSpacing(QFont::AbsoluteSpacing, 10);

  //  painter.setFont(font);
  //  painter.setPen(Qt::green);
  //  painter.drawText(120, 80, tr("xiaohai"));
  //  painter.translate(100, 100);
  //  painter.rotate(90);
  //  painter.drawText(0., 0, tr("xiaopangzi"));

  //  QPainter painter(this);
  //  QPainterPath path;
  //  path.moveTo(50, 250);
  //  path.lineTo(50, 230);
  //  path.cubicTo(QPointF(105, 40), QPointF(115, 80), QPointF(120, 60));
  //  path.lineTo(130, 130);
  //  path.addEllipse(QPointF(130, 130), 30, 30);
  //  painter.setPen(Qt::darkYellow);
  //  painter.drawPath(path);

  //  path.translate(200, 0);
  //  painter.setPen(Qt::darkBlue);
  //  painter.drawPath(path);

  QPainter painter(this);
  QPainterPath path;
  path.addEllipse(10, 50, 100, 100);
  path.addRect(50, 100, 100, 100);
  painter.setBrush(Qt::cyan);
  painter.drawPath(path);

  painter.translate(180, 0);
  path.setFillRule(Qt::WindingFill);
  painter.drawPath(path);
}
