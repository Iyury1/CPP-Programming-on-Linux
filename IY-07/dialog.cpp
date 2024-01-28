#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFont>
#include <QFileInfo>
#include <QFileInfoList>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{font-size: 12px;}");
    QFont mFont = ui->plainTextEdit->font();
    mFont.setPointSize(12);
    ui->plainTextEdit->setFont(mFont);
    ui->lineEdit->setText(QDir::homePath());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    QString currPath = ui->lineEdit->text();
    QDir myDir(currPath);
    if (myDir.exists())
    {
        QFileInfoList myInfoList = myDir.entryInfoList();
        for (QFileInfo info : myInfoList)
        {
            ui->plainTextEdit->appendPlainText(info.absoluteFilePath());
        }
    }
    else
    {
        ui->plainTextEdit->setPlainText("Directory does not exist");
    }
}

