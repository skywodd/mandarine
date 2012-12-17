#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Dependencies */
#include "ui_mainwindow.h"

/* MultimediaKit (Phonon killer) dependencies */
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
    
protected:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
/*
protected slots:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void fastForward();
    void fastRewind();
    void mute();
    void changeVolume(int volume);
    void changeTimeSeek(int timeseek);
    void addFiles();
    void addDirectory();
    void addNetwork();
    void newPlaylist();
    void openPlaylist();
    void savePlaylist();
    void showLoopMenu();
    void loopDisable();
    void loopMusic();
    void loopPlaylist();
    void showRandomMenu();
    void randomDisable();
    void randomPlaylist();
    void randomLibrary();
    void goToPlaying();
    void flushPlaylist();
    void mixPlaylist();
    void searchPlaylist();
    void searchLibrary();
    void enableFFT(bool enable);
    void showHelpDialog();
    void showAboutDialog();
    void showQtAboutDialog();
    void showSetupDialog();
    void showAudioInterfacesDialog();
    void showSupportedFormatsDialog();
    void showDatabaseCleanupDialog();
    void showDatabaseUpdateDialog();
    void showEqualizerDialog();
*/
};

#endif // MAINWINDOW_H
