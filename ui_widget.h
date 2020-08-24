/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *open_file_button;
    QLabel *file_name_label;
    QProgressBar *progress_bar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(519, 90);
        open_file_button = new QPushButton(Widget);
        open_file_button->setObjectName(QString::fromUtf8("open_file_button"));
        open_file_button->setGeometry(QRect(410, 20, 91, 31));
        file_name_label = new QLabel(Widget);
        file_name_label->setObjectName(QString::fromUtf8("file_name_label"));
        file_name_label->setGeometry(QRect(10, 20, 391, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(10);
        file_name_label->setFont(font);
        progress_bar = new QProgressBar(Widget);
        progress_bar->setObjectName(QString::fromUtf8("progress_bar"));
        progress_bar->setGeometry(QRect(10, 60, 491, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(12);
        progress_bar->setFont(font1);
        progress_bar->setValue(24);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        open_file_button->setText(QCoreApplication::translate("Widget", "Open File", nullptr));
        file_name_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
