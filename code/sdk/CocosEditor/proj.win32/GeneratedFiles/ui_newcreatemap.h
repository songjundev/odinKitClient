/********************************************************************************
** Form generated from reading UI file 'newcreatemap.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCREATEMAP_H
#define UI_NEWCREATEMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewCreateMap
{
public:
    QPushButton *btn_create;
    QLabel *label;
    QLineEdit *edit_width;
    QLineEdit *edit_height;
    QLabel *label_2;
    QPushButton *btn_help;

    void setupUi(QWidget *NewCreateMap)
    {
        if (NewCreateMap->objectName().isEmpty())
            NewCreateMap->setObjectName(QStringLiteral("NewCreateMap"));
        NewCreateMap->resize(267, 212);
        btn_create = new QPushButton(NewCreateMap);
        btn_create->setObjectName(QStringLiteral("btn_create"));
        btn_create->setGeometry(QRect(130, 110, 75, 23));
        label = new QLabel(NewCreateMap);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 54, 12));
        edit_width = new QLineEdit(NewCreateMap);
        edit_width->setObjectName(QStringLiteral("edit_width"));
        edit_width->setGeometry(QRect(80, 50, 113, 20));
        edit_height = new QLineEdit(NewCreateMap);
        edit_height->setObjectName(QStringLiteral("edit_height"));
        edit_height->setGeometry(QRect(80, 80, 113, 20));
        label_2 = new QLabel(NewCreateMap);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 80, 54, 12));
        btn_help = new QPushButton(NewCreateMap);
        btn_help->setObjectName(QStringLiteral("btn_help"));
        btn_help->setGeometry(QRect(40, 110, 75, 23));

        retranslateUi(NewCreateMap);

        QMetaObject::connectSlotsByName(NewCreateMap);
    } // setupUi

    void retranslateUi(QWidget *NewCreateMap)
    {
        NewCreateMap->setWindowTitle(QApplication::translate("NewCreateMap", "NewCreateMap", 0));
        btn_create->setText(QApplication::translate("NewCreateMap", "create map", 0));
        label->setText(QApplication::translate("NewCreateMap", "width", 0));
        label_2->setText(QApplication::translate("NewCreateMap", "height", 0));
        btn_help->setText(QApplication::translate("NewCreateMap", "help", 0));
    } // retranslateUi

};

namespace Ui {
    class NewCreateMap: public Ui_NewCreateMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCREATEMAP_H
