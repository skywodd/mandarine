#ifndef INFOEXPLORER_H
#define INFOEXPLORER_H

#include "ui_infoexplorer.h"

class InfoExplorer : public QWidget, protected Ui::InfoExplorer
{
    Q_OBJECT
    
public:
    explicit InfoExplorer(QWidget *parent = 0);
    ~InfoExplorer();
};

#endif // INFOEXPLORER_H
