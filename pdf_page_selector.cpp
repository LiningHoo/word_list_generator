#include "pdf_page_selector.h"
#include "ui_pdf_page_selector.h"
#include "qdebug.h"

pdf_page_selector::pdf_page_selector(QPdfDocument *pdf_doc, size_t &start, size_t &end, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pdf_page_selector)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Pdf Page Selector");

    this->pdf_doc = pdf_doc;
    this->start_page_index = &start;
    this->end_page_index = &end;


    connect(ui->cancel_bt, &QPushButton::clicked, this, [&](){
        this->close();
    });

    connect(ui->confirm_bt, &QPushButton::clicked, this, [&](){
        this->close();
    });

    connect(ui->start_page_edit, &QLineEdit::editingFinished, this, [&](){
        *(this->start_page_index) = strtouq(ui->start_page_edit->text().toLocal8Bit(), nullptr, 0);
        QSize img_size = ui->start_page_view->size();
        QImage view_image = this->pdf_doc->render(*start_page_index-1, img_size);
        ui->start_page_view->setPixmap(QPixmap::fromImage(view_image));
    });

    connect(ui->end_page_edit, &QLineEdit::editingFinished, this, [&](){
        *(this->end_page_index) = strtouq(ui->end_page_edit->text().toLocal8Bit(), nullptr, 0);
        QSize img_size = ui->end_page_view->size();
        QImage view_image = this->pdf_doc->render(*end_page_index-1, img_size);
        ui->end_page_view->setPixmap(QPixmap::fromImage(view_image));
    });
}

void pdf_page_selector::keyPressEvent(QKeyEvent *event) {
    switch (event->key())
        {
        case Qt::Key_Enter:
            break;
        case Qt::Key_Escape:
            break;
        default:
            pdf_page_selector::keyPressEvent(event);
        }
}

pdf_page_selector::~pdf_page_selector()
{
    delete ui;
}
