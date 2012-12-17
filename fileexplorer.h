#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include "ui_fileexplorer.h"

class FileExplorer : public QWidget, protected Ui::FileExplorer
{
    Q_OBJECT
    
public:
    explicit FileExplorer(QWidget *parent = 0);
    ~FileExplorer();
};

#endif // FILEEXPLORER_H
