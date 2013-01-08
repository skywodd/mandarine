/* Includes */
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include "mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_player(new QMediaPlayer(this)),
    m_playlist(new QMediaPlaylist(this))
{
    /* Setup UI */
    setupUi(this);

    m_player->setPlaylist(m_playlist);
    player_controls->setEnabled(false);

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

    /* Connect PlaylistControls signals to slots */
    connect(playlist_controls, &PlaylistControls::newPlaylist, m_playlist, &QMediaPlaylist::clear);
    connect(playlist_controls, &PlaylistControls::savePlaylist, this, &MainWindow::handleSavePlaylist);
    connect(playlist_controls, &PlaylistControls::loadPlaylist, this, &MainWindow::handleLoadPlaylist);
    connect(playlist_controls, &PlaylistControls::currentIndexChanged, m_playlist, &QMediaPlaylist::setCurrentIndex);
    connect(playlist_controls, &PlaylistControls::mediaRemoved, this, &MainWindow::handleRemoveMedia);

    /* Connect menu player signals to slots */
    connect(action_play, &QAction::triggered, player_controls, &PlayerControls::setTogglePlayPause);
    connect(action_stop, &QAction::triggered, player_controls, &PlayerControls::setStop);
    connect(action_next_music, &QAction::triggered, player_controls, &PlayerControls::setNext);
    connect(action_previous_music, &QAction::triggered, player_controls, &PlayerControls::setPrevious);
    connect(action_mute, &QAction::triggered, player_slides, &PlayerSliders::setToggleVolumeMute);

    /* Connect menu library signals to slots */
    connect(action_add_file, &QAction::triggered, this, &MainWindow::handleAddFiles);
    connect(action_add_directory, &QAction::triggered, this, &MainWindow::handleAddDirectories);

    /* Connect menu playlist signals to slots */
    connect(action_new_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleNewPlaylist);
    connect(action_save_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleSavePlaylist);
    connect(action_open_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleLoadPlaylist);
    // TODO menu play mode
    connect(action_mix_playlist, &QAction::triggered, m_playlist, &QMediaPlaylist::shuffle);
    connect(action_go_to_playing, &QAction::triggered, playlist_controls, &PlaylistControls::goToCurrentIndex);

    /* Connect menu tools signals to slots */
    // TODO

    /* Connect QMediaPlayer signal to slots */
    connect(m_player, &QMediaPlayer::bufferStatusChanged, player_slides, &PlayerSliders::setBuffering);
    connect(m_player, &QMediaPlayer::seekableChanged, player_slides, &PlayerSliders::setSeekable);
    connect(m_player, &QMediaPlayer::durationChanged, player_slides, &PlayerSliders::setTotalTime);
    connect(m_player, &QMediaPlayer::positionChanged, player_slides, &PlayerSliders::setCurrentTime);

    /* Connect QMediaPlaylist to slots */
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, playlist_controls, &PlaylistControls::setCurrentIndex);
    connect(m_playlist, &QMediaPlaylist::loaded, this, &MainWindow::handlePlaylistLoaded);
    connect(m_playlist, &QMediaPlaylist::loadFailed, this, &MainWindow::handlePlaylistError);

    /* Connect menu help signals to slots */
    connect(action_show_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(action_show_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(action_show_aboutqt, &QAction::triggered, this, &MainWindow::showQtAboutDialog);
}

MainWindow::~MainWindow()
{
}

void MainWindow::proxyAddMedia(const QString& path, const PlaylistTableModel::RowData_t& infos)
{
    QMediaContent *media = new QMediaContent(QUrl(path));
    m_playlist->addMedia(*media);
    playlist_controls->addMedia(infos);
}

void MainWindow::handlePlaylistMetaChanged()
{

}

void MainWindow::handleAddFiles()
{
    library_explorer->addFiles(QFileDialog::getOpenFileNames(this, QString(tr("Ajouter des fichiers à la bibliothéque ..."))));
}

void MainWindow::handleAddDirectories()
{
    library_explorer->addDirectories(QFileDialog::getExistingDirectory(this, QString(tr("Ajouter des fichiers à la bibliothéque ..."))));
}

void MainWindow::handlePlaylistLoaded()
{
    player_controls->setMode(PlayerControls::MODE_BEGIN);
}

void MainWindow::handlePlaylistError()
{
    QMessageBox::warning(this, QString(tr("Erreur de chargement ...")), QString(tr("Une erreur est survenue lors du chargement de la playlist !")));
}

void MainWindow::showHelpDialog()
{
    /* Display help dialog */
    //QMessageBox::about(this, tr("Aide"), tr("Désolé mais pour le moment vous devez vous démerder tous seul :)"));

    // Demo
    PlaylistTableModel::RowData_t info;
    info.album = "SAO";
    info.authors = "LiSA";
    info.genre = "Jpop";
    info.duration = "xx:xx";

    info.title = "test1.mp3";
    proxyAddMedia(QString("test1.mp3"), info);

    info.title = "test2.mp3";
    proxyAddMedia(QString("test2.mp3"), info);
}

void MainWindow::showAboutDialog()
{
    /* Display about dialog */
    AboutDialog(this).exec();
}

void MainWindow::showQtAboutDialog()
{
    /* Display about Qt dialog */
    QMessageBox::aboutQt(this, tr("A propos de Qt"));
}

void MainWindow::handleSavePlaylist(const QUrl& location)
{
    m_playlist->save(location, "m3u");
}

void MainWindow::handleLoadPlaylist(const QUrl& location)
{
    m_playlist->load(location, "m3u");
}

void MainWindow::handleRemoveMedia(int pos)
{
    m_playlist->removeMedia(pos);
}

