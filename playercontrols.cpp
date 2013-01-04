/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 *
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 *
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

/* Includes */
#include <QMenu>
#include <QCursor>
#include "playercontrols.h"

/* Static members initialization */
const QString PlayerControls::m_iconPlay(":/controls/play.png");
const QString PlayerControls::m_iconPause(":/controls/pause.png");

PlayerControls::PlayerControls(QWidget *parent) :
    QWidget(parent), m_isplaying(false),
    m_speedLevel(SPEED_NORMAL), m_playMode(QMediaPlaylist::Sequential),
    m_mode(MODE_BEGIN)
{
    /* Setup UI */
    setupUi(this);
    setMode(MODE_BEGIN);

    /* Connect button signals to slots */
    connect(player_controls_play, &QAbstractButton::clicked, this, &PlayerControls::setTogglePlayPause);
    connect(player_controls_stop, &QAbstractButton::clicked, this, &PlayerControls::setStop);
    connect(player_controls_next, &QAbstractButton::clicked, this, &PlayerControls::setNext);
    connect(player_controls_previous, &QAbstractButton::clicked, this, &PlayerControls::setPrevious);
    connect(player_controls_speed, &QAbstractButton::clicked, this, &PlayerControls::handleSpeedLevel);
    connect(player_controls_play_mode, &QAbstractButton::clicked, this, &PlayerControls::handlePlayMode);
}

PlayerControls::~PlayerControls()
{
}

void PlayerControls::setTogglePlayPause()
{
    /* toggle play / pause */
    if (m_isplaying)
        setPause();
    else
        setPlay();
}

void PlayerControls::setPlay()
{
    /* Force widget state to play */
    m_isplaying = true;
    player_controls_play->setIcon(QIcon(m_iconPause));
    emit play();
}

void PlayerControls::setPause()
{
    /* Force widget state to pause */
    m_isplaying = false;
    player_controls_play->setIcon(QIcon(m_iconPlay));
    emit pause();
}

void PlayerControls::setStop()
{
    /* Force widget state to stop */
    m_isplaying = false;
    player_controls_play->setIcon(QIcon(m_iconPlay));
    emit stop();
}

void PlayerControls::setSpeed(Speed_t speed)
{
    /* Store speed modification level */
    m_speedLevel = speed;

    /* Emit speedChanged signal according factor */
    switch(speed) {
    case SPEED_025:
        emit speedChanged(0.25);
        break;

    case SPEED_05:
        emit speedChanged(0.5);
        break;

    case SPEED_NORMAL:
        emit speedChanged(1);
        break;

    case SPEED_2:
        emit speedChanged(2.0);
        break;

    case SPEED_4:
        emit speedChanged(4.0);
        break;
    }
}

void PlayerControls::setPlayMode(QMediaPlaylist::PlaybackMode playMode){

    /* Store playback mode */
    m_playMode = playMode;

    /* Emit the playModeChanged changed signal */
    emit playModeChanged(playMode);
}

void PlayerControls::setNext()
{
    /* Emit next() signal */
    if(m_mode != MODE_ENDING)
        emit next();
}

void PlayerControls::setPrevious()
{
    /* Emit previous() signal */
    if(m_mode != MODE_BEGIN)
        emit previous();
}

void PlayerControls::setMode(Mode_t mode)
{
    /* Store mode */
    m_mode = mode;

    /* Apply display mode */
    switch(mode) {
    case MODE_BEGIN:
        player_controls_previous->setEnabled(false);
        player_controls_next->setEnabled(true);
        break;

    case MODE_RUNNING:
        player_controls_previous->setEnabled(true);
        player_controls_next->setEnabled(true);
        break;

    case MODE_ENDING:
        player_controls_previous->setEnabled(true);
        player_controls_next->setEnabled(false);
        break;
    }
}

void PlayerControls::setStatus(bool enabled)
{
    /* Set buttons states */
    player_controls_play->setEnabled(enabled);
    player_controls_stop->setEnabled(enabled);
    player_controls_next->setEnabled(enabled);
    player_controls_previous->setEnabled(enabled);
    player_controls_speed->setEnabled(enabled);
    player_controls_play_mode->setEnabled(enabled);

    /* Restore display mode */
    if(enabled)
        setMode(m_mode);
}

void PlayerControls::reset()
{
    /* Reset widget to his default state */
    setStop();
    setPlayMode(QMediaPlaylist::Sequential);
    setMode(MODE_BEGIN);
    setStatus(false);
}

