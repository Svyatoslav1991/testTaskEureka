#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>


SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Второе окно");
    this->resize(300, 200);
}

//-----------------------------------------------------------

SecondWindow::~SecondWindow()
{
    delete ui;
}

//-----------------------------------------------------------

// нажатие на кнопку "Создать файл и выйти"
void SecondWindow::on_createFile_button_clicked()
{
    QByteArray byteArray = "Миру мир!";
    QFile file("output.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(byteArray);
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи output.txt");
    }

    emit closeAppSignal();
    this->close();
}
