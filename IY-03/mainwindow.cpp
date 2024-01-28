#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Select");
    ui->lineEdit->setStyleSheet("QLineEdit { font-size : 28px; color : red; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText("Hello World");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
}