void PlayerControls::handleSpeedLevel()
{
    QMenu changeSpeed(this);

    /* Craft menu items */
    QAction* level_1 = changeSpeed.addAction(tr("x0.25 (trés lent)"));
    QAction* level_2 = changeSpeed.addAction(tr("x0.5 (lent)"));
    QAction* level_3 = changeSpeed.addAction(tr("x1 (normal)"));
    QAction* level_4 = changeSpeed.addAction(tr("x2 (rapide)"));
    QAction* level_5 = changeSpeed.addAction(tr("x4 (trés rapide)"));

    /* Set items checkable */
    level_1->setCheckable(true);
    level_2->setCheckable(true);
    level_3->setCheckable(true);
    level_4->setCheckable(true);
    level_5->setCheckable(true);

    /* Check the currently selected mode */
    switch(m_speedLevel) {
    case SPEED_025:
        level_1->setChecked(true);
        break;
    case SPEED_05:
        level_2->setChecked(true);
        break;
    case SPEED_NORMAL:
        level_3->setChecked(true);
        break;
    case SPEED_2:
        level_4->setChecked(true);
        break;
    case SPEED_4:
        level_5->setChecked(true);
        break;
    }

    /* Connect items signals to slots */
    connect(level_1, &QAction::triggered, this, &PlayerControls::handleSpeedLevel1);
    connect(level_2, &QAction::triggered, this, &PlayerControls::handleSpeedLevel2);
    connect(level_3, &QAction::triggered, this, &PlayerControls::handleSpeedLevel3);
    connect(level_4, &QAction::triggered, this, &PlayerControls::handleSpeedLevel4);
    connect(level_5, &QAction::triggered, this, &PlayerControls::handleSpeedLevel5);

    /* Show menu at the current cursor position */
    changeSpeed.exec(QCursor().pos());

    /* Disconnect signals */
    disconnect(level_1, &QAction::triggered, this, &PlayerControls::handleSpeedLevel1);
    disconnect(level_2, &QAction::triggered, this, &PlayerControls::handleSpeedLevel2);
    disconnect(level_3, &QAction::triggered, this, &PlayerControls::handleSpeedLevel3);
    disconnect(level_4, &QAction::triggered, this, &PlayerControls::handleSpeedLevel4);
    disconnect(level_5, &QAction::triggered, this, &PlayerControls::handleSpeedLevel5);
}

void PlayerControls::handleSpeedLevel1()
{
    setSpeed(SPEED_025);
}

void PlayerControls::handleSpeedLevel2()
{
    setSpeed(SPEED_05);
}

void PlayerControls::handleSpeedLevel3()
{
    setSpeed(SPEED_NORMAL);
}

void PlayerControls::handleSpeedLevel4()
{
    setSpeed(SPEED_2);
}

void PlayerControls::handleSpeedLevel5()
{
    setSpeed(SPEED_4);
}

void PlayerControls::handlePlayMode()
{
    QMenu playMode(this);

    /* Craft menu items */
    QAction* sequential = playMode.addAction(tr("Lecture normale"));
    QAction* loopItem = playMode.addAction(tr("Lecture en bouble (morceau en cours)"));
    QAction* loopPlaylist = playMode.addAction(tr("Lecture en bouble (playlist)"));
    QAction* random = playMode.addAction(tr("Lecture aléatoire"));

    /* Set items checkable */
    sequential->setCheckable(true);
    loopItem->setCheckable(true);
    loopPlaylist->setCheckable(true);
    random->setCheckable(true);

    /* Check the currently selected mode */
    switch(m_playMode) {
    case QMediaPlaylist::Sequential:
        sequential->setChecked(true);
        break;

    case QMediaPlaylist::CurrentItemInLoop:
        loopItem->setChecked(true);
        break;

    case QMediaPlaylist::Loop:
        loopPlaylist->setChecked(true);
        break;

    case QMediaPlaylist::Random:
        random->setChecked(true);
        break;
    }

    /* Connect items signals to slots */
    connect(sequential, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeSequential);
    connect(loopItem, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeLoopItem);
    connect(loopPlaylist, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeLoopPlaylist);
    connect(random, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeRandom);

    /* Show menu at the current cursor position */
    playMode.exec(QCursor().pos());

    /* Disconnect signals */
    disconnect(sequential, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeSequential);
    disconnect(loopItem, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeLoopItem);
    disconnect(loopPlaylist, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeLoopPlaylist);
    disconnect(random, &QAction::toggled, this, &PlayerControls::handlePlayModeChangeRandom);
}

void PlayerControls::handlePlayModeChangeSequential()
{
    setPlayMode(QMediaPlaylist::Sequential);
}

void PlayerControls::handlePlayModeChangeLoopItem()
{
   setPlayMode(QMediaPlaylist::CurrentItemInLoop);
}

void PlayerControls::handlePlayModeChangeLoopPlaylist()
{
    setPlayMode(QMediaPlaylist::Loop);
}

void PlayerControls::handlePlayModeChangeRandom()
{
    setPlayMode(QMediaPlaylist::Random);
}
