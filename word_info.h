#ifndef WORD_INFO_H
#define WORD_INFO_H

#include <QWidget>
#include "set"
#include "fstream"
#include "sqlite3pp/sqlite3pp.h"
#include "QProgressBar"
#include "QTextCodec"
#include "unordered_set"
#include "QtPdf/QtPdf"
#include "string"
#include "sstream"
#include "pdf_page_selector.h"
#include "QMutex"


namespace Ui {
class word_info;
}



class word_info : public QWidget
{
    Q_OBJECT

public:
    explicit word_info(QString path, QProgressBar* bar, QWidget *parent=nullptr);
    ~word_info();
    void main_task_start();
    void append_words_to_set(const std::string &str);


private:
    Ui::word_info *ui;
    std::unordered_set<std::string> word_set;
    std::unordered_set<std::string>::iterator iter = word_set.begin();
    QWidget *parent;
    std::string file_path;
    std::string output_file_path;
    std::string word;
    sqlite3pp::database db = sqlite3pp::database("stardict.db");
    sqlite3pp::database already_know_db = sqlite3pp::database("already_know.db");
    long long progress = 0;
    QProgressBar *progress_bar;
    std::ifstream file;
    std::ofstream output_file;
    QMutex mtx;


    void load_content_to_widget(const std::unordered_set<std::string>::iterator &it);
    bool is_letter(const char &c);
    bool is_english_word(const std::string &s);
    bool is_already_know(const std::string &word);
    std::string translation(const std::string &word);
    void trim(std::string &word);
    std::string get_file_ext(const std::string &file_path);
    void txt_task(const std::string &file_path);
    void pdf_task(const std::string &file_path);

signals:
    void one_word_processed();
};

class AppendWordSetThread: public QThread {
    Q_OBJECT
private:
    word_info *parent;
    std::unordered_set<std::string> *word_set;
    QPdfDocument *pdf_doc;
    size_t start_page_index;
    size_t end_page_index;
    QMutex *mtx = new QMutex;
public:
    explicit AppendWordSetThread() = default;
    explicit AppendWordSetThread(word_info *parent, std::unordered_set<std::string> *word_set,
                         QPdfDocument *pdf_doc, size_t start_page_index, size_t end_page_index) {
        this->parent = parent;
        this->word_set = word_set;
        this->pdf_doc = pdf_doc;
        this->start_page_index = start_page_index;
        this->end_page_index = end_page_index;
    }
protected:
    void run() override {
        for(size_t page=start_page_index-1; page!=end_page_index; ++page) {
            std::string str = pdf_doc->getAllText(page).text().toStdString().append("\n");
            parent->append_words_to_set(str);
        }
    }
};

#endif // WORD_INFO_H
