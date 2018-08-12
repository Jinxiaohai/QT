#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->widget->SetBGPressColor(QColor(198, 47, 47));
    ui->widget->setBGReleaseColor(QColor(198, 47, 47));
    ui->widget->setContentText(QString("Groups WorkSpace"));

    ui->widget->SetBGPressColor(QColor(80, 80, 80));
    ui->widget->setBGReleaseColor(QColor(30, 30, 30));
    ui->widget->setContentText(QString("Groups WorkSpace"));
    ui->widget_2->setColorModel(WKButton::ColorMode_Replace);
}

Form::~Form()
{
    delete ui;
}
