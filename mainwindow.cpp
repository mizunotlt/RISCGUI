#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <RiscMachine.h>
#include "QObject"
#include "Parser.h"
#include "qfile.h"
#include "qfiledialog.h"
#include "texteditor.h"
#include "QLineEdit"
#include "QInputDialog"
RiscMachine risc(100,1000);

QString outStepByStep(int index){
    QString result = "";
    result += "Шаг номер:" + QString:: number(risc.getCountForStep()) +"\r\n";
    switch (risc.getCommand(index)) {
        case risc.ADD: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "ADD" + regA + regB + "0000" +regCI +"\r\n";
            break;
        }
        case risc.ADDI: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "ADDI" + regA + regB + regCI +"\r\n";
            break;
        }
        case risc.NAND: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "NAND" + regA + regB + "0000" +regCI + "\r\n";
            break;
        }
        case risc.LUI:{
            break;
        }
        case risc.SW: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "SW" + regA + regB + regCI +"\r\n";
            break;
        }
        case risc.LW: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "LW" + regA + regB + regCI +"\r\n";
            break;
        }
        case risc.BEQ: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "BEQ" + regA + regB + regCI +"\r\n";
            break;
        }
        case risc.JAIR: {
            QString regA = QString::number(risc.getRegA(index));
            QString regB = QString::number(risc.getRegB(index));
            QString regCI = QString::number(risc.getRegCI(index));
            result = result + "JAIR" + regA + regB + "0000" +regCI +"\r\n";
            break;
        }
    }
    result += "Вывод состояний регистров машины: \r\n";
    for(int i = 0; i < risc.REG; i++){
        result += "Регистр [" + QString:: number(i) + "] = " + QString:: number(risc.getRegMemory(i)) + "\r\n";
    }
    result += "Вывод состояния памяти машины: \r\n";
    for(int i = 0; i <= risc.getMemory(1); i++){
        result += "Ячейка [" + QString:: number(i) + "] = " + QString:: number(risc.getMemory(i)) + "\r\n";
    }
    return result;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textWindow = new TextEditor();
    connect(textWindow, &TextEditor::mainWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Полное выполнение работы программы(готово)
void MainWindow::on_toolButton_4_clicked()
{
    ui->textBrowser->clear();
    risc.fullWork();
    QString result = "";
    result += "Вывод состояний регистров машины: \r\n";
    for(int i = 0; i < risc.REG; i++){
        result += "Регистр [" + QString:: number(i) + "] = " + QString:: number(risc.getRegMemory(i)) + "\r\n";
    }
    result += "Вывод состояния памяти машины: \r\n";
    for(int i = 0; i <= risc.getMemory(1); i++){
        result += "Ячейка [" + QString:: number(i) + "] = " + QString:: number(risc.getMemory(i)) + "\r\n";
    }
    ui->textBrowser->insertPlainText(result);
}
//Кнопка второй режим(готово)
void MainWindow::on_toolButton_clicked()
{
    ui->textBrowser->clear();
    risc.stepFlag = true;
}

//вывод перевода команд с двоичного кода на естественный язык(готов)
void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    QString str = ""; // через нее все собирается;
    for (int i = 0; i < risc.countCom; i++){
        str = "";
        switch (risc.getCommand(i)) {
            case risc.ADD:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "ADD" + regA + regB + "0000" +regCI;
                break;
            }
            case risc.ADDI: {
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "ADDI" + regA + regB +regCI;
                break;
            }
            case risc.NAND:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "NAND" + regA + regB + "0000" +regCI;
                break;
            }
            case risc.LUI:{
                break;
            }
            case risc.SW:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "SW" + regA + regB +regCI;
                break;
            }
            case risc.LW:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "LW" + regA + regB +regCI;
                break;
            }
            case risc.BEQ:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "BEQ" + regA + regB +regCI;
                break;
            }
            case risc.JAIR:{
                QString regA = QString::number(risc.getRegA(i));
                QString regB = QString::number(risc.getRegB(i));
                QString regCI = QString::number(risc.getRegCI(i));
                str = str + "JAIR" + regA + regB +regCI;
                break;
            }
        }
        ui->textBrowser->insertPlainText(str);
        ui->textBrowser->insertPlainText(" ");
        ui->textBrowser->append("");
    }
}
//Кнопка step(готово)
void MainWindow::on_toolButton_2_clicked()
{
    if (risc.stepFlag == true){
        if (risc.getstepByStep() == 0){
            ui->textBrowser->clear();
        }
        if (risc.getstepByStep() == risc.countCom){
            ui->textBrowser->insertPlainText("Текущее выполнение завершено");
            ui->textBrowser->insertPlainText(" ");
            ui->textBrowser->append("");
            ui->textBrowser->insertPlainText(QString:: number(risc.getMemory(risc.getMemory(1))));
            risc.stepFlag = false;
        }
        else{
            if (risc.stepFlag == true){
                QString str = outStepByStep(risc.getstepByStep());
                risc.stepByStepWork();
                ui->textBrowser->insertPlainText(str);
            }
        }
    }
    else{
        ui->textBrowser->clear();
        ui->textBrowser->insertPlainText("ERROR!Не активирован режим выполнить по шагам");
    }
}

