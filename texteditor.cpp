#include "texteditor.h"
#include "ui_texteditor.h"
#include <QMainWindow>
#include "qfiledialog.h"
#include "qtextstream.h"


TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    this->setMinimumHeight(381);
    this->setMaximumHeight(381);
    this->setMinimumWidth(700);
    this->setMaximumWidth(700);
    this->setStyleSheet("background-color: #ccff90;");
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::on_pushButton_clicked()
{
    this->close();
    emit mainWindow();
}

void TextEditor::on_pushButton_2_clicked()
{
    QString fileout = QFileDialog::getSaveFileName();
    QFile file(fileout);
    //file.open(QIODevice::WriteOnly);
    QString str=ui->textEdit->toPlainText();
    QStringList strList=str.split('\n');
    file.open(QIODevice::WriteOnly);
    for (int i = 0; i < strList.size(); i++){
        file.write(strList.at(i).toUtf8());
        file.write("\r\n");
    }
}
