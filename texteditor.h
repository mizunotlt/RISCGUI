#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

signals:
    void mainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TextEditor *ui;
};

#endif // TEXTEDITOR_H
