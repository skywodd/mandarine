/**
 * @file playlistcontrols.h
 * @brief Playlist controls widget
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate PlaylistControls object.\n
 * The PlaylistControls object is a widget designed to handle playlist item display and management.\n
 * The widget also support internal drag and drop for playlist's item move.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section license_sec License
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
#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

/* Dependencies */
#include <QWidget>
#include "ui_playlistcontrols.h"
#include "playlisttablemodel.h"

/**
 * @brief Playlist controls widget
 *
 * This class is designed to display and manage playlist items.
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
    /** TableModel used to store items data */
    PlaylistTableModel* m_playlistTableModel;

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
    void setCurrentIndex(int pos);

    /**
     * Add a media to the playlist
     *
     * @brief add media
     */
    void addMedia(const PlaylistTableModel::RowData_t& media);

    /**
     * Remove a media from the playlist
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
    void handleDoubleClick(const QModelIndex& index);

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
};

#endif // PLAYLISTCONTROLS_H
