/********************************************************************************
** Form generated from reading UI file 'cocoseditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COCOSEDITOR_H
#define UI_COCOSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CocosEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CocosEditorClass)
    {
        if (CocosEditorClass->objectName().isEmpty())
            CocosEditorClass->setObjectName(QStringLiteral("CocosEditorClass"));
        CocosEditorClass->resize(600, 400);
        menuBar = new QMenuBar(CocosEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CocosEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CocosEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CocosEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CocosEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CocosEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CocosEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CocosEditorClass->setStatusBar(statusBar);

        retranslateUi(CocosEditorClass);

        QMetaObject::connectSlotsByName(CocosEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CocosEditorClass)
    {
        CocosEditorClass->setWindowTitle(QApplication::translate("CocosEditorClass", "CocosEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class CocosEditorClass: public Ui_CocosEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COCOSEDITOR_H
