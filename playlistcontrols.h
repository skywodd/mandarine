#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

/* Dependencies */
#include "ui_playlistcontrols.h"
#include "playlisttablemodel.h"
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>

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
    void currentIndexChanged(int pos);
    void mediaRemoved(int pos);

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

    /**
     * Set the current index
     *
     * @brief setCurrentIndex
     */
    void setCurrentIndex( int pos );

    /**
     * Add a media to the playlist
     *
     * @brief add media
     */
    void addMedia(const PlaylistTableModel::RowData_t& media);

    /**
     * Remove a media in the playlist
     *
     * @brief remove media
     */
    void removeMedia(int pos);

protected slots:
    /**
     * Handle search playlist input trigger
     *
     * @brief handleSearchPlaylist
     */
    void handleSearchPlaylist(const QString& text);

    /**
     * Handle double click on a row to set the current index
     *
     * @brief handleDoubleClick
     */
    void handleDoubleClick(const QModelIndex & index);

    /**
     * Handle right click on a row to display menu
     *
     * @brief handleRightClick
     */
    void handleRightClicked(QContextMenuEvent* event);

    /**
     * Handle contextual menu play click
     *
     * @brief handleContextualMenuPlay
     */
    void handleContextualMenuPlay();

    /**
     * Handle contextual menu remove click
     *
     * @brief handleContextualMenuRemove
     */
    void handleContextualMenuRemove();



    void dropEvent(QDropEvent *event);

    void dragMoveEvent(QDragMoveEvent * event);

    void mousePressEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent * event);

    /**
     * Handle Internal move of rows
     *
     * @brief handleInternalMove
     */
    void handleInternalMove(QDragEnterEvent *event);

};

#endif // PLAYLISTCONTROLS_H
