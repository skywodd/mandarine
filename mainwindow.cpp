/* Includes */
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QWidget>
#include <QDebug>
#include <QUrl>
#include "aboutdialog.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_player(0),
    m_playlist(0)
{
    /* Setup UI */
    setupUi(this);

    /* Instantiate QMediaPlayer and QMediaPlaylist objects */
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(m_playlist);

    /* Connect menu player signals to slots */
    connect(action_play, &QAction::triggered, player_controls, &PlayerControls::setTogglePlayPause);
    connect(action_stop, &QAction::triggered, player_controls, &PlayerControls::setStop);
    connect(action_next_music, &QAction::triggered, player_controls, &PlayerControls::setNext);
    connect(action_previous_music, &QAction::triggered, player_controls, &PlayerControls::setPrevious);
    connect(action_mute, &QAction::triggered, player_slides, &PlayerSliders::setToggleVolumeMute);

    /* Connect menu library signals to slots */
    connect(action_add_file, &QAction::triggered, [this](){
        QStringList filenames = QFileDialog::getOpenFileNames(this, QString(tr("Ajouter des fichiers à la bibliothéque ...")));
        if(filenames.size() > 0)
            library_explorer->addFiles(filenames);
    });
    connect(action_add_directory, &QAction::triggered, [this](){
        QString path = QFileDialog::getExistingDirectory(this, QString(tr("Ajouter des fichiers à la bibliothéque ...")));
        if(path != "")
            library_explorer->addDirectories(path);
    });

    /* Connect menu playlist signals to slots */
    connect(action_new_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleNewPlaylist);
    connect(action_save_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleSavePlaylist);
    connect(action_open_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleLoadPlaylist);
    connect(action_playmode_sequencial, &QAction::triggered, [this]() {
        player_controls->setPlayMode(QMediaPlaylist::Sequential);
    });
    connect(action_playmode_loopitem, &QAction::triggered, [this]() {
        player_controls->setPlayMode(QMediaPlaylist::CurrentItemInLoop);
    });
    connect(action_playmode_loopplaylist, &QAction::triggered, [this]() {
        player_controls->setPlayMode(QMediaPlaylist::Loop);
    });
    connect(action_playmode_random, &QAction::triggered, [this]() {
        player_controls->setPlayMode(QMediaPlaylist::Random);
    });
    connect(action_mix_playlist, &QAction::triggered, m_playlist, &QMediaPlaylist::shuffle);
    connect(action_go_to_playing, &QAction::triggered, playlist_controls, &PlaylistControls::goToCurrentIndex);

    /* Connect menu tools signals to slots */
    // TODO

    /* Connect QMediaPlayer signal to slots */
    //connect(m_player, &QMediaPlayer::audioAvailableChanged, player_controls, &PlayerControls::setStatus);
    connect(m_player, &QMediaPlayer::bufferStatusChanged, player_slides, &PlayerSliders::setBuffering);
    connect(m_player, &QMediaPlayer::durationChanged, player_slides, &PlayerSliders::setTotalTime);
    //connect(m_player, &QMediaPlayer::error, this, &MainWindow::proxyMediaPlayerError);
    connect(m_player, &QMediaPlayer::mediaChanged, [this](const QMediaContent& media) {
        music_info->bindQMediaRessource(&media.canonicalResource());
    });
    connect(m_player, &QMediaPlayer::positionChanged, player_slides, &PlayerSliders::setCurrentTime);
    connect(m_player, &QMediaPlayer::seekableChanged, player_slides, &PlayerSliders::setSeekable);
    connect(m_player, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state) {
        switch(state) {
        case QMediaPlayer::PlayingState:
            qDebug() << "is playing" ;
            break;

        case QMediaPlayer::PausedState:
            qDebug() << "is paused" ;
            break;

        case QMediaPlayer::StoppedState:
            qDebug() << "is stopped" ;
            break;
        }
    });

    /* Connect QMediaPlaylist to slots */
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, playlist_controls, &PlaylistControls::setCurrentIndex);
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int) {
        if(m_playlist->currentIndex() == (m_playlist->mediaCount() - 1))
            player_controls->setMode(PlayerControls::MODE_ENDING);
        else if(m_playlist->currentIndex() == 0)
            player_controls->setMode(PlayerControls::MODE_BEGIN);
        else
            player_controls->setMode(PlayerControls::MODE_RUNNING);
    });
    connect(m_playlist, &QMediaPlaylist::loaded, this, &MainWindow::handlePlaylistLoaded);
    connect(m_playlist, &QMediaPlaylist::loadFailed, this, &MainWindow::handlePlaylistError);
    /*connect(m_playlist, &QMediaPlaylist::mediaChanged, [this](int start, int end) {
    });
    connect(m_playlist, &QMediaPlaylist::mediaInserted, [this](int start, int end) {
    });
    connect(m_playlist, &QMediaPlaylist::mediaRemoved, [this](int start, int end) {
    });*/

    /* Connect menu help signals to slots */
    connect(action_show_help, &QAction::triggered, [this]() {
        //QMessageBox::about(this, tr("Aide"), tr("Désolé mais pour le moment vous devez vous démerder tous seul :)"));

        // Demo
        PlaylistTableModel::RowData_t info;
        info.album = "SAO";
        info.authors = "LiSA";
        info.genre = "Jpop";
        info.duration = "xx:xx";

        info.title = "test1.mp3";
        proxyAddMedia(QString("C:\\Users\\skywodd\\workspace\\github\\Mandarine-build-Desktop\\debug\\test1.mp3"), info);

        info.title = "test2.mp3";
        proxyAddMedia(QString("C:\\Users\\skywodd\\workspace\\github\\Mandarine-build-Desktop\\debug\\test2.mp3"), info);
    });
    connect(action_show_about, &QAction::triggered, [this]() {
        AboutDialog(this).exec();
    });
    connect(action_show_aboutqt, &QAction::triggered, [this]() {
        QMessageBox::aboutQt(this, tr("A propos de Qt"));
    });

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

    connect(player_controls, &PlayerControls::play, [this]() {
        qDebug() << "play";
    });
    connect(player_controls, &PlayerControls::pause, [this]() {
        qDebug() << "pause";
    });
    connect(player_controls, &PlayerControls::stop, [this]() {
        qDebug() << "stop";
    });
    connect(player_controls, &PlayerControls::next, [this]() {
        qDebug() << "next";
    });
    connect(player_controls, &PlayerControls::previous, [this]() {
        qDebug() << "previous";
    });
    connect(player_controls, &PlayerControls::playModeChanged, [this](QMediaPlaylist::PlaybackMode mode) {
        qDebug() << "playModeChanged " << mode ;
    });
    connect(player_controls, &PlayerControls::speedChanged, [this](qreal speed) {
        qDebug() << "speedChanged " << speed;
    });

    /* Connect PlaylistControls signals to slots */
    connect(playlist_controls, &PlaylistControls::newPlaylist, m_playlist, &QMediaPlaylist::clear);
    connect(playlist_controls, &PlaylistControls::savePlaylist, [this](const QUrl& location) {
        m_playlist->save(location);
    });
    connect(playlist_controls, &PlaylistControls::loadPlaylist, [this](const QUrl& location) {
        m_playlist->load(location);
    });
    connect(playlist_controls, &PlaylistControls::currentIndexChanged, m_playlist, &QMediaPlaylist::setCurrentIndex);
    /*connect(playlist_controls, &PlaylistControls::currentIndexChanged, [this](int pos) {
        m_playlist->setCurrentIndex(pos);
        player_controls->setPlay();
    });*/
    connect(playlist_controls, &PlaylistControls::mediaRemoved, [this] (int pos) {
        m_playlist->removeMedia(pos);
    });

    /* Connect library signals to slots */
    connect(library_explorer, &LibraryExplorer::addMediaToPlaylist, this, &MainWindow::proxyAddMedia);

    /* Init. player controls */
    player_controls->setMode(PlayerControls::MODE_BEGIN);
    //player_controls->setStatus(true);

    /* Init. library */
    library_explorer->openDatabase();
    library_explorer->refresh(QString(""));
}

