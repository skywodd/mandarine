#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Dependencies */
#include <QMainWindow>
#include <QMediaPlayer>
#include "playlisttablemodel.h"
#include "ui_mainwindow.h"

/* Forward declaration */
class QUrl;
class Widget;
class QString;
class QMediaPlaylist;

/**
 * @brief The MainWindow class
 *
 * This class is designed to handle everything, from widget signal to media playing.
 */
class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
    
protected:
    /** Media player object */
    QMediaPlayer *m_player;

    /** Media playlist object */
    QMediaPlaylist *m_playlist;

public:
    /**
     * Default constructor of the main window
     *
     * @brief MainWindow constructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Default destructor of the main window
     *
     * @brief MainWindow destructor
     */
    virtual ~MainWindow();

protected slots:
	void proxyRefreshInfo(int index);
    void proxyMediaPlayerError(QMediaPlayer::Error error);
    void proxyAddMedia(const QString& path, const PlaylistTableModel::RowData_t& infos);
    void proxyPlaylistMetaChanged(const QString& key, const QVariant& value);
    void handlePlaylistLoaded();
    void handlePlaylistError();
};

#endif // MAINWINDOW_H
