#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyboardHandler>
#include <QComponent>
#include <Qt3DCore>
#include <QTimer>
#include <QTimerEvent>
#include "Game_Field.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    game = new Game_Field(this,300,300,10);

    /*
    //Инициализация игрового поля
    QFrame* Game_Field = new QFrame(this);
    Game_Field->setFrameStyle(QFrame::Panel);
    Game_Field->setGeometry(50,50,500,500);
    Game_Field->show();
    //Инициализация змейки
    snake = new Snake(Game_Field,3,240,240);
    snake->setGeometry(0,0,500,500);
    this->setFocus();

    //Инициализация таймера
    game_timer = new QTimer(this);
    game_timer->start(1000);
    */


    ui->setupUi(this);

    ui->PointsLabel->hide();
    ui->Points->hide();
    ui->Targetlabel->hide();
    ui->Target->hide();
    ui->LifesLabel->hide();
    ui->Lifes->hide();
    ui->LevelLabel->hide();
    ui->Level->hide();
    ui->LevelNameLabel->hide();
    ui->startButton->hide();
    //сигналы и слоты
    connect(game,SIGNAL(refresh_signal()),this,SLOT(refresh_game_information()));
    connect(game,SIGNAL(death_signal()),this,SLOT(death_restart()));
    connect(game,SIGNAL(success_signal()),this,SLOT(success_restart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_game_information()
{
    ui->Points->setText(QString::number(game->getPoints()));
    ui->Target->setText(QString::number(game->getTargetPoints()));
    ui->Lifes->setText(QString::number(game->getLifes()));
    ui->Level->setText(QString::number(game->getLevel()));
    ui->LevelNameLabel->setText("Уровень " + QString::number(game->getLevel()));

}

void MainWindow::death_restart()
{
    if(game->getLifes()>0)
    {
        game->resetGame();
        game->setLifes(game->getLifes()-1);
        game->startGame();
    }
    else
    {
        game->stopGame();
        game->resetGame();
        game->stopMusic();
        ui->LevelNameLabel->setText("Вы проиграли!");
        ui->LevelNameLabel->show();
        ui->PointsLabel->hide();
        ui->Points->hide();
        ui->Targetlabel->hide();
        ui->Target->hide();
        ui->LifesLabel->hide();
        ui->Lifes->hide();
        ui->LevelLabel->hide();
        ui->Level->hide();
        ui->startButton->hide();
        ui->startGameButton->show();
        ui->exitGameButton->show();
    }
}

void MainWindow::success_restart()
{
    if(game->getLevel() < 10)
    {
        int points,target_points,level;
        game->stopGame();
        game->resetGame();
        level=game->getLevel();
        level++;
        getParametersByLevel(level,&points,&target_points);
        game->setAllGameParameters(points,target_points,game->getLifes(),level);
        ui->LevelNameLabel->show();
        ui->startButton->show();
    }
    else
    {
        game->stopGame();
        game->resetGame();
        game->stopMusic();
        ui->LevelNameLabel->setText("Вы выиграли!");
        ui->LevelNameLabel->show();
        ui->PointsLabel->hide();
        ui->Points->hide();
        ui->Targetlabel->hide();
        ui->Target->hide();
        ui->LifesLabel->hide();
        ui->Lifes->hide();
        ui->LevelLabel->hide();
        ui->Level->hide();
        ui->startButton->hide();
        ui->startGameButton->show();
        ui->exitGameButton->show();
     }

}

void MainWindow::getParametersByLevel(int level, int* points, int* target_points)
{
    switch(level)
    {
        case 1:
            *points = 0;
            *target_points = 30;
            break;
        case 2:
            *points = 0;
            *target_points = 60;
            break;
        case 3:
            *points = 0;
            *target_points = 90;
            break;
        case 4:
            *points = 0;
            *target_points = 120;
            break;
        case 5:
            *points = 0;
            *target_points = 150;
            break;
        case 6:
            *points = 0;
            *target_points = 180;
            break;
        case 7:
            *points = 0;
            *target_points = 210;
            break;
        case 8:
            *points = 0;
            *target_points = 240;
            break;
        case 9:
            *points = 0;
            *target_points = 270;
            break;
        case 10:
            *points = 0;
            *target_points = 300;
            break;
        default:
            break;
    }
}

void MainWindow::on_exitGameButton_clicked()
{
    close();
}

void MainWindow::on_startGameButton_clicked()
{
    ui->startGameButton->hide();
    ui->exitGameButton->hide();
    ui->LevelNameLabel->setText("Уровень 1");
    ui->LevelNameLabel->show();
    ui->startButton->setGeometry(100,130,160,40);
    ui->startButton->show();

    game->setAllGameParameters(0,30,5,1);
    ui->PointsLabel->show();
    ui->Points->show();


    ui->Targetlabel->show();
    ui->Target->show();

    ui->Lifes->show();
    ui->LifesLabel->show();


    ui->LevelLabel->show();
    ui->Level->show();

}

void MainWindow::on_startButton_clicked()
{
    game->startGame();
    game->startMusic();
    ui->startButton->hide();
    ui->LevelNameLabel->hide();

}
