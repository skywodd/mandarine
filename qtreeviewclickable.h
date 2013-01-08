/**
 * @file qtreeviewclickable.h
 * @brief QTreeView extension with right click support
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate QTreeViewClickable object.\n
 * The QTreeViewClickable object is an extension of the standard QTreeview widget with right click support.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section license_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */
#ifndef QTREEVIEWCLICKABLE_H
#define QTREEVIEWCLICKABLE_H

/* Dependencies */
#include <QTreeView>

/* Forward declarations */
class QWidget;
class QStringList;

/**
 * @brief QTreeView with rigth click support
 *
 * This class is a enhanced version of QTreeView widget with rigth click support
 */
class QTreeViewClickable : public QTreeView
{
    Q_OBJECT

public:
    /**
     * Default constructor of the widget
     *
     * @brief QTreeViewClickable constructor
     * @param parent Parent widget
     */
    explicit QTreeViewClickable(QWidget* parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief QTreeViewClickable destructor
     * @remarks Ready for overload
     */
    virtual ~QTreeViewClickable();

signals:
    void dragAddFiles(const QStringList& filenames);
    void dragAddDirectories(const QStringList& paths);

protected:
    // TODO drag 'n drop support for files and directory
};

#endif // QTREEVIEWCLICKABLE_H
