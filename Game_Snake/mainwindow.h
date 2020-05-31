#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLine>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include "Snake.h"
#include "Game_Field.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
     //параметры
public:
     QTimer* game_timer;
     Snake* snake;
     Game_Field* game;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void getParametersByLevel(int level,int* points,int* target_points);

private slots:

    void refresh_game_information();
    void death_restart();
    void success_restart();
    void on_exitGameButton_clicked();

    void on_startGameButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    QLine* line1;
    QLineEdit* lineedit;
    QLabel* label1;
    QFrame* frame1;
    Snake* snk;
};
#endif // MAINWINDOW_H