MainWindow::~MainWindow()
{
    /* Free memory */
    delete m_player;
    delete m_playlist;
}

void MainWindow::proxyMediaPlayerError(QMediaPlayer::Error)
{
    QMessageBox::critical(this, QString(tr("Erreur interne")), QString(tr("Une erreur est survenue !\n%1")).arg(m_player->errorString()));
}

void MainWindow::proxyAddMedia(const QString& path, const PlaylistTableModel::RowData_t& infos)
{
    QMediaContent media(QUrl::fromLocalFile(path));
    m_playlist->addMedia(media);
    playlist_controls->addMedia(infos);
    player_controls->setStatus(true);
}

void MainWindow::proxyPlaylistMetaChanged(const QString& key, const QVariant& value)
{
    /* Display wikipedia informations */
    if(key == QMediaMetaData::AlbumTitle)
        author_info->displayInfo(value.toString());

    /* Display meta informations */
    music_info->displayMetaInfo(key, value);
}

void MainWindow::handlePlaylistLoaded()
{
    //player_controls->setMode(PlayerControls::MODE_BEGIN);
    //player_controls->setStatus(true);
    //playlist_controls->setCurrentIndex(0);
}

void MainWindow::handlePlaylistError()
{
    QMessageBox::warning(this, QString(tr("Erreur de chargement")), QString(tr("Une erreur est survenue lors du chargement de la playlist !\n%1")).arg(m_playlist->errorString()));
}

