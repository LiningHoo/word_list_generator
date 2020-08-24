#include "word_info.h"
#include "ui_word_info.h"

word_info::word_info(QString path, QProgressBar* bar, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::word_info)
{
    ui->setupUi(this);
    this->setVisible(false);
    this->setFixedSize(this->size());
    this->setWindowTitle("Write to file?");
    this->parent = parent;
    this->file_path = path.toLocal8Bit().data();
    this->progress_bar = bar;

    QTextCodec *code = QTextCodec::codecForName("GB2312");
    this->output_file_path = code->fromUnicode(path + "_word_list.txt").data();

    this->file = std::ifstream(file_path);
    this->output_file = std::ofstream(output_file_path);


    connect(this, &word_info::one_word_processed, this, [&](){
        progress_bar->setValue(std::min(100, static_cast<int>(++progress*100.f/word_set.size())));
    });

    connect(ui->yes_bt, &QPushButton::clicked, this, [&](){
        if(std::distance(iter, this->word_set.end()) >= 2){
            output_file << *iter << "\t" << translation(*iter) << std::endl;
            load_content_to_widget(++this->iter);
        }
        emit one_word_processed();
    });

    connect(ui->no_bt, &QPushButton::clicked, this, [&](){
        const std::string &word = *iter;
        if(std::distance(iter, this->word_set.end()) >= 2){
            if(!is_already_know(word)) {
                std::string sql =
                    std::string("insert into words (word) values ('") + word + "');";
                already_know_db.execute(sql.c_str());
                already_know_db.execute("commiter;");
            }
            load_content_to_widget(++this->iter);
        }
        emit one_word_processed();
    });

}

word_info::~word_info()
{
    delete ui;
}

void word_info::load_content_to_widget(const std::unordered_set<std::string>::iterator &iter) {
    ui->label->setText(QString::fromStdString(*iter));
    ui->textBrowser->setText(QString::fromStdString(translation(*iter)));
}

void word_info::main_task_start() {
    this->progress = 0;
    std::string ext = get_file_ext(file_path);
    if(ext == ".txt") {
        txt_task(file_path);
    } else if(ext == ".pdf") {
        pdf_task(file_path);
    } else {
        ;
    }
}

void word_info::append_words_to_set(const std::string &str) {
    if(str.empty()) return;
    std::istringstream iss(str);
    while(iss >> word) {
        trim(word);
        if(is_english_word(word) && word_set.find(word)==word_set.end()) {
            std::transform(word.begin(), word.end(), word.begin(), tolower);
            std::string chinese = translation(word);
            if(chinese != "" && !is_already_know(word)) {
                word_set.insert(word);
            }
        }
    }
}

bool word_info::is_letter(const char &c) {
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}

bool word_info::is_english_word(const std::string &s) {
    if(s[0]=='-') return false;
    for(const char &c: s) {
        if(!(is_letter(c)||c=='-'))
            return false;
    }
    return true;
}

bool word_info::is_already_know(const std::string &word) {
    std::string sql = std::string("select * from words where word='") + word + "'";
    sqlite3pp::query qry(already_know_db, sql.c_str());
    return std::distance(qry.begin(), qry.end()) > 0;
}

std::string word_info::translation(const std::string &word) {
    QString sql =
        QString("select translation from stardict where word='") + QString::fromStdString(word)+"'";
    sqlite3pp::query qry(db, sql.toLocal8Bit());
    std::string chinese;
    for(auto val: qry) {
        val.getter() >> chinese;
    }
    size_t pos = 0;
    while((pos=chinese.find('\n'))!=std::string::npos) {
        chinese.replace(pos, 1, " ");
    }
    return chinese;
}

void word_info::trim(std::string &word) {
    for(auto it=word.begin(); it!=word.end(); ++it) {
        const char &c = *it;
        if(c != '-' && c != '\'' && !is_letter(*it)) {
            word.erase(it--);
        }
    }
}

std::string word_info::get_file_ext(const std::string &file_path) {
    size_t last_dot_pos = file_path.rfind('.');
    return file_path.substr(last_dot_pos, file_path.length()-last_dot_pos);
}

void word_info::txt_task(const std::string &file_path) {
    std::ifstream file(file_path);
    std::string temp, str;

    while(std::getline(file, temp)) {
        str.append(temp);
    }
    append_words_to_set(str);
    this->setVisible(true);
    this->iter = word_set.begin();
    load_content_to_widget(iter);
}


void word_info::pdf_task(const std::string &file_path) {
    this->setVisible(false);

    std::string str = "";
    QPdfDocument *pdf_doc = new QPdfDocument();

    pdf_doc->load(QString::fromStdString(file_path));

    size_t start_page_index = 1, end_page_index = pdf_doc->pageCount();

    pdf_page_selector *selector = new pdf_page_selector(pdf_doc, start_page_index, end_page_index);
    selector->exec();


    if(start_page_index!=0 && end_page_index!=0) {
        AppendWordSetThread *thread = new AppendWordSetThread(this, &word_set, pdf_doc, start_page_index, end_page_index);
        thread->start();
        while(thread->isRunning());
        this->iter = word_set.begin();
        this->load_content_to_widget(iter);
        this->setVisible(true);
    }
}
