#ifndef AUDIOFORMATSDIALOG_H
#define AUDIOFORMATSDIALOG_H

#include "ui_audioformatsdialog.h"

class AudioFormatsDialog : public QDialog, protected Ui::AudioFormatsDialog
{
    Q_OBJECT

public:
    explicit AudioFormatsDialog(QWidget *parent = 0);
    virtual ~AudioFormatsDialog();
};

#endif // AUDIOFORMATSDIALOG_H
