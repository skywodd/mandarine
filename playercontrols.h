#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "ui_playercontrols.h"

#include <QMediaPlaylist>

class PlayerControls : public QWidget, protected Ui::PlayerControls
{
    Q_OBJECT

public:
    typedef enum {
        BEGIN,
        RUNNING,
        ENDING
    } Mode_t;

    explicit PlayerControls(QWidget *parent = 0);
    virtual ~PlayerControls();

protected:
    bool m_isplaying;
    int m_fastLevel;
    QMediaPlaylist::PlaybackMode m_playMode;
    Mode_t m_mode;
    static const QString m_iconPlay;
    static const QString m_iconPause;


signals:
    void play();
    void pause();
    void stop();
    void fastRewind(int level);
    void fastForward(int level);
    void next();
    void previous();
    void playModeChanged(QMediaPlaylist::PlaybackMode playMode);
    void modeChanged(Mode_t mode);
    void speedChanged(int speed);


public slots:
    void setPlay();
    void setPause();
    void setStop();
    void setSpeed(int level);
    void setNext();
    void setPrevious();

    void setStatus(bool enabled);
    void reset();
    void setMode(Mode_t mode);
    void setPlayMode(QMediaPlaylist::PlaybackMode playMode);


protected slots:
    void handlePlay();
    void handleStop();
    void handleSpeed();
    void handleSpeedLevel1();
    void handleSpeedLevel2();
    void handleSpeedLevel3();
    void handleSpeedLevel4();
    void handleSpeedLevel5();
    void handleSpeedChanged(int level);
    void handleNext();
    void handlePrevious();
    void handleMode(Mode_t mode);
    void handlePlayMode();
    void handlePlayModeChangeSequential();
    void handlePlayModeChangeLoop();
    void handlePlayModeChangeRandom();


    void handleStatus(bool enabled);
    void handleReset();
};

#endif // PLAYERCONTROLS_H
