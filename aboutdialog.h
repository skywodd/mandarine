#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "ui_aboutdialog.h"

class AboutDialog : public QDialog, protected Ui::AboutDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    virtual ~AboutDialog();
    
};

#endif // ABOUTDIALOG_H
