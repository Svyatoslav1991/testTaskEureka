#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QMediaPlayer>
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /// @brief настройка приложения
    void settingProgramm();//настройка приложения

    /// @brief создать связь сигналов и слотов
    void createSignalSlotConnections();//создать связь сигналов и слотов

private slots:
    /// @brief нажатие на кнопку "ОТКРЫТЬ ВТОРОЕ ОКНО"
    void on_openSecondWindow_button_clicked();

    /// @brief слот, заканчивающий работу приложения
    void closeAppSlot();

    /// @brief нажатие на Звук->Вкл.
    void soundOn_action_clicked();

    /// @brief нажатие на Звук->Выкл.
    void soundOff_action_clicked();

    /// @brief изменение состояния фоновой музыки
    void backgroundMusicStateChangedSlot(QMediaPlayer::State state);//изменение состояния фоновой музыки

    /// @brief нажатие "О программе..."
    void showInfoMessageSlot();//нажатие "О программе..."

private:
    Ui::MainWindow *ui;

    /// @brief указатель на второе окно
    SecondWindow* m_pSecondWindow;

    /// @brief флаг работы звука программы
    bool m_isSoundOn;

    /// @brief короткая музыка нажатия на кнопку
    std::unique_ptr<QMediaPlayer> m_pShortSound;

    /// @brief фоновая музыка
    std::unique_ptr<QMediaPlayer> m_pBackgroundSound;

    /// @brief фоновая картинка
    QImage m_backgroundImage;

    // QWidget interface
protected:
    /// @brief изменение размеров главного окна
    virtual void resizeEvent(QResizeEvent *event);

};
#endif // MAINWINDOW_H
