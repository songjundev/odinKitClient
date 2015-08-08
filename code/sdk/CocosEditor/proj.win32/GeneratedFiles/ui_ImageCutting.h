/********************************************************************************
** Form generated from reading UI file 'ImageCutting.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGECUTTING_H
#define UI_IMAGECUTTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageCutting
{
public:
    QGroupBox *groupBox;
    QLineEdit *edit_width;
    QLabel *lbl_width;
    QPushButton *btn_begin;
    QLineEdit *edit_height;
    QLabel *lbl_height;
    QPushButton *btn_selected;
    QPushButton *btn_setSavePath;
    QLabel *lbl_savePath;

    void setupUi(QWidget *ImageCutting)
    {
        if (ImageCutting->objectName().isEmpty())
            ImageCutting->setObjectName(QStringLiteral("ImageCutting"));
        ImageCutting->resize(709, 448);
        groupBox = new QGroupBox(ImageCutting);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 10, 681, 81));
        edit_width = new QLineEdit(groupBox);
        edit_width->setObjectName(QStringLiteral("edit_width"));
        edit_width->setGeometry(QRect(50, 20, 113, 20));
        lbl_width = new QLabel(groupBox);
        lbl_width->setObjectName(QStringLiteral("lbl_width"));
        lbl_width->setGeometry(QRect(10, 20, 54, 12));
        btn_begin = new QPushButton(groupBox);
        btn_begin->setObjectName(QStringLiteral("btn_begin"));
        btn_begin->setGeometry(QRect(430, 20, 75, 23));
        edit_height = new QLineEdit(groupBox);
        edit_height->setObjectName(QStringLiteral("edit_height"));
        edit_height->setGeometry(QRect(220, 20, 113, 20));
        lbl_height = new QLabel(groupBox);
        lbl_height->setObjectName(QStringLiteral("lbl_height"));
        lbl_height->setGeometry(QRect(170, 20, 54, 12));
        btn_selected = new QPushButton(groupBox);
        btn_selected->setObjectName(QStringLiteral("btn_selected"));
        btn_selected->setGeometry(QRect(350, 20, 75, 23));
        btn_setSavePath = new QPushButton(groupBox);
        btn_setSavePath->setObjectName(QStringLiteral("btn_setSavePath"));
        btn_setSavePath->setGeometry(QRect(10, 50, 91, 21));
        lbl_savePath = new QLabel(groupBox);
        lbl_savePath->setObjectName(QStringLiteral("lbl_savePath"));
        lbl_savePath->setGeometry(QRect(110, 50, 61, 16));

        retranslateUi(ImageCutting);

        QMetaObject::connectSlotsByName(ImageCutting);
    } // setupUi

    void retranslateUi(QWidget *ImageCutting)
    {
        ImageCutting->setWindowTitle(QApplication::translate("ImageCutting", "Form", 0));
        groupBox->setTitle(QApplication::translate("ImageCutting", "\345\210\207\345\233\276\351\200\211\351\241\271", 0));
        lbl_width->setText(QApplication::translate("ImageCutting", "width:", 0));
        btn_begin->setText(QApplication::translate("ImageCutting", "\345\274\200\345\247\213", 0));
        lbl_height->setText(QApplication::translate("ImageCutting", "height:", 0));
        btn_selected->setText(QApplication::translate("ImageCutting", "\351\200\211\345\233\276", 0));
        btn_setSavePath->setText(QApplication::translate("ImageCutting", "\350\256\276\347\275\256\344\277\235\345\255\230\350\267\257\345\276\204", 0));
        lbl_savePath->setText(QApplication::translate("ImageCutting", "NULL", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageCutting: public Ui_ImageCutting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGECUTTING_H
