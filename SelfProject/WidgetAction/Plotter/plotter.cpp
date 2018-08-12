#include <QIcon>
#include <QStylePainter>
#include <QToolButton>

#include "plotter.h"

Plotter::Plotter(QWidget *parent) : QWidget(parent) {
  this->setBackgroundRole(QPalette::Dark);
  this->setAutoFillBackground(true);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFocusPolicy(Qt::StrongFocus);
  this->rubberBandIsShown = false;

  zoomInButton = new QToolButton(this);
  zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
  zoomInButton->adjustSize();
  connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

  zoomOutButton = new QToolButton(this);
  zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
  zoomOutButton->adjustSize();
  connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

  setPlotSettings(PlotSettings());
}

Plotter::~Plotter() {}

void Plotter::setPlotSettings(const PlotSettings &settings) {
  zoomStack.clear();
  zoomStack.append(settings);
  curZoom = 0;
  zoomInButton->hide();
  zoomOutButton->hide();
  refreshPixmap();
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data) {
  curveMap[id] = data;
  refreshPixmap();
}

void Plotter::clearCurve(int id) {
  curveMap.remove(id);
  refreshPixmap();
}

QSize Plotter::minimumSizeHint() const { return QSize(6 * Margin, 4 * Margin); }

QSize Plotter::sizeHint() const { return QSize(12 * Margin, 8 * Margin); }

void Plotter::zoomIn() {
  if (curZoom < zoomStack.count() - 1) {
    ++curZoom;
    zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
    zoomOutButton->setEnabled(true);
    zoomOutButton->show();
    refreshPixmap();
  }
}

void Plotter::zoomOut() {
  if (curZoom > 0) {
    --curZoom;
    zoomOutButton->setEnabled(curZoom > 0);
    zoomInButton->setEnabled(true);
    zoomInButton->show();
    refreshPixmap();
  }
}

void Plotter::paintEvent(QPaintEvent *event) {
  QStylePainter painter(this);
  painter.drawPixmap(0, 0, pixmap);

  if (rubberBandIsShown) {
    painter.setPen(palette().light().color());
    painter.drawRect(rubberBandRect.normalized().adjusted(0, 0, -1, -1));
  }
}
