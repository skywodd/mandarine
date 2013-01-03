#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

/* Dependencies */
#include "ui_playlistcontrols.h"
#include "playlisttablemodel.h"

/**
 * @brief Playlist control's widget
 *
 * This class is designed to display paylist informations.
 */
class PlaylistControls : public QWidget, protected Ui::PlaylistControls
{
    Q_OBJECT
    
public:
    /**
     * Default contructor of the widget
     *
     * @brief PlaylistControls contructor
     * @param parent Parent widget
     */
    explicit PlaylistControls(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief PlaylistControls destructor
     * @remarks Ready for overload
     */
    virtual ~PlaylistControls();

protected:
    /** TableModel used to store playlist data */
    PlaylistTableModel m_playlistTableModel;

signals:
    void newPlaylist();
    void loadPlaylist(const QUrl& location);
    void savePlaylist(const QUrl& location);
    // currentIndexChanged

public slots:
    /**
     * Handle new playlist button click
     *
     * @brief handleNewPlaylist
     */
    void handleNewPlaylist();

    /**
     * Handle load playlist button click
     *
     * @brief handleLoadPlaylist
     */
    void handleLoadPlaylist();

    /**
     * Handle save playlist button click
     *
     * @brief handleSavePlaylist
     */
    void handleSavePlaylist();

    /**
     * Select the currently played row
     *
     * @brief goToCurrentIndex
     */
    void goToCurrentIndex();

    // setCurrentIndex
    // addMedia
    // removeMedia

protected slots:
    /**
     * Handle search playlist input trigger
     *
     * @brief handleSearchPlaylist
     */
    void handleSearchPlaylist(const QString& text);

    // handleDoubleClick
    // handleSelectionDelete
    // handleInternalMove

};

#endif // PLAYLISTCONTROLS_H
