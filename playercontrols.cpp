#include <QMenu>
#include <QCursor>
#include <functional>

#include "playercontrols.h"

using namespace std::placeholders;

const QString PlayerControls::m_iconPlay(":/controls/play.png");
const QString PlayerControls::m_iconPause(":/controls/pause.png");

PlayerControls::PlayerControls(QWidget *parent) :
    QWidget(parent), m_isplaying(false), m_fastLevel(100), m_playMode(QMediaPlaylist::Sequential), m_mode(BEGIN)
{

    setupUi(this);
    player_controls_previous->setEnabled(false);

    //Connect ui slots
    connect(player_controls_play,&QAbstractButton::clicked, this, &PlayerControls::handlePlay);
    connect(player_controls_stop,&QAbstractButton::clicked, this, &PlayerControls::handleStop);
    connect(player_controls_next,&QAbstractButton::clicked, this, &PlayerControls::handleNext);
    connect(player_controls_previous,&QAbstractButton::clicked, this, &PlayerControls::handlePrevious);
    connect(player_controls_speed,&QAbstractButton::clicked, this, &PlayerControls::handleSpeed);
    connect(player_controls_play_mode,&QAbstractButton::clicked, this, &PlayerControls::handlePlayMode);
}

PlayerControls::~PlayerControls()
{

}

// ---- Public slots

void PlayerControls::setPlay()
{
    m_isplaying=true;
    player_controls_play->setIcon(QIcon(m_iconPause));
    emit play();
    if(m_mode==BEGIN)
        setStatus(RUNNING);
}

void PlayerControls::setPause()
{
    m_isplaying=false;
    player_controls_play->setIcon(QIcon(m_iconPlay));
    emit pause();
}

void PlayerControls::setStop()
{
     handleStop();
}

void PlayerControls::setSpeed(int level)
{
    handleSpeedChanged(level);
}

void PlayerControls::setNext()
{
    handleNext();
}

void PlayerControls::setPrevious()
{
    handlePrevious();
}

void PlayerControls::setMode(Mode_t mode)
{
    handleMode(mode);
}

void PlayerControls::setPlayMode(QMediaPlaylist::PlaybackMode playMode){
    if(playMode==QMediaPlaylist::Sequential)
        handlePlayModeChangeSequential();
    else if(playMode==QMediaPlaylist::Loop)
        handlePlayModeChangeLoop();
    else if(playMode==QMediaPlaylist::Random)
        handlePlayModeChangeRandom();
}

void PlayerControls::setStatus(bool enabled)
{
    handleStatus(enabled);
}

void PlayerControls::reset()
{
    handleReset();
}

// ---- Private slots

void PlayerControls::handlePlay()
{
    if( m_isplaying)
        setPause();
    else
        setPlay();
}

void PlayerControls::handleStop()
{
    m_isplaying=false;
    player_controls_play->setIcon(QIcon(m_iconPlay));
    emit stop();
}

void PlayerControls::handleSpeed()
{
    QMenu changeSpeed(this);
    QAction* level_1 = changeSpeed.addAction(tr("0.25"));
    QAction* level_2 = changeSpeed.addAction(tr("0.5"));
    QAction* level_3 = changeSpeed.addAction(tr("normal"));
    QAction* level_4 = changeSpeed.addAction(tr("2"));
    QAction* level_5 = changeSpeed.addAction(tr("4"));

    level_1->setCheckable(true);
    level_2->setCheckable(true);
    level_3->setCheckable(true);
    level_4->setCheckable(true);
    level_5->setCheckable(true);

    switch(m_fastLevel)
    {
    case 25:
        level_1->setChecked(true);
        break;
    case 50:
        level_2->setChecked(true);
        break;
    case 100:
        level_3->setChecked(true);
        break;
    case 200:
        level_4->setChecked(true);
        break;
    case 400:
        level_5->setChecked(true);
        break;
    }

    connect(level_1, &QAction::toggled, this, &PlayerControls::handleSpeedLevel1 );
    connect(level_2, &QAction::toggled, this, &PlayerControls::handleSpeedLevel2 );
    connect(level_3, &QAction::toggled, this, &PlayerControls::handleSpeedLevel3 );
    connect(level_4, &QAction::toggled, this, &PlayerControls::handleSpeedLevel4 );
    connect(level_5, &QAction::toggled, this, &PlayerControls::handleSpeedLevel5 );

    changeSpeed.exec(QCursor().pos());
}

