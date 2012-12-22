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
        RUNNING
    } Mode_t;

    explicit PlayerControls(QWidget *parent = 0);
    virtual ~PlayerControls();

protected:
    bool m_isplaying;
    int m_fastLevel;
    QMediaPlaylist::PlaybackMode m_loopMode;
    Mode_t m_mode;
    static const QString m_iconPlay;
    static const QString m_iconPause;


signals:
    void play();
    void pause();
    void stop();
    void speedChanged(int level);
    void next();
    void previous();
    void playModeChanged(Mode_t mode);

public slots:
    void setPlay();
    void setPause();
    void setStop();
    void setSpeed(int level);
    void setNext();
    void setPrevious();

    void setStatus(bool enabled);
    void setMode(Mode_t mode);
    void reset();

protected slots:
    void handlePlay();
    void handleStop();
    void handleSetSpeed(int level);
    void handleNext();
    void handlePrevious();
    void handleMode(Mode_t mode);
    void handlePlayMode();


    void handleStatus(bool enabled);
    void handleReset();
};

#endif // PLAYERCONTROLS_H
