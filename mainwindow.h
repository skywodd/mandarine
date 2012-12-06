/**
 * @file mainwindow.h
 * @brief The main window header class
 * @author SkyWodd & jordanVertaure
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * TODO\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section licence_sec Licence
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Dependencies */
#include <QMainWindow>
#include "ui_mainwindow.h"

/* MultimediaKit (Phonon killer) dependencies */
#include <QMediaPlayer>
#include <QMediaPlaylist>

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
protected:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

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
};

#endif // MAINWINDOW_H