//Кнопка стоп(готово)
void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    risc.stepFlag = false;
    ui->textBrowser->insertPlainText("Выполнение программы прекращено, по требованию пользователя");
}

//Вызов нового окна(готово)
void MainWindow::on_pushButton_4_clicked()
{
    on_action_Text_activated();
}

//При нажатие на кнопку редактора(готово)
void  MainWindow::on_action_Text_activated()
  {
    textWindow->show();
    this->close();
  }

//Запись в файл выполнения по шагам(готово)
void MainWindow::on_pushButton_6_clicked()
{
    QString fileout = QFileDialog::getSaveFileName();
    QFile file(fileout);
    QString str=ui->textBrowser->toPlainText();
    QStringList strList=str.split('\n');
    file.open(QIODevice::WriteOnly);
    for (int i = 0; i < strList.size(); i++){
        file.write(strList.at(i).toUtf8());
        file.write("\r\n");
    }
}
//Инициализатор машины(готово)
void MainWindow::on_pushButton_7_clicked()
{
    QString init = QFileDialog::getOpenFileName();
    QString com = QFileDialog::getOpenFileName();
    risc.parseRisc(init.toUtf8().data(), com.toUtf8().data());
    ui->textBrowser->insertPlainText("Программа загружена");
    ui->textBrowser->insertPlainText(" ");
    ui->textBrowser->append("");
    risc.initRegMemory();
    ui->textBrowser->insertPlainText("Машина готова");
    ui->textBrowser->insertPlainText(" ");
    ui->textBrowser->append("");
}
//Выполнить оперделенное количество шагов(готово)
void MainWindow::on_pushButton_5_clicked()
{
    int  numberStep = QInputDialog::getInt(0,
                                         "Несколько шагов",
                                         "Число шагов:",
                                         QLineEdit::Normal,
                                          0);
    int count = 0;
    while (count < numberStep){
        QString str = outStepByStep(risc.getCountForStep());
        risc.exactStepWork(numberStep);
        ui->textBrowser->insertPlainText(str);
        count++;
    }


}

//Выход(готово)
void MainWindow::on_action_triggered()
{
    risc.destroyed();
    this->close();
}

//Точка останова
void MainWindow::on_toolButton_3_clicked()
{
    int  number = QInputDialog::getInt(0,
                                         "BreakPoint",
                                         "Введите номер строки:",
                                         QLineEdit::Normal,
                                          0);
    risc.bPoint(number);
    ui->textBrowser->insertPlainText(QString::number(risc.getCount()));
    QString result = "";
    result += "Вывод состояний регистров машины: \r\n";
    for(int i = 0; i < risc.REG; i++){
        result += "Регистр [" + QString:: number(i) + "] = " + QString:: number(risc.getRegMemory(i)) + "\r\n";
    }
    result += "Вывод состояния памяти машины: \r\n";
    for(int i = 0; i <= risc.getMemory(1); i++){
        result += "Ячейка [" + QString:: number(i) + "] = " + QString:: number(risc.getMemory(i)) + "\r\n";
    }
    ui->textBrowser->insertPlainText(result);
}
