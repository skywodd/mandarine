/* Includes */
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include "mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_player(new QMediaPlayer(this)),
    m_playlist(new QMediaPlaylist(this))
{
    /* Setup UI */
    setupUi(this);
    m_player->setPlaylist(m_playlist);

    /* Connect PlayerSliders signals to slots */
    connect(player_slides, &PlayerSliders::muteChanged, m_player, &QMediaPlayer::setMuted);
    connect(player_slides, &PlayerSliders::volumeChanged, m_player, &QMediaPlayer::setVolume);
    connect(player_slides, &PlayerSliders::seekChanged, m_player, &QMediaPlayer::setPosition);

    /* Connect PlayerControls signals to slots */
    connect(player_controls, &PlayerControls::play, m_player, &QMediaPlayer::play);
    connect(player_controls, &PlayerControls::pause, m_player, &QMediaPlayer::pause);
    connect(player_controls, &PlayerControls::stop, m_player, &QMediaPlayer::stop);
    connect(player_controls, &PlayerControls::next, m_playlist, &QMediaPlaylist::next);
    connect(player_controls, &PlayerControls::previous, m_playlist, &QMediaPlaylist::previous);
    connect(player_controls, &PlayerControls::playModeChanged, m_playlist, &QMediaPlaylist::setPlaybackMode);
    connect(player_controls, &PlayerControls::speedChanged, m_player, &QMediaPlayer::setPlaybackRate);

    /* Connect menu signals to slots */
    connect(action_show_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(action_show_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(action_show_aboutqt, &QAction::triggered, this, &MainWindow::showQtAboutDialog);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showHelpDialog()
{
    QMessageBox::about(this, tr("Aide"), tr("Désolé mais pour le moment vous devez vous démerder tous seul :)"));
}

void MainWindow::showAboutDialog()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::showQtAboutDialog()
{
    QMessageBox::aboutQt(this, tr("A propos de Qt"));
}
