#include "Game_Field.h"
#include <QPalette>
#include <memory>

//Конструктор и деструктор класса Game_Field
Game_Field::Game_Field(QWidget* parent,int new_field_X, int new_field_Y, int new_step) : QFrame(parent)
{
    field_X = new_field_X;
    field_Y = new_field_Y;
    this->setGeometry(25,25,field_X,field_Y);
    step = new_step;
    default_snake_size = 3;
    default_snake_X = field_X/2-step;
    default_snake_Y = field_Y/2-step;
    this->setFrameStyle(QFrame::Panel);
    this->setLineWidth(step/2);
    this->setFocus();
    //Инициализация яблока
    apple = new QFrame(this);
    apple->setFrameShape(QFrame::Box);
    apple->setGeometry(50,50,step,step);
    QPalette pal;
    pal.setColor(QPalette::Background,Qt::green);
    apple->setPalette(pal);
    apple->setAutoFillBackground(true);
    apple->hide();
    //Инициализация змейки
    snake = new Snake(this,default_snake_size,default_snake_X,default_snake_Y,step);
    snake->setWindowFlag(Qt::WindowStaysOnTopHint);
    //Инициализация барьеров периметра
    for(int i=0;i<4;i++)
    {
        barriers.push_back(new QFrame(this));
        pal.setColor(QPalette::Background,Qt::darkYellow);
        barriers[i]->setPalette(pal);
        barriers[i]->setAutoFillBackground(true);
    }
    barriers[0]->setGeometry(step/2,step/2,step/2,field_Y-step);
    barriers[1]->setGeometry(step/2,step/2,field_X-step,step/2);
    barriers[2]->setGeometry(step/2,field_Y-step,field_X-step,step/2);
    barriers[3]->setGeometry(field_X-step,step/2,step/2,field_Y-step);

    //Инициализация звуков
    eat_sound = new QSound(":/sounds/EAT2.wav",this);
    death_sound = new QSound(":/sounds/Death.wav",this);
    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/music/playing 1.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 2.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 3.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 4.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 5.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 6.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 7.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 8.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 9.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 10.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 11.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 12.mp3"));
    playlist->addMedia(QUrl("qrc:/music/playing 13.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer(this);
    music->setAudioRole(QAudio::GameRole);
    music->setPlaylist(playlist);
    music->setPosition(1);
    music->setVolume(100);



    //Инициализация игрового таймера
    game_timer = new QTimer(this);
    //Инициализация таймера смерти змейки
    death_timer = new QTimer(this);
    //Инициализация сигналов и слотов
    connect(game_timer,SIGNAL(timeout()),this,SLOT(gameCycle()));
    connect(death_timer,SIGNAL(timeout()),this,SLOT(deathCycle()));

    //Инициализация генератора случайных чисел
    QTime time = QTime::currentTime();
    qsrand(time.msec());


}

Game_Field::~Game_Field()
{
    delete snake;
    delete game_timer;
    delete apple;
    for (int i=0;i<barriers.size();i++)
        delete barriers[i];
    barriers.clear();

}


//Функции интерфейса класса
int Game_Field::getLevel()
{
   return level;
}
int Game_Field::getLifes()
{
    return lifes;
}
int Game_Field::getDefaultSnakeSize()
{
    return default_snake_size;
}
int Game_Field::getPoints()
{
    return points;
}
int Game_Field::getTargetPoints()
{
    return target_points;
}
bool Game_Field::setLevel(int new_level)
{
    if(game_stat == wait)
    {
        level = new_level;
        return true;
    }
    else
    {
        return false;
    }

}
game_status Game_Field::getGameStatus()
{
    return game_stat;
}
bool Game_Field::setLifes(int new_lives)
{
    if(game_stat == wait)
    {
        lifes = new_lives;
        emit refresh_signal();
        return true;
    }
    else
    {
        return false;
    }
}
bool Game_Field::setDefaultSnakeSize(int new_snake_size)
{
    if(game_stat == wait)
    {
        default_snake_size = new_snake_size;
        return true;
    }
    else
    {
        return false;
    }
}
bool Game_Field::setPoints(int new_points)
{
    if(game_stat == wait)
    {
        points = new_points;
        emit refresh_signal();
        return true;
    }
    else
    {
        return false;
    }

}
bool Game_Field::setTargetPoints(int new_target_points)
{
    if(game_stat == wait)
    {
        target_points = new_target_points;
        emit refresh_signal();
        return true;
    }
    else
    {
        return false;
    }
}
bool Game_Field::setAllGameParameters(int new_points, int new_target_points, int new_lifes, int new_level)
{
    if(game_stat == wait)
    {
        points = new_points;
        target_points = new_target_points;
        lifes = new_lifes;
        level = new_level;
        emit refresh_signal();
        return true;
    }
    else
    {
        return false;
    }
}

//Функция обработки нажатия клавиш
void Game_Field::keyPressEvent(QKeyEvent* key_event)
{

    if(key_event->key() == Qt::Key_Up)
        snake->setDirection(s_up);
    if(key_event->key() == Qt::Key_Down)
        snake->setDirection(s_down);
    if(key_event->key() == Qt::Key_Left)
        snake->setDirection(s_left);
    if(key_event->key() == Qt::Key_Right)
        snake->setDirection(s_right);
    this->setFocus();
}

//Рабочие функции и слоты класса
void Game_Field::gameCycle()                        //Главный цикл игры
{

    if(apple->isHidden())                           //Яблоко отсутствует на поле, нужно отрисовать
    {
        do
            {

                int x_apple,y_apple;
                x_apple = qrand() % (field_X/step)*step;
                y_apple = qrand()%(field_Y/step)*step;
                apple->setGeometry(x_apple,y_apple,step,step);
            }
        while((snake->checkAppleIntersection(apple)) || (this->checkBarrierIntersection(apple)));
     //   while(snake->checkAppleIntersection(apple));
        QRect test = apple->geometry();
        int test2 = apple->frameShape();
        apple->show();
        snake->Move();
    }
    else                                            //Яблоко есть на поле, проверяем, съела ли его змейка
    {
        if(snake->checkAppleIntersection(apple))    //Змейка съела яблоко
        {
            if((!snake->isMoveAcross())&&(!this->checkBarrierIntersection(snake->getNextPosition())))
            {
                snake->Rise();
                apple->hide();
                points++;
                emit refresh_signal();

                if(target_points == points)
                    emit success_signal();
            }
            else
                death();
        }
        else                                        //Змейка не съела яблоко
        {
            if((!snake->isMoveAcross())&&(!this->checkBarrierIntersection(snake->getNextPosition())))
            {
                snake->Move();
                if(snake->checkAppleIntersection(apple))
                    eat_sound->play();
            }
            else
                death();
        }

    }


}
void Game_Field::deathCycle()
{
    if(!snake->isHidden())
        snake->hide();
    else
        snake->show();
    death_time--;
    if(death_time==0)
    {
        death_timer->stop();
        emit death_signal();
    }
}
void Game_Field::startGame() //Запуск игры
{
    game_timer->start(1000/(level+1));
    this->setFocus();
    game_stat = play;
}
void Game_Field::stopGame()//Останов игры
{
    game_timer->stop();
    game_stat = wait;
}
void Game_Field::resetGame()//Сброс игрового поля
{
    delete snake;
    //Переинициализация змейки
    snake = new Snake(this,default_snake_size,default_snake_X,default_snake_Y,step);
    snake->setWindowFlag(Qt::WindowStaysOnTopHint);
    snake->show();
    apple->hide();
    game_stat = wait;
    points = 0;
    emit refresh_signal();
}
bool Game_Field::checkBarrierIntersection(QFrame* object)
{
    QRect rect_barrier, rect_object;
    rect_object = object->geometry();
    int test = object->frameShape();
    for(QVector<QFrame*>::iterator iter=barriers.begin(); iter!=barriers.end();iter++)
    {
        QFrame* frame_temp = *iter;
        QRect rect_inter;
        rect_barrier = frame_temp->geometry();
        rect_inter = rect_barrier&rect_object;
        if(rect_inter.isNull())
            continue;
        else
            return true;
    }
    test = object->frameShape();
    return false;
}
bool Game_Field::checkBarrierIntersection(QRect object)
{
    QRect rect_barrier;
    QRect rect_inter;
    for(QVector<QFrame*>::iterator iter=barriers.begin(); iter!=barriers.end();iter++)
    {
        QFrame* frame_temp = *iter;
        rect_barrier = frame_temp->geometry();
        rect_inter = rect_barrier&object;
        if(rect_inter.isNull())
            continue;
        else
            return true;
    }
    return false;
}
void Game_Field::death()                                //функция обработки смерти змейки
{
    game_stat = snake_death;
    emit refresh_signal();
    death_sound->play();
    death_time = 20;
    game_timer->stop();
    death_timer->start(100);


}

void Game_Field::startMusic()
{
    music->play();
}

void Game_Field::stopMusic()
{
    music->stop();
}
