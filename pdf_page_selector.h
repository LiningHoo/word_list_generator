#ifndef PDF_PAGE_SELECTOR_H
#define PDF_PAGE_SELECTOR_H

#include <QDialog>
#include <QtPdf/QtPdf>

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

private:
    Ui::pdf_page_selector *ui;
    QPdfDocument *pdf_doc;
    size_t *start_page_index;
    size_t *end_page_index;
};

#endif // PDF_PAGE_SELECTOR_H
