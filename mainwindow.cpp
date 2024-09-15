#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settingProgramm();
    this->createSignalSlotConnections();

}

//----------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------------------------------------------------------------------------------

//настройка приложения
void MainWindow::settingProgramm()
{
    this->resize(400, 300);
    this->setWindowTitle("Главное окно");
    this->setWindowIcon(QIcon(":/icons/icons/rocket.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    m_pSecondWindow = nullptr;
    m_isSoundOn = true;

    ui->sound_menu->setIcon(QIcon(":/icons/icons/notes.ico"));
    ui->soundOn_action->setIcon(QIcon(":/icons/icons/soundOn.ico"));
    ui->soundOn_action->setText("Вкл. \u2713");
    ui->soundOn_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    ui->soundOff_action->setIcon(QIcon(":/icons/icons/soundOff.ico"));
    ui->soundOff_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    ui->about_action->setIcon(QIcon(":/icons/icons/questionmark.ico"));
    ui->about_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));

    m_backgroundImage.load(":/pictures/pictures/future.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);

    m_pShortSound = std::make_unique<QMediaPlayer>();
    m_pShortSound->setMedia(QUrl("qrc:/music/sounds/short.mp3"));

    m_pBackgroundSound = std::make_unique<QMediaPlayer>();
    m_pBackgroundSound->setMedia(QUrl("qrc:/music/sounds/dendy.mp3"));
    m_pBackgroundSound->setVolume(30);
    m_pBackgroundSound->play();
}

//----------------------------------------------------------------------------------------------------

//создать связь сигналов и слотов
void MainWindow::createSignalSlotConnections()
{
    connect(ui->soundOn_action, SIGNAL(triggered(bool)), this, SLOT(soundOn_action_clicked()));
    connect(ui->soundOff_action, SIGNAL(triggered(bool)), this, SLOT(soundOff_action_clicked()));
    connect(m_pBackgroundSound.get(), SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(backgroundMusicStateChangedSlot(QMediaPlayer::State)));
    connect(ui->about_action, SIGNAL(triggered(bool)), this, SLOT(showInfoMessageSlot()));
}

//----------------------------------------------------------------------------------------------------

// нажатие на кнопку "ОТКРЫТЬ ВТОРОЕ ОКНО"
void MainWindow::on_openSecondWindow_button_clicked()
{
    if(m_pSecondWindow)
    {
        delete m_pSecondWindow;
    }

    m_pSecondWindow = new SecondWindow(this);
    connect(m_pSecondWindow, SIGNAL(closeAppSignal()), this, SLOT(closeAppSlot()));

    m_pSecondWindow->show();
}

//----------------------------------------------------------------------------------------------------

// слот, заканчивающий работу приложения
void MainWindow::closeAppSlot()
{
    this->close();
}

//----------------------------------------------------------------------------------------------------

//нажатие на Звук->Вкл.
void MainWindow::soundOn_action_clicked()
{
    if(!m_isSoundOn)
    {
        m_isSoundOn = true;
        ui->soundOn_action->setText("Вкл. \u2713");
        ui->soundOff_action->setText("Выкл.");
        m_pBackgroundSound->play();
    }
}

//----------------------------------------------------------------------------------------------------

//нажатие на Звук->Выкл.
void MainWindow::soundOff_action_clicked()
{
    if(m_isSoundOn)
    {
        m_isSoundOn = false;
        ui->soundOn_action->setText("Вкл.");
        ui->soundOff_action->setText("Выкл. t\u2713");
        m_pBackgroundSound->pause();
    }
}

//----------------------------------------------------------------------------------------------------

//изменение состояния фоновой музыки
void MainWindow::backgroundMusicStateChangedSlot(QMediaPlayer::State state)
{
    //бесконечное воспроизведение
    if(state == QMediaPlayer::StoppedState)
    {
        m_pBackgroundSound->play();
    }
}

//----------------------------------------------------------------------------------------------------

//нажатие "О программе..."
void MainWindow::showInfoMessageSlot()
{
    QMessageBox::information(this, "Тестовое задание в компанию \"Эврика\"",
                             "Создать графическое приложение с использование библиотека Qt, содержащее две пустые формы, содержащие кнопку строго по центру:\n первая форма – главное окно. При нажатии на кнопку открывается вторая форма.\n вторая форма – диалог. При нажатии на кнопку создается текстовый файл, содержащий строку текста «Миру мир!» и завершается работа приложения.");
}

// изменение размеров главного окна
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);

    Q_UNUSED(event)
}
