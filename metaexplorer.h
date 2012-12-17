#ifndef METAEXPLORER_H
#define METAEXPLORER_H

#include "ui_metaexplorer.h"

class MetaExplorer : public QWidget, protected Ui::MetaExplorer
{
    Q_OBJECT
    
public:
    explicit MetaExplorer(QWidget *parent = 0);
    ~MetaExplorer();

};

#endif // METAEXPLORER_H
