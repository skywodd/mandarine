/**
 * @file playercontrols.h
 * @brief Player controls widget
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate PlayerControls object.\n
 * The PlayerControls object is a widget designed to handle all controls of a standard media player.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section license_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */
#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

/* Dependencies */
#include <QMediaPlaylist>
#include <QWidget>
#include <QString>
#include "ui_playercontrols.h"

/**
 * @brief Player controls widget
 *
 * This class is designed as a widget made to handle all controls of the media player.
 */
class PlayerControls : public QWidget, protected Ui::PlayerControls
{
    Q_OBJECT

public:
    /**
     * Controls modes
     */
    typedef enum {
        MODE_BEGIN, /*!< Playlist cursor at beginning */
        MODE_RUNNING, /*!< Playlist cursor somewhere between beginning and ending */
        MODE_ENDING /*!< Playlist cursor at ending */
    } Mode_t;

    /**
     * Speed modification factor levels
     */
    typedef enum {
        SPEED_025, /*!< /4 factor */
        SPEED_05, /*!< /2 factor */
        SPEED_NORMAL, /*!< x1 factor */
        SPEED_2, /*!< x2 factor */
        SPEED_4 /*!< x4 factor */
    } Speed_t;

    /**
     * Default constructor of the widget
     *
     * @brief PlayerControls constructor
     * @param parent Parent widget
     */
    explicit PlayerControls(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief PlayerControls destructor
     * @remarks Ready for overload
     */
    virtual ~PlayerControls();

protected:
    /** True if the widget is in "playing mode", false if in "paused mode" */
    bool m_isplaying;

    /** Speed modification factor level */
    Speed_t m_speedLevel;

    /** Playback mode */
    QMediaPlaylist::PlaybackMode m_playMode;

    /** Controls display */
    Mode_t m_mode;

    /** Play icon ressource location */
    static const QString m_iconPlay;

    /** Pause icon ressource location */
    static const QString m_iconPause;

signals:
    // TODO doxygen
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void playModeChanged(QMediaPlaylist::PlaybackMode playMode);
    void speedChanged(qreal speed);

public slots:
    void setTogglePlayPause();
    void setPlay();
    void setPause();
    void setStop();
    void setSpeed(Speed_t speed);
    void setPlayMode(QMediaPlaylist::PlaybackMode playMode);
    void setNext();
    void setPrevious();
    void setMode(Mode_t mode);
    void setStatus(bool enabled);
    void reset();

protected slots:
    void handleSpeedLevel();
    void handlePlayMode();
};

#endif // PLAYERCONTROLS_H
