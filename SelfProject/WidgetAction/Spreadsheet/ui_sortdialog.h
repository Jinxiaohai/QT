/********************************************************************************
** Form generated from reading UI file 'sortdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SortDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem;
    QPushButton *moreButton;
    QGroupBox *tertiaryGroupBox;
    QGridLayout *gridLayout1;
    QComboBox *tertiaryOrderCombo;
    QLabel *tertiaryOrderLabel;
    QLabel *tertiaryColumnLabel;
    QSpacerItem *spacerItem1;
    QComboBox *tertiaryColumnCombo;
    QGroupBox *secondaryGroupBox;
    QGridLayout *gridLayout2;
    QComboBox *secondaryOrderCombo;
    QLabel *secondaryOrderLabel;
    QLabel *secondaryColumnLabel;
    QSpacerItem *spacerItem2;
    QComboBox *secondaryColumnCombo;
    QSpacerItem *spacerItem3;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout3;
    QComboBox *primaryOrderCombo;
    QLabel *primaryOrderLabel;
    QLabel *primaryColumnLabel;
    QSpacerItem *spacerItem4;
    QComboBox *primaryColumnCombo;

    void setupUi(QDialog *SortDialog)
    {
        if (SortDialog->objectName().isEmpty())
            SortDialog->setObjectName(QStringLiteral("SortDialog"));
        SortDialog->resize(299, 398);
        gridLayout = new QGridLayout(SortDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        okButton = new QPushButton(SortDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        vboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(SortDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        vboxLayout->addWidget(cancelButton);

        spacerItem = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        moreButton = new QPushButton(SortDialog);
        moreButton->setObjectName(QStringLiteral("moreButton"));
        moreButton->setCheckable(true);

        vboxLayout->addWidget(moreButton);


        gridLayout->addLayout(vboxLayout, 0, 1, 2, 1);

        tertiaryGroupBox = new QGroupBox(SortDialog);
        tertiaryGroupBox->setObjectName(QStringLiteral("tertiaryGroupBox"));
        gridLayout1 = new QGridLayout(tertiaryGroupBox);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        tertiaryOrderCombo = new QComboBox(tertiaryGroupBox);
        tertiaryOrderCombo->addItem(QString());
        tertiaryOrderCombo->addItem(QString());
        tertiaryOrderCombo->setObjectName(QStringLiteral("tertiaryOrderCombo"));

        gridLayout1->addWidget(tertiaryOrderCombo, 1, 1, 1, 2);

        tertiaryOrderLabel = new QLabel(tertiaryGroupBox);
        tertiaryOrderLabel->setObjectName(QStringLiteral("tertiaryOrderLabel"));

        gridLayout1->addWidget(tertiaryOrderLabel, 1, 0, 1, 1);

        tertiaryColumnLabel = new QLabel(tertiaryGroupBox);
        tertiaryColumnLabel->setObjectName(QStringLiteral("tertiaryColumnLabel"));

        gridLayout1->addWidget(tertiaryColumnLabel, 0, 0, 1, 1);

        spacerItem1 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem1, 0, 2, 1, 1);

        tertiaryColumnCombo = new QComboBox(tertiaryGroupBox);
        tertiaryColumnCombo->addItem(QString());
        tertiaryColumnCombo->setObjectName(QStringLiteral("tertiaryColumnCombo"));

        gridLayout1->addWidget(tertiaryColumnCombo, 0, 1, 1, 1);


        gridLayout->addWidget(tertiaryGroupBox, 3, 0, 1, 1);

        secondaryGroupBox = new QGroupBox(SortDialog);
        secondaryGroupBox->setObjectName(QStringLiteral("secondaryGroupBox"));
        gridLayout2 = new QGridLayout(secondaryGroupBox);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        secondaryOrderCombo = new QComboBox(secondaryGroupBox);
        secondaryOrderCombo->addItem(QString());
        secondaryOrderCombo->addItem(QString());
        secondaryOrderCombo->setObjectName(QStringLiteral("secondaryOrderCombo"));

        gridLayout2->addWidget(secondaryOrderCombo, 1, 1, 1, 2);

        secondaryOrderLabel = new QLabel(secondaryGroupBox);
        secondaryOrderLabel->setObjectName(QStringLiteral("secondaryOrderLabel"));

        gridLayout2->addWidget(secondaryOrderLabel, 1, 0, 1, 1);

        secondaryColumnLabel = new QLabel(secondaryGroupBox);
        secondaryColumnLabel->setObjectName(QStringLiteral("secondaryColumnLabel"));

        gridLayout2->addWidget(secondaryColumnLabel, 0, 0, 1, 1);

        spacerItem2 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem2, 0, 2, 1, 1);

        secondaryColumnCombo = new QComboBox(secondaryGroupBox);
        secondaryColumnCombo->addItem(QString());
        secondaryColumnCombo->setObjectName(QStringLiteral("secondaryColumnCombo"));

        gridLayout2->addWidget(secondaryColumnCombo, 0, 1, 1, 1);


        gridLayout->addWidget(secondaryGroupBox, 2, 0, 1, 1);

        spacerItem3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem3, 1, 0, 1, 1);

        primaryGroupBox = new QGroupBox(SortDialog);
        primaryGroupBox->setObjectName(QStringLiteral("primaryGroupBox"));
        gridLayout3 = new QGridLayout(primaryGroupBox);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        primaryOrderCombo = new QComboBox(primaryGroupBox);
        primaryOrderCombo->addItem(QString());
        primaryOrderCombo->addItem(QString());
        primaryOrderCombo->setObjectName(QStringLiteral("primaryOrderCombo"));

        gridLayout3->addWidget(primaryOrderCombo, 1, 1, 1, 2);

        primaryOrderLabel = new QLabel(primaryGroupBox);
        primaryOrderLabel->setObjectName(QStringLiteral("primaryOrderLabel"));

        gridLayout3->addWidget(primaryOrderLabel, 1, 0, 1, 1);

        primaryColumnLabel = new QLabel(primaryGroupBox);
        primaryColumnLabel->setObjectName(QStringLiteral("primaryColumnLabel"));

        gridLayout3->addWidget(primaryColumnLabel, 0, 0, 1, 1);

        spacerItem4 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem4, 0, 2, 1, 1);

        primaryColumnCombo = new QComboBox(primaryGroupBox);
        primaryColumnCombo->addItem(QString());
        primaryColumnCombo->setObjectName(QStringLiteral("primaryColumnCombo"));

        gridLayout3->addWidget(primaryColumnCombo, 0, 1, 1, 1);


        gridLayout->addWidget(primaryGroupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(primaryColumnCombo, primaryOrderCombo);
        QWidget::setTabOrder(primaryOrderCombo, secondaryColumnCombo);
        QWidget::setTabOrder(secondaryColumnCombo, secondaryOrderCombo);
        QWidget::setTabOrder(secondaryOrderCombo, tertiaryColumnCombo);
        QWidget::setTabOrder(tertiaryColumnCombo, tertiaryOrderCombo);
        QWidget::setTabOrder(tertiaryOrderCombo, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, moreButton);

        retranslateUi(SortDialog);
        QObject::connect(moreButton, SIGNAL(toggled(bool)), secondaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(moreButton, SIGNAL(toggled(bool)), tertiaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(okButton, SIGNAL(clicked()), SortDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SortDialog, SLOT(reject()));

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(SortDialog);
    } // setupUi

    void retranslateUi(QDialog *SortDialog)
    {
        SortDialog->setWindowTitle(QApplication::translate("SortDialog", "Sort", nullptr));
        okButton->setText(QApplication::translate("SortDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("SortDialog", "Cancel", nullptr));
        moreButton->setText(QApplication::translate("SortDialog", "&More", nullptr));
        tertiaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Tertiary Key", nullptr));
        tertiaryOrderCombo->setItemText(0, QApplication::translate("SortDialog", "Ascending", nullptr));
        tertiaryOrderCombo->setItemText(1, QApplication::translate("SortDialog", "Descending", nullptr));

        tertiaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", nullptr));
        tertiaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", nullptr));
        tertiaryColumnCombo->setItemText(0, QApplication::translate("SortDialog", "None", nullptr));

        secondaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Secondary Key", nullptr));
        secondaryOrderCombo->setItemText(0, QApplication::translate("SortDialog", "Ascending", nullptr));
        secondaryOrderCombo->setItemText(1, QApplication::translate("SortDialog", "Descending", nullptr));

        secondaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", nullptr));
        secondaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", nullptr));
        secondaryColumnCombo->setItemText(0, QApplication::translate("SortDialog", "None", nullptr));

        primaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Primary Key", nullptr));
        primaryOrderCombo->setItemText(0, QApplication::translate("SortDialog", "Ascending", nullptr));
        primaryOrderCombo->setItemText(1, QApplication::translate("SortDialog", "Descending", nullptr));

        primaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", nullptr));
        primaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", nullptr));
        primaryColumnCombo->setItemText(0, QApplication::translate("SortDialog", "None", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SortDialog: public Ui_SortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
