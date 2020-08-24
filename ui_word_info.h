/********************************************************************************
** Form generated from reading UI file 'word_info.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORD_INFO_H
#define UI_WORD_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_word_info
{
public:
    QLabel *label;
    QTextBrowser *textBrowser;
    QPushButton *yes_bt;
    QPushButton *no_bt;

    void setupUi(QWidget *word_info)
    {
        if (word_info->objectName().isEmpty())
            word_info->setObjectName(QString::fromUtf8("word_info"));
        word_info->resize(400, 249);
        label = new QLabel(word_info);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 361, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        font.setPointSize(26);
        label->setFont(font);
        textBrowser = new QTextBrowser(word_info);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 60, 371, 141));
        yes_bt = new QPushButton(word_info);
        yes_bt->setObjectName(QString::fromUtf8("yes_bt"));
        yes_bt->setGeometry(QRect(50, 210, 101, 31));
        no_bt = new QPushButton(word_info);
        no_bt->setObjectName(QString::fromUtf8("no_bt"));
        no_bt->setGeometry(QRect(220, 210, 101, 31));

        retranslateUi(word_info);

        QMetaObject::connectSlotsByName(word_info);
    } // setupUi

    void retranslateUi(QWidget *word_info)
    {
        word_info->setWindowTitle(QCoreApplication::translate("word_info", "Form", nullptr));
        label->setText(QCoreApplication::translate("word_info", "TextLabel", nullptr));
        yes_bt->setText(QCoreApplication::translate("word_info", "Yes", nullptr));
        no_bt->setText(QCoreApplication::translate("word_info", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class word_info: public Ui_word_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORD_INFO_H
