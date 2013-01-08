#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Dependencies */
#include "playlisttablemodel.h"
#include "ui_mainwindow.h"

/* Forward declaration */
class QUrl;
class QString;

/* MultimediaKit (Phonon killer) forward declaration */
class QMediaPlayer;
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
    void proxyAddMedia(const QString& path, const PlaylistTableModel::RowData_t& infos);
    void handleSavePlaylist(const QUrl& location);
    void handleLoadPlaylist(const QUrl& location);
    void handleRemoveMedia(int pos);
    void handlePlaylistMetaChanged();
    void handleAddFiles();
    void handleAddDirectories();
    void handlePlaylistLoaded();
    void handlePlaylistError();
    void showHelpDialog();
    void showAboutDialog();
    void showQtAboutDialog();
};

#endif // MAINWINDOW_H
