/* Includes */
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QUrl>
#include "playlisttablemodel.h"
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
    m_player->setNotifyInterval(1000);

    /* Connect menu player signals to slots */
    connect(action_play, &QAction::triggered, player_controls, &PlayerControls::setTogglePlayPause);
    connect(action_stop, &QAction::triggered, player_controls, &PlayerControls::setStop);
    connect(action_next_music, &QAction::triggered, player_controls, &PlayerControls::setNext);
    connect(action_previous_music, &QAction::triggered, player_controls, &PlayerControls::setPrevious);
    connect(action_mute, &QAction::triggered, player_slides, &PlayerSliders::setToggleVolumeMute);

    /* Connect menu library signals to slots */
    connect(action_add_file, &QAction::triggered, [this](){
        qDebug() << "action_add_file::triggered -> library_explorer::addFile";
        QStringList filenames = QFileDialog::getOpenFileNames(this, QString(tr("Ajouter des fichiers à la bibliothéque ...")));
        if(filenames.size() > 0)
            library_explorer->addFiles(filenames);
    });
    connect(action_add_directory, &QAction::triggered, [this](){
        qDebug() << "action_add_directory::triggered -> library_explorer::addDirectory";
        QString path = QFileDialog::getExistingDirectory(this, QString(tr("Ajouter un dossier à la bibliothéque ...")));
        if(path != "")
            library_explorer->addDirectory(path);
    });

    /* Connect menu playlist signals to slots */
    connect(action_new_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleNewPlaylist);
    connect(action_save_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleSavePlaylist);
    connect(action_open_playlist, &QAction::triggered, playlist_controls, &PlaylistControls::handleLoadPlaylist);
    connect(action_playmode_sequencial, &QAction::triggered, [this]() {
        qDebug() << "action_playmode_sequencial::triggered -> player_controls::setPlayMode";
        player_controls->setPlayMode(QMediaPlaylist::Sequential);
    });
    connect(action_playmode_loopitem, &QAction::triggered, [this]() {
        qDebug() << "action_playmode_sequencial::triggered -> player_controls::setPlayMode";
        player_controls->setPlayMode(QMediaPlaylist::CurrentItemInLoop);
    });
    connect(action_playmode_loopplaylist, &QAction::triggered, [this]() {
        qDebug() << "action_playmode_sequencial::triggered -> player_controls::setPlayMode";
        player_controls->setPlayMode(QMediaPlaylist::Loop);
    });
    connect(action_playmode_random, &QAction::triggered, [this]() {
        qDebug() << "action_playmode_sequencial::triggered -> player_controls::setPlayMode";
        player_controls->setPlayMode(QMediaPlaylist::Random);
    });
    connect(action_mix_playlist, &QAction::triggered, m_playlist, &QMediaPlaylist::shuffle);
    connect(action_go_to_playing, &QAction::triggered, playlist_controls, &PlaylistControls::goToCurrentIndex);

    /* Connect QMediaPlayer signal to slots */
    //connect(m_player, &QMediaPlayer::audioAvailableChanged, player_controls, &PlayerControls::setStatus);
    connect(m_player, &QMediaPlayer::bufferStatusChanged, player_slides, &PlayerSliders::setBuffering);
    connect(m_player, &QMediaPlayer::durationChanged, player_slides, &PlayerSliders::setTotalTime);
    connect(m_player, &QMediaPlayer::durationChanged, [this](qint64 time) {
        qDebug() << "m_player::durationChanged -> update duration display";
        PlaylistTableModel::RowData_t row;
        row.duration = QString("%1").arg(time);
        playlist_controls->editMedia(m_playlist->currentIndex(), PlaylistTableModel::EDIT_DURATION, row);
    });
    connect(m_player, &QMediaPlayer::positionChanged, player_slides, &PlayerSliders::setCurrentTime);
    connect(m_player, &QMediaPlayer::seekableChanged, player_slides, &PlayerSliders::setSeekable);
    connect(m_player, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state) {
        qDebug() << "m_player::stateChanged -> nothing";
        switch(state) {
        case QMediaPlayer::PlayingState:
            qDebug() << "QMediaPlayer is playing" ;
            break;

        case QMediaPlayer::PausedState:
            qDebug() << "QMediaPlayer is paused" ;
            break;

        case QMediaPlayer::StoppedState:
            qDebug() << "QMediaPlayer is stopped" ;
            break;
        }
    });
    connect(m_player, static_cast<void (QMediaPlayer::*)(const QString&, const QVariant&)>(&QMediaPlayer::metaDataChanged), this, &MainWindow::proxyPlaylistMetaChanged);
    // Ho god ... why !? #uglyCast T_T

    /* Connect QMediaPlaylist to slots */
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::proxyRefreshInfo);
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
        qDebug() << "action_show_help::triggered-> nothing";
        //TODO help dialog
    });
    connect(action_show_about, &QAction::triggered, [this]() {
        qDebug() << "action_show_about::triggered -> AboutDialog::exec";
        AboutDialog(this).exec();
    });
    connect(action_show_aboutqt, &QAction::triggered, [this]() {
        qDebug() << "action_show_aboutqt::triggered -> QMessageBox::aboutQt";
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

    /* Connect PlaylistControls signals to slots */
    connect(playlist_controls, &PlaylistControls::newPlaylist, m_playlist, &QMediaPlaylist::clear);
    connect(playlist_controls, &PlaylistControls::savePlaylist, [this](const QUrl& location) {
        qDebug() << "playlist_controls::savePlaylist -> m_playlist->save";
        m_playlist->save(location);
    });
    connect(playlist_controls, &PlaylistControls::loadPlaylist, [this](const QUrl& location) {
        qDebug() << "playlist_controls::loadPlaylist -> m_playlist->load";
        m_playlist->load(location);
    });
    connect(playlist_controls, &PlaylistControls::currentIndexChanged, m_playlist, &QMediaPlaylist::setCurrentIndex);
    connect(playlist_controls, &PlaylistControls::mediaRemoved, [this] (int pos) {
        qDebug() << "playlist_controls::mediaRemoved -> m_playlist->removeMedia";
        m_playlist->removeMedia(pos);
    });

    /* Connect library signals to slots */
    connect(library_explorer, &LibraryExplorer::addMediaToPlaylist, this, &MainWindow::proxyAddMedia);

    /* Init. player controls */
    player_controls->setMode(PlayerControls::MODE_BEGIN);

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

void MainWindow::proxyRefreshInfo(int index)
{
	qDebug() << "m_playlist::currentIndexChanged -> player_controls::setMode";

	/* Setup player controls */
	if(index == (m_playlist->mediaCount() - 1))
		player_controls->setMode(PlayerControls::MODE_ENDING);
	else if(index == 0)
		player_controls->setMode(PlayerControls::MODE_BEGIN);
	else
		player_controls->setMode(PlayerControls::MODE_RUNNING);

	/* Setup meta info display & web view */
	if(m_playlist->mediaCount() == 0) return;
	PlaylistTableModel::RowData_t row = playlist_controls->getRow(index);
	proxyPlaylistMetaChanged(QMediaMetaData::Title, row.title);
	proxyPlaylistMetaChanged(QMediaMetaData::AlbumTitle, row.album);
	proxyPlaylistMetaChanged(QMediaMetaData::Author, row.authors);
	proxyPlaylistMetaChanged(QMediaMetaData::Genre, row.genre);

	/* Display external cover if possible */
	QString filepath = m_playlist->media(index).canonicalUrl().toLocalFile();
	QFileInfo cover(QFileInfo(filepath).absolutePath() + QString("/cover.jpg"));
	qDebug() << "Cover filepath: " << cover.absoluteFilePath();
	if(cover.exists())
		music_info->displayExternalCover(cover.absoluteFilePath());

	/* Display authors info */
	author_info->displayInfo(row.authors);

	/* Resend signal to parent */
	playlist_controls->setCurrentIndex(index);
}

void MainWindow::proxyMediaPlayerError(QMediaPlayer::Error e)
{
    qDebug() << "-> MainWindow::proxyMediaPlayerError(" << e << ")";
    QMessageBox::critical(this, QString(tr("Erreur interne")), QString(tr("Une erreur est survenue !\n%1")).arg(m_player->errorString()));
}

void MainWindow::proxyAddMedia(const QString& path, const PlaylistTableModel::RowData_t& infos)
{
    qDebug() << "-> MainWindow::proxyAddMedia(" << path << ", ...)";
    QMediaContent media(QUrl::fromLocalFile(path));
    m_playlist->addMedia(media);
    playlist_controls->addMedia(infos);
    player_controls->setStatus(true);
}

void MainWindow::proxyPlaylistMetaChanged(const QString& key, const QVariant& value)
{
    qDebug() << "-> MainWindow::proxyPlaylistMetaChanged(" << key << ", ...)";

    /* Display meta informations */
    music_info->displayMetaInfo(key, value);
}

void MainWindow::handlePlaylistLoaded()
{
    qDebug() << "-> MainWindow::handlePlaylistLoaded()";
}

void MainWindow::handlePlaylistError()
{
    qDebug() << "-> MainWindow::handlePlaylistError()";
    QMessageBox::warning(this, QString(tr("Erreur de chargement")), QString(tr("Une erreur est survenue lors du chargement de la playlist !\n%1")).arg(m_playlist->errorString()));
}
