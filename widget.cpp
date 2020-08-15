#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle(QString("Word List Generator"));
    ui->progress_bar->setRange(0, 100);
    ui->progress_bar->setValue(0);

//    connect(this, &QWidget::close, this, [&](){
//        exit(0);
//    });

    connect(ui->open_file_button, &QPushButton::clicked, this, [&](){
          QFileDialog *fileDialog = new QFileDialog(this);
          fileDialog->setWindowTitle(tr("打开文件"));
          fileDialog->setDirectory(".");
          QStringList name_filter;
          name_filter << "Text files (*.txt)" << "Pdf files (*.pdf)";
          fileDialog->setNameFilters(name_filter);
          fileDialog->setViewMode(QFileDialog::Detail);
          QString file_name;
          if (fileDialog->exec())
          {
            file_name = fileDialog->selectedFiles()[0];
          }
          ui->file_name_label->setText(file_name);

          if(!file_name.isEmpty()) {
              word_info *info_widget =
                      new word_info(file_name, ui->progress_bar);
              info_widget->start();
          }
    });
}

Widget::~Widget()
{
    delete ui;
}

