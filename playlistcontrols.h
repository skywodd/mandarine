#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

#include "ui_playlistcontrols.h"
#include "playlisttablemodel.h"


class PlaylistControls : public QWidget, protected Ui::PlaylistControls
{
    Q_OBJECT
    
public:
    explicit PlaylistControls(QWidget *parent = 0);
    ~PlaylistControls();

protected:
    PlaylistTableModel m_playlistTableModel;


 signals:
    void newPlaylist();
    void loadPlaylist();
    void savePlaylist();
    void searchPlaylist();

public slots:

protected slots:
    void handleNewPlaylist();
    void handleLoadPlaylist();
    void handleSavePlaylist();
    void handleSearchPlaylist();
};

#endif // PLAYLISTCONTROLS_H
