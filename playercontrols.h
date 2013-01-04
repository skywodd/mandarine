
#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

/* Dependencies */
#include "ui_playercontrols.h"
#include <QMediaPlaylist>

/**
 * @brief Player controls's widget
 *
 * This class is designed to handle all controls of the media player.
 */
class PlayerControls : public QWidget, protected Ui::PlayerControls
{
    Q_OBJECT

public:
    /**
     * Controls modes
     */
    typedef enum {
        MODE_BEGIN,
        MODE_RUNNING,
        MODE_ENDING
    } Mode_t;

    /**
     * Speed modification factor levels
     */
    typedef enum {
        SPEED_025,
        SPEED_05,
        SPEED_NORMAL,
        SPEED_2,
        SPEED_4
    } Speed_t;

    /**
     * Default constructor of the widget
     *
     * @brief PlayerControls
     * @param parent Parent widget
     */
    explicit PlayerControls(QWidget *parent = 0);

    /**
     * Default destructor
     *
     * @brief ~PlayerControls
     * @remarks Ready for overload
     */
    virtual ~PlayerControls();

protected:
    /** True if widget is in "play mode", false if in "pause mode" */
    bool m_isplaying;

    /** Speed modification factor level */
    Speed_t m_speedLevel;

    /** Playback mode */
    QMediaPlaylist::PlaybackMode m_playMode;

    /** Controls display */
    Mode_t m_mode; // NOTE usefull ?

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
    // TODO use bind (if possible)
    void handleSpeedLevel();
    void handleSpeedLevel1();
    void handleSpeedLevel2();
    void handleSpeedLevel3();
    void handleSpeedLevel4();
    void handleSpeedLevel5();

    // TODO use bind (if possible)
    void handlePlayMode();
    void handlePlayModeChangeSequential();
    void handlePlayModeChangeLoopItem();
    void handlePlayModeChangeLoopPlaylist();
    void handlePlayModeChangeRandom();
};

#endif // PLAYERCONTROLS_H
