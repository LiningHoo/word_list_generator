/********************************************************************************
** Form generated from reading UI file 'pdf_page_selector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDF_PAGE_SELECTOR_H
#define UI_PDF_PAGE_SELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pdf_page_selector
{
public:
    QLabel *start_label;
    QLineEdit *start_page_edit;
    QLabel *end_label;
    QLineEdit *end_page_edit;
    QPushButton *confirm_bt;
    QPushButton *cancel_bt;
    QLabel *start_page_view;
    QLabel *end_page_view;

    void setupUi(QWidget *pdf_page_selector)
    {
        if (pdf_page_selector->objectName().isEmpty())
            pdf_page_selector->setObjectName(QString::fromUtf8("pdf_page_selector"));
        pdf_page_selector->resize(523, 342);
        start_label = new QLabel(pdf_page_selector);
        start_label->setObjectName(QString::fromUtf8("start_label"));
        start_label->setGeometry(QRect(50, 20, 71, 18));
        start_page_edit = new QLineEdit(pdf_page_selector);
        start_page_edit->setObjectName(QString::fromUtf8("start_page_edit"));
        start_page_edit->setGeometry(QRect(130, 20, 113, 26));
        end_label = new QLabel(pdf_page_selector);
        end_label->setObjectName(QString::fromUtf8("end_label"));
        end_label->setGeometry(QRect(280, 20, 61, 18));
        end_page_edit = new QLineEdit(pdf_page_selector);
        end_page_edit->setObjectName(QString::fromUtf8("end_page_edit"));
        end_page_edit->setGeometry(QRect(360, 20, 113, 26));
        confirm_bt = new QPushButton(pdf_page_selector);
        confirm_bt->setObjectName(QString::fromUtf8("confirm_bt"));
        confirm_bt->setGeometry(QRect(100, 300, 91, 31));
        cancel_bt = new QPushButton(pdf_page_selector);
        cancel_bt->setObjectName(QString::fromUtf8("cancel_bt"));
        cancel_bt->setGeometry(QRect(330, 300, 91, 31));
        start_page_view = new QLabel(pdf_page_selector);
        start_page_view->setObjectName(QString::fromUtf8("start_page_view"));
        start_page_view->setGeometry(QRect(70, 60, 151, 221));
        end_page_view = new QLabel(pdf_page_selector);
        end_page_view->setObjectName(QString::fromUtf8("end_page_view"));
        end_page_view->setGeometry(QRect(300, 60, 151, 221));

        retranslateUi(pdf_page_selector);

        QMetaObject::connectSlotsByName(pdf_page_selector);
    } // setupUi

    void retranslateUi(QWidget *pdf_page_selector)
    {
        pdf_page_selector->setWindowTitle(QCoreApplication::translate("pdf_page_selector", "Form", nullptr));
        start_label->setText(QCoreApplication::translate("pdf_page_selector", "Start Page", nullptr));
        end_label->setText(QCoreApplication::translate("pdf_page_selector", "End Page", nullptr));
        confirm_bt->setText(QCoreApplication::translate("pdf_page_selector", "Confirm", nullptr));
        cancel_bt->setText(QCoreApplication::translate("pdf_page_selector", "Cancel", nullptr));
        start_page_view->setText(QCoreApplication::translate("pdf_page_selector", "TextLabel", nullptr));
        end_page_view->setText(QCoreApplication::translate("pdf_page_selector", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pdf_page_selector: public Ui_pdf_page_selector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDF_PAGE_SELECTOR_H