void PlayerControls::handleSpeedLevel1()
{
    m_fastLevel = 25;
    emit speedChanged(25);

}

void PlayerControls::handleSpeedLevel2()
{
    m_fastLevel = 50;
    emit speedChanged(50);
}

void PlayerControls::handleSpeedLevel3()
{
    m_fastLevel = 100;
    emit speedChanged(100);
}

void PlayerControls::handleSpeedLevel4()
{
    m_fastLevel = 200;
    emit speedChanged(200);
}


void PlayerControls::handleSpeedLevel5()
{
    m_fastLevel = 400;
    emit speedChanged(400);
}


void PlayerControls::handleSpeedChanged(int level)
{
    m_fastLevel=level;
    if(level<100)
        emit fastRewind(level);
    else
        emit fastForward(level);
}

void PlayerControls::handleNext()
{
    emit next();
    if(m_mode==BEGIN)
        setStatus(RUNNING);
}

void PlayerControls::handlePrevious()
{
    emit previous();
}

void PlayerControls::handleStatus(bool enabled)
{
    player_controls_play->setEnabled(enabled);
    player_controls_stop->setEnabled(enabled);

    player_controls_next->setEnabled(enabled);
    player_controls_previous->setEnabled(enabled);

    player_controls_speed->setEnabled(enabled);

    player_controls_play_mode->setEnabled(enabled);

}

void PlayerControls::handleReset()
{
    setStop();
    setPlayMode(QMediaPlaylist::Sequential);
    setMode(BEGIN);
    setStatus(false);
}

void PlayerControls::handlePlayMode()
{
    QMenu playMode(this);
    QAction* sequential = playMode.addAction(tr("Lecture standard"));
    QAction* loop = playMode.addAction(tr("Lecture en bouble"));
    QAction* random = playMode.addAction(tr("Lecture aléatoire"));

    sequential->setCheckable(true);
    loop->setCheckable(true);
    random->setCheckable(true);

    if(m_playMode==QMediaPlaylist::Sequential)
        sequential->setChecked(true);
    else if(m_playMode==QMediaPlaylist::Loop)
        loop->setChecked(true);
    else if(m_playMode==QMediaPlaylist::Random)
        random->setChecked(true);

    connect(sequential, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeSequential );
    connect(loop, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeLoop );
    connect(random, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeRandom );

    playMode.exec(QCursor().pos());
}

void PlayerControls::handlePlayModeChangeSequential()
{
    m_playMode = QMediaPlaylist::Sequential;
    emit playModeChanged(QMediaPlaylist::Sequential);
}

void PlayerControls::handlePlayModeChangeLoop()
{
    m_playMode = QMediaPlaylist::Loop;
    emit playModeChanged(QMediaPlaylist::Loop);
}

void PlayerControls::handlePlayModeChangeRandom()
{
    m_playMode = QMediaPlaylist::Random;
    emit playModeChanged(QMediaPlaylist::Random);
}

void PlayerControls::handleMode(Mode_t mode)
{
    m_mode = mode;
    switch (mode)
    {
    case BEGIN:
        player_controls_previous->setEnabled(false);
        emit modeChanged(mode);
        break;
    case RUNNING:
        player_controls_previous->setEnabled(true);
        emit modeChanged(mode);
        break;
    case ENDING:
        player_controls_next->setEnabled(false);
        emit modeChanged(mode);
        break;
    }
}
