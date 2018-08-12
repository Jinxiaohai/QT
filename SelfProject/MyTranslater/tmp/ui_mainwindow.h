/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qgiflabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit_src;
    QPlainTextEdit *plainTextEdit_dst;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QPushButton *btnTranslate;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer_4;
    QGifLabel *label_statusPicture;
    QLabel *label_translationStatus;
    QLabel *label_main_top;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(614, 460);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 4, 4, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(3);
        plainTextEdit_src = new QPlainTextEdit(centralWidget);
        plainTextEdit_src->setObjectName(QStringLiteral("plainTextEdit_src"));
        plainTextEdit_src->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(plainTextEdit_src, 1, 0, 1, 1);

        plainTextEdit_dst = new QPlainTextEdit(centralWidget);
        plainTextEdit_dst->setObjectName(QStringLiteral("plainTextEdit_dst"));
        plainTextEdit_dst->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit_dst, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 27));
        comboBox->setMaximumSize(QSize(190, 27));

        horizontalLayout_2->addWidget(comboBox);

        btnTranslate = new QPushButton(centralWidget);
        btnTranslate->setObjectName(QStringLiteral("btnTranslate"));
        btnTranslate->setMinimumSize(QSize(90, 25));
        btnTranslate->setMaximumSize(QSize(90, 25));
        btnTranslate->setFocusPolicy(Qt::NoFocus);
        btnTranslate->setStyleSheet(QStringLiteral(""));
        btnTranslate->setFlat(true);

        horizontalLayout_2->addWidget(btnTranslate);

        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        btnClear->setMinimumSize(QSize(90, 25));
        btnClear->setMaximumSize(QSize(90, 25));
        btnClear->setFocusPolicy(Qt::NoFocus);
        btnClear->setStyleSheet(QStringLiteral(""));
        btnClear->setFlat(true);

        horizontalLayout_2->addWidget(btnClear);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_statusPicture = new QGifLabel(centralWidget);
        label_statusPicture->setObjectName(QStringLiteral("label_statusPicture"));

        horizontalLayout_2->addWidget(label_statusPicture);

        label_translationStatus = new QLabel(centralWidget);
        label_translationStatus->setObjectName(QStringLiteral("label_translationStatus"));

        horizontalLayout_2->addWidget(label_translationStatus);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        label_main_top = new QLabel(centralWidget);
        label_main_top->setObjectName(QStringLiteral("label_main_top"));
        label_main_top->setMinimumSize(QSize(0, 50));
        label_main_top->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_main_top, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(plainTextEdit_src, plainTextEdit_dst);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnTranslate->setText(QApplication::translate("MainWindow", "Translate", nullptr));
        btnClear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        label_statusPicture->setText(QString());
        label_translationStatus->setText(QString());
        label_main_top->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
