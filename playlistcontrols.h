#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

#include "ui_playlistcontrols.h"

class PlaylistControls : public QWidget, protected Ui::PlaylistControls
{
    Q_OBJECT
    
public:
    explicit PlaylistControls(QWidget *parent = 0);
    ~PlaylistControls();

};

#endif // PLAYLISTCONTROLS_H
