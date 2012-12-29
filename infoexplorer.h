#ifndef INFOEXPLORER_H
#define INFOEXPLORER_H

/* Dependencies */
#include "ui_infoexplorer.h"

/**
 * @brief Wikipedia informations display widget
 *
 * This widget is designed to display wikipedia informations about album or authors.
 */
class InfoExplorer : public QWidget, protected Ui::InfoExplorer
{
    Q_OBJECT
    
public:
    /**
     * Default constructor of the widget
     *
     * @brief InfoExplorer
     * @param parent Parent widget
     */
    explicit InfoExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief ~InfoExplorer
     * @remarks Ready for overload
     */
    virtual ~InfoExplorer();

    /**
     * Display available informations about the specified album
     *
     * @brief showInformation
     * @param album The album or author(s) name to search and display
     */
    void showInformation(const QString& album);

};

#endif // INFOEXPLORER_H
