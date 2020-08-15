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

    ui->start_page_edit->setText("1");
    ui->end_page_edit->setText(std::to_string(this->pdf_doc->pageCount()).c_str());
    this->view_render(ui->start_page_view, 1);
    this->view_render(ui->end_page_view, this->pdf_doc->pageCount());

    connect(ui->cancel_bt, &QPushButton::clicked, this, [&](){
        this->close();
    });

    connect(ui->confirm_bt, &QPushButton::clicked, this, [&](){
        if(!is_page_index_legal(*start_page_index)
             || !is_page_index_legal(*end_page_index)
                || *start_page_index > *end_page_index) {
            QMessageBox::warning(NULL, "Warning", "Invalid page index.", QMessageBox::Ok);
        } else {
            this->close();
        }
    });

    connect(ui->start_page_edit, &QLineEdit::textChanged, this, [&](const QString &s){
        dynamic_page_index_check(s, end_page_index, ui->start_page_edit, ui->end_page_edit, ui->start_page_view);
    });

    connect(ui->end_page_edit, &QLineEdit::textChanged, this, [&](const QString &s){
        dynamic_page_index_check(s, start_page_index, ui->end_page_edit, ui->start_page_edit, ui->end_page_view);
    });

    connect(ui->start_page_edit, &QLineEdit::editingFinished, this, [&](){
        *(this->start_page_index) = strtouq(ui->start_page_edit->text().toLocal8Bit(), nullptr, 0);

    });

    connect(ui->end_page_edit, &QLineEdit::editingFinished, this, [&](){
        *(this->end_page_index) = strtouq(ui->end_page_edit->text().toLocal8Bit(), nullptr, 0);

    });
}

void pdf_page_selector::dynamic_page_index_check(const QString &s,
         size_t *another_page_index, QLineEdit *editor, QLineEdit *another_editor, QLabel *view) {
    size_t page_index = strtouq(s.toLocal8Bit(), nullptr, 0);
    bool page_range_ok =
       (another_page_index==start_page_index)?(page_index>=*another_page_index):(page_index<=*another_page_index);
    if(!is_page_index_legal(s)) {
        this->highlight_edit_err(editor);
    } else {
        this->clean_edit_err_highlight(editor);
        this->view_render(view, page_index);
    }
    if(page_range_ok) {
        this->clean_edit_err_highlight(another_editor);
    } else {
        this->highlight_edit_err(editor);
    }
}

void pdf_page_selector::highlight_edit_err(QLineEdit *editor) {
    if(!ui->start_page_edit->text().isEmpty()&&!ui->end_page_edit->text().isEmpty()) {
        editor->setStyleSheet("border: 1px solid red;");
    }
}

void pdf_page_selector::clean_edit_err_highlight(QLineEdit *editor) {
    editor->setStyleSheet("border: none;");
}

bool pdf_page_selector::is_page_index_legal(const size_t &page_index) {
    if(page_index < 1)  return false;
    if(page_index > (size_t)this->pdf_doc->pageCount()) return false;
    return true;
}

bool pdf_page_selector::is_page_index_legal(const QString &page_index_str) {
    if(page_index_str.isEmpty()) return true;
    for(const QChar* it=page_index_str.begin(); it!=page_index_str.end(); ++it) {
        if(!isdigit((*it).toLatin1())) return false;
    }
    size_t page_index = strtouq(page_index_str.toLocal8Bit(), nullptr, 0);
    return is_page_index_legal(page_index);
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

void pdf_page_selector::view_render(QLabel *view, size_t page) {
    QSize img_size = view->size();
    QImage view_image = this->pdf_doc->render(page-1, img_size);
    view->setPixmap(QPixmap::fromImage(view_image));
}

pdf_page_selector::~pdf_page_selector()
{
    delete ui;
}
