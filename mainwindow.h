#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "RiscMachine.h"
#include "texteditor.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_action_Text_activated();

private slots:
    void on_toolButton_4_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_action_triggered();

    void on_toolButton_3_clicked();

private:
    Ui::MainWindow *ui;
    TextEditor *textWindow;
};

#endif // MAINWINDOW_H
