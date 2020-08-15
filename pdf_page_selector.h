#ifndef PDF_PAGE_SELECTOR_H
#define PDF_PAGE_SELECTOR_H

#include <QDialog>
#include <QtPdf/QtPdf>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <cctype>

namespace Ui {
class pdf_page_selector;
}

class pdf_page_selector : public QDialog
{
    Q_OBJECT

public:
    explicit pdf_page_selector(QPdfDocument *pdf_doc, size_t &start, size_t &end, QWidget *parent = nullptr);
    ~pdf_page_selector();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void view_render(QLabel *view, size_t page);
    void highlight_edit_err(QLineEdit *editor);
    void clean_edit_err_highlight(QLineEdit *editor);
    void dynamic_page_index_check(const QString &s,
        size_t *another_page_ndex, QLineEdit *editor, QLineEdit *another_editor, QLabel *view);
    bool is_page_index_legal(const QString &page_index_str);
    bool is_page_index_legal(const size_t &page_index);

private:
    Ui::pdf_page_selector *ui;
    QPdfDocument *pdf_doc;
    size_t *start_page_index;
    size_t *end_page_index;
};

#endif // PDF_PAGE_SELECTOR_H
