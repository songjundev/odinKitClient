/********************************************************************************
** Form generated from reading UI file 'ControlPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanel
{
public:
    QPushButton *btn_drag;
    QGroupBox *groupBox;
    QComboBox *cbo_stop;
    QPushButton *btn_edit;
    QGroupBox *groupBox_2;
    QPushButton *btn_editEventArea;
    QLabel *label;
    QLineEdit *edit_eventType;
    QPushButton *btn_deleteEvent;
    QPushButton *btn_selectedEvent;

    void setupUi(QWidget *ControlPanel)
    {
        if (ControlPanel->objectName().isEmpty())
            ControlPanel->setObjectName(QStringLiteral("ControlPanel"));
        ControlPanel->resize(356, 483);
        btn_drag = new QPushButton(ControlPanel);
        btn_drag->setObjectName(QStringLiteral("btn_drag"));
        btn_drag->setGeometry(QRect(10, 10, 75, 23));
        groupBox = new QGroupBox(ControlPanel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 201, 61));
        cbo_stop = new QComboBox(groupBox);
        cbo_stop->setObjectName(QStringLiteral("cbo_stop"));
        cbo_stop->setGeometry(QRect(10, 20, 101, 22));
        btn_edit = new QPushButton(groupBox);
        btn_edit->setObjectName(QStringLiteral("btn_edit"));
        btn_edit->setGeometry(QRect(120, 20, 75, 23));
        groupBox_2 = new QGroupBox(ControlPanel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 261, 91));
        btn_editEventArea = new QPushButton(groupBox_2);
        btn_editEventArea->setObjectName(QStringLiteral("btn_editEventArea"));
        btn_editEventArea->setGeometry(QRect(10, 50, 91, 23));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 71, 16));
        edit_eventType = new QLineEdit(groupBox_2);
        edit_eventType->setObjectName(QStringLiteral("edit_eventType"));
        edit_eventType->setGeometry(QRect(90, 20, 113, 20));
        btn_deleteEvent = new QPushButton(groupBox_2);
        btn_deleteEvent->setObjectName(QStringLiteral("btn_deleteEvent"));
        btn_deleteEvent->setGeometry(QRect(100, 50, 75, 23));
        btn_selectedEvent = new QPushButton(groupBox_2);
        btn_selectedEvent->setObjectName(QStringLiteral("btn_selectedEvent"));
        btn_selectedEvent->setGeometry(QRect(170, 50, 75, 23));

        retranslateUi(ControlPanel);

        QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
        ControlPanel->setWindowTitle(QApplication::translate("ControlPanel", "ControlPanel", 0));
        btn_drag->setText(QApplication::translate("ControlPanel", "\346\213\226\346\213\275\346\250\241\345\274\217", 0));
        groupBox->setTitle(QApplication::translate("ControlPanel", "\347\274\226\350\276\221\351\230\273\346\214\241\346\225\260\346\215\256", 0));
        cbo_stop->clear();
        cbo_stop->insertItems(0, QStringList()
         << QApplication::translate("ControlPanel", "\345\217\257\344\273\245\350\241\214\350\265\260", 0)
         << QApplication::translate("ControlPanel", "\346\234\211\351\201\256\346\214\241", 0)
         << QApplication::translate("ControlPanel", "\345\256\214\345\205\250\351\230\273\346\214\241", 0)
        );
        btn_edit->setText(QApplication::translate("ControlPanel", "\347\274\226\350\276\221", 0));
        groupBox_2->setTitle(QApplication::translate("ControlPanel", "\344\272\213\344\273\266\345\214\272\347\274\226\350\276\221", 0));
        btn_editEventArea->setText(QApplication::translate("ControlPanel", "\347\274\226\350\276\221\344\272\213\344\273\266\345\214\272\345\237\237", 0));
        label->setText(QApplication::translate("ControlPanel", "event type:", 0));
        btn_deleteEvent->setText(QApplication::translate("ControlPanel", "\345\210\240\351\231\244", 0));
        btn_selectedEvent->setText(QApplication::translate("ControlPanel", "\346\237\245\350\257\242", 0));
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
