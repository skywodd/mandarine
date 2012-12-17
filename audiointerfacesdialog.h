#ifndef AUDIOINTERFACESDIALOG_H
#define AUDIOINTERFACESDIALOG_H

#include "ui_audiointerfacesdialog.h"

class AudioInterfacesDialog : public QDialog, protected Ui::AudioInterfacesDialog
{
    Q_OBJECT

public:
    explicit AudioInterfacesDialog(QWidget *parent = 0);
    virtual ~AudioInterfacesDialog();
    
};

#endif // AUDIOINTERFACESDIALOG_H
