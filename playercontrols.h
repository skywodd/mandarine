#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "ui_playercontrols.h"

class PlayerControls : public QWidget, protected Ui::PlayerControls
{
    Q_OBJECT
    
public:
    explicit PlayerControls(QWidget *parent = 0);
    ~PlayerControls();

};

#endif // PLAYERCONTROLS_H
