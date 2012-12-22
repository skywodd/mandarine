#include "playercontrols.h"

const QString PlayerControls::m_iconPlay(":/controls/controls/play.png");
const QString PlayerControls::m_iconPause(":/controls/controls/pause.png");

PlayerControls::PlayerControls(QWidget *parent) :
    QWidget(parent), m_isplaying(false), m_loopMode(QMediaPlaylist::Sequential)
{

    setupUi(this);

    setMode(BEGIN);

    //Connect ui slots
    connect(player_controls_play,&QAbstractButton::clicked, this, &PlayerControls::handlePlay);
    connect(player_controls_stop,&QAbstractButton::clicked, this, &PlayerControls::handleStop);
    connect(player_controls_speed,&QAbstractButton::clicked, this, &PlayerControls::handleSetSpeed);
    connect(player_controls_next,&QAbstractButton::clicked, this, &PlayerControls::handleNext);
    connect(player_controls_previous,&QAbstractButton::clicked, this, &PlayerControls::handlePrevious);
    connect(player_controls_play_mode,&QAbstractButton::clicked, this, &PlayerControls::handlePlayMode);
    //TODO changer boutons de séléction du mode
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
    handleSetSpeed(level);
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

void PlayerControls::setStatus(bool enabled)
{
    handleStatus(enabled);
}

void PlayerControls::reset()
{
    m_isplaying=false;
    m_loopMode=QMediaPlaylist::Sequential;
    setMode(BEGIN);
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

void PlayerControls::handleSetSpeed(int level)
{
    m_fastLevel=level;
    emit speedChanged(level);
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
    player_controls_previous->setEnabled(enabled);

    player_controls_speed->setEnabled(enabled);
    player_controls_next->setEnabled(enabled);
//    player_controls_random->setEnabled(enabled);
//    player_controls_loop->setEnabled(enabled);
}
void PlayerControls::handleMode(Mode_t mode)
{
    switch (mode)
    {
    case BEGIN:
//        player_controls_fast_rewind->setEnabled(false);
        emit playModeChanged(BEGIN);
        break;
    case RUNNING:
//        player_controls_fast_rewind->setEnabled(true);
        emit playModeChanged(RUNNING);
        break;
    }
}

void PlayerControls::handleReset()
{
    m_isplaying = false;
    m_loopMode = QMediaPlaylist::Sequential;
    m_mode = BEGIN;
    setStatus(false);
}

void PlayerControls::handlePlayMode()
{

}
