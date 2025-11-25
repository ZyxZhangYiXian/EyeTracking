#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 连接信号与槽
    connect(ui->cmd_line_edit, SIGNAL(returnPressed()), this, SLOT(on_commit_button_clicked()));
    connect(ui->cancel_button, &QPushButton::clicked, this, &Widget::on_cancel_button_clicked);
    connect(ui->browse_button, &QPushButton::clicked, [this]()
    {
        QMessageBox::information(this, "信息", "点击浏览");
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_commit_button_clicked()
{
    // 获取 lineedit 数据
    QString program = ui->cmd_line_edit->text();
    // 创建一个 QProcess 对象
    QProcess *my_process = new QProcess(this);
    my_process->start(program);
}

void Widget::on_cancel_button_clicked()
{
    // 关闭应用程序
    this->close();
}

void Widget::on_button_one_clicked()
{
    expression += "1";
    ui->cmd_line_edit->setText(expression);
}