#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // 获取 lineedit 数据
    QString program = ui->lineEdit->text();
    // 创建一个 QProcess 对象
    QProcess *my_process = new QProcess(this);
    my_process->start(program);
}

