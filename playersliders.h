#ifndef PLAYERSLIDERS_H
#define PLAYERSLIDERS_H

#include "ui_playersliders.h"

class PlayerSliders : public QWidget, protected Ui::PlayerSliders
{
    Q_OBJECT
    
public:
    explicit PlayerSliders(QWidget *parent = 0);
    ~PlayerSliders();
    
};

#endif // PLAYERSLIDERS_H
