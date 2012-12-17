#ifndef EQUALIZERDIALOG_H
#define EQUALIZERDIALOG_H

#include "ui_equalizer.h"

class EqualizerDialog : public QDialog, protected Ui::EqualizerDialog
{
    Q_OBJECT
public:
    explicit EqualizerDialog(QWidget *parent = 0);
    ~EqualizerDialog();
};

#endif // EQUALIZERDIALOG_H
