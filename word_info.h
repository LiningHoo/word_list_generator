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

namespace Ui {
class word_info;
}

class word_info : public QWidget
{
    Q_OBJECT

public:
    explicit word_info(QString path, QProgressBar* bar, QWidget *parent=nullptr);
    ~word_info();
    void load();
    void start();


private:
    Ui::word_info *ui;
    std::unordered_set<std::string> word_set;
    std::unordered_set<std::string>::iterator it = word_set.begin();
    QWidget *parent;
    std::string file_path;
    std::string output_file_path;
    std::string word;
    sqlite3pp::database db;
    sqlite3pp::database already_know_db;
    long long progress = 0;
    QProgressBar *progress_bar;
    std::ifstream file;
    std::ofstream output_file;


    bool is_letter(const char &c);
    bool is_english_word(const std::string &s);
    bool is_already_know(const std::string &word);
    std::string translation(const std::string &word);
    std::string trim(const std::string &word);
    std::string get_file_ext(const std::string &file_path);
    std::string file2str(const std::string &file_path);
    std::string txt2str(const std::string &file_path);
    std::string pdf2str(const std::string &file_path);

signals:
    void one_word_processed();
};

#endif // WORD_INFO_H
