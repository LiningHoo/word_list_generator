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
        if(std::distance(it, this->word_set.end()) >= 2){
            output_file << *it << "\t" << translation(*it) << std::endl;
            ++this->it;
            load();
        }
        emit one_word_processed();
    });

    connect(ui->no_bt, &QPushButton::clicked, this, [&](){
        const std::string &word = *it;
        if(std::distance(it, this->word_set.end()) >= 2){
            if(!is_already_know(word)) {
                std::string sql =
                    std::string("insert into words (word) values ('") + word + "');";
                already_know_db.execute(sql.c_str());
                already_know_db.execute("commit;");
            }
            ++this->it;
            load();
        }
        emit one_word_processed();
    });
}

word_info::~word_info()
{
    delete ui;
}

void word_info::load() {
    ui->label->setText(QString::fromStdString(*this->it));
    ui->textBrowser->setText(QString::fromStdString(translation(*this->it)));
}

void word_info::start() {
    word_set.clear();

    db = sqlite3pp::database("stardict.db");
    already_know_db = sqlite3pp::database("already_know.db");

    std::string str = file2str(file_path);
    std::istringstream iss(str);

    while(iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        word = trim(word);
        if(is_english_word(word) && word_set.find(word)==word_set.end()) {
            std::string chinese = translation(word);
            if(chinese != "" && !is_already_know(word)) {
                word_set.insert(word);
            }
        }
    }

    this->setVisible(true);
    this->it = this->word_set.begin();
    load();
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

std::string word_info::trim(const std::string &word) {
    int left = 0, right = word.length();
    while(left < (int)word.length() && !is_letter(word[left])) ++left;
    while(--right >=0 && !is_letter(word[right]));
    return left <= right ? word.substr(left, right-left+1) : word;
}

std::string word_info::get_file_ext(const std::string &file_path) {
    size_t last_dot_pos = file_path.rfind('.');
    return file_path.substr(last_dot_pos, file_path.length()-last_dot_pos);
}

std::string word_info::file2str(const std::string &file_path) {
    std::string ext = get_file_ext(file_path);
    if(ext == ".txt") {
        return txt2str(file_path);
    } else if(ext == ".pdf") {
        return pdf2str(file_path);
    } else {
        return "";
    }
}

std::string word_info::txt2str(const std::string &file_path) {
    std::ifstream file(file_path);
    std::string ret, temp;
    while(std::getline(file, temp)) {
        ret.append(temp).append("\n");
    }
    return ret;
}

std::string word_info::pdf2str(const std::string &file_path) {
    this->setVisible(false);

    std::string ret = "";
    QPdfDocument *pdf_doc = new QPdfDocument();

    pdf_doc->load(QString::fromStdString(file_path));

    size_t start_page_index, end_page_index;

    pdf_page_selector *selector = new pdf_page_selector(pdf_doc, start_page_index, end_page_index);
    selector->exec();

    for(size_t page=start_page_index-1; page!=end_page_index; ++page) {
        ret.append(pdf_doc->getAllText(page).text().toLocal8Bit().data()).append("\n");
    }

//    qDebug() << start_page_index << " " << end_page_index << "\n";
//    QPdfSelection selected_text = pdf_doc->getAllText(35);

//    qDebug() << selected_text.text().toLocal8Bit().data();
//    this->setVisible(true);
    return ret;
}
