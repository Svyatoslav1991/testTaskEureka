#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    /// @brief нажатие на кнопку "Создать файл и выйти"
    void on_createFile_button_clicked();

signals:
    /// @brief сигнал, соединяющийся с главным окном, для закрытия приложения
    void closeAppSignal();

private:
    Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
