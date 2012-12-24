#ifndef FILEINFORMATIONSDIALOG_H
#define FILEINFORMATIONSDIALOG_H

/* Dependencies */
#include <QMediaResource>
#include "ui_fileinformationsdialog.h"

/**
 * @brief Audio file information display's dialog
 *
 * This class is designed to display audio ressource informations.
 */
class FileInformationsDialog : public QDialog, protected Ui::FileInformationsDialog
{
    Q_OBJECT
    
public:
    /**
     * Default construcor of the dialog
     *
     * @brief FileInformationsDialog constructor
     * @param source Source media ressource to display
     * @param parent Parent widget
     */
    explicit FileInformationsDialog(QMediaResource *source, QWidget *parent = 0);

    /**
     * Default destructor of the dialog
     *
     * @brief FileInformationsDialog destructor
     */
    virtual ~FileInformationsDialog();
};

#endif // FILEINFORMATIONSDIALOG_H
