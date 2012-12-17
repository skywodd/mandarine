#ifndef LIBRARYEXPLORER_H
#define LIBRARYEXPLORER_H

#include "ui_libraryexplorer.h"

class LibraryExplorer : public QWidget, protected Ui::LibraryExplorer
{
    Q_OBJECT
    
public:
    explicit LibraryExplorer(QWidget *parent = 0);
    ~LibraryExplorer();
};

#endif // LIBRARYEXPLORER_H
