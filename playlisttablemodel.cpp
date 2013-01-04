/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 *
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 *
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

/* Includes */
#include <QFont>
#include <QPixmap>
#include "playlisttablemodel.h"

/* Static members initialization */
const QString PlaylistTableModel::m_playingIcon(":/sound/audio.png");

PlaylistTableModel::PlaylistTableModel(QObject *parent) :
    QAbstractTableModel(parent), m_currentIndex(-1)
{
}

PlaylistTableModel::~PlaylistTableModel()
{
}

int PlaylistTableModel::rowCount(const QModelIndex&) const
{
    /* Return row count (dynamic) */
    return m_data.size();
}

int PlaylistTableModel::columnCount(const QModelIndex&) const
{
    /* Return column count (static) */
    return 5;
}

QVariant PlaylistTableModel::data(const QModelIndex &index, int role) const
{
    /* Switch according role */
    switch(role)
    {
    case Qt::DisplayRole: /* Ask for data */

        /* Return data */
        switch(index.column()) {
        case 0:
            return m_data[index.row()].title;
            break;

        case 1:
            return m_data[index.row()].album;
            break;

        case 2:
            return m_data[index.row()].authors;
            break;

        case 3:
            return m_data[index.row()].genre;
            break;

        case 4:
            return m_data[index.row()].duration;
            break;
        }
        break;

    case Qt::FontRole: /* Ask for font */

        /* If the specified row is currently played */
        if(index.row() == m_currentIndex)
        {
            /* Set row text to bold */
            QFont font;
            font.setBold(true);
            return font;
        }
        break;
    }

    /* No data available */
    return QVariant();
}

QVariant PlaylistTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    /* Switch according role */
    switch(role)
    {
    case Qt::DisplayRole: /* Ask for data */

        /* Horizontal header only */
        if(orientation == Qt::Horizontal)
        {
            /* Return header section data */
            switch(section)
            {
            case 0:
                return QString(tr("Titre"));
                break;

            case 1:
                return QString(tr("Album"));
                break;

            case 2:
                return QString(tr("Artiste"));
                break;

            case 3:
                return QString(tr("Genre"));
                break;

            case 4:
                return QString(tr("Durée"));
                break;
            }
        }
        break;

    case Qt::DecorationRole: /* Ask for icon */

        /* Vertical header only and if row is currently played */
        if(orientation == Qt::Vertical && section == m_currentIndex)
            return QPixmap(m_playingIcon);
        break;
    }

    /* No data available */
    return QVariant();
}

bool PlaylistTableModel::hasToBeHidden(int row, const QString &mask) const
{
    /* Check title for match */
    if(m_data[row].title.contains(mask, Qt::CaseInsensitive))
        return false; /* Match, line will not be hidden */

    /* Check title for match */
    if(m_data[row].album.contains(mask, Qt::CaseInsensitive))
        return false; /* Match, line will not be hidden */

    /* Check title for match */
    if(m_data[row].authors.contains(mask, Qt::CaseInsensitive))
        return false; /* Match, line will not be hidden */

    /* Check title for match */
    if(m_data[row].genre.contains(mask, Qt::CaseInsensitive))
        return false; /* Match, line will not be hidden */

    /* Nothing match line will be hidden */
    return true;
}

int PlaylistTableModel::getCurrentIndex() const
{
    /* Return the current index */
    return m_currentIndex;
}

void PlaylistTableModel::setCurrentIndex(int pos)
{
    /* Unset previous index */
    int tmp = m_currentIndex;
    m_currentIndex = -1;
    emit dataChanged(createIndex(tmp, 0), createIndex(tmp, 4));
    emit headerDataChanged(Qt::Vertical, tmp, tmp);

    /* Store the new index */
    m_currentIndex = pos;
    emit dataChanged(createIndex(pos, 0), createIndex(pos, 4));
    emit headerDataChanged(Qt::Vertical, pos, pos);
}

void PlaylistTableModel::flush()
{
    /* Warm view for flush */
    emit modelAboutToBeReset();

    /* Flush data */
    m_data.clear();

    /* Force view refresh */
    emit modelReset();
}

void PlaylistTableModel::addRow(const RowData_t &data)
{
    /* Warm view for new rows */
    emit beginInsertRows(QModelIndex(), m_data.size() + 1, m_data.size() + 1);

    /* Add row's data */
    m_data.append(data);

    /* Force view refresh */
    emit endInsertRows();
}

void PlaylistTableModel::removeRow(int pos)
{
    /* Warm view for delete */
    emit beginRemoveRows(QModelIndex(), pos, pos);

    /* Delete row's data */
    m_data.removeAt(pos);

    /* Force view refresh */
    emit endRemoveRows();
}

void PlaylistTableModel::moveRow(int from, int to)
{
    /* Warm view for move */
    emit beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);

    /* Move row's data */
    RowData_t tmp = m_data[to];
    m_data[to] = m_data[from];
    m_data[from] = tmp;

    /* Force view refresh */
    emit endMoveRows();
}

void PlaylistTableModel::editRow(int pos, PlaylistTableModel::EditMode_t how, PlaylistTableModel::RowData_t &data)
{
    /* Edit row's data according how */
    if(how & EDIT_TITLE) m_data[pos].title = data.title;
    if(how & EDIT_ALBUM) m_data[pos].album = data.album;
    if(how & EDIT_AUTHORS) m_data[pos].authors = data.authors;
    if(how & EDIT_GENRE) m_data[pos].genre = data.genre;

    /* Warm view for change */
    emit dataChanged(createIndex(pos, 0), createIndex(pos, 4));
}
