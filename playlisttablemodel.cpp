#include <QPixmap>
#include <QStandardItem>

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

int PlaylistTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int PlaylistTableModel::columnCount(const QModelIndex &parent ) const
{
    return 5;
}

QVariant PlaylistTableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole :

            return m_data[index.row()][index.column()];
            break;
    case Qt::FontRole:
        if( index.row() == m_currentIndex )
        {
            QFont font;
            font.setBold(true);
            return font;
        }
        break;
    }
    return QVariant();
}

QVariant PlaylistTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole :
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return QString( tr("Titre"));
                break;
            case 1:
                return QString( tr("Album"));
                break;
            case 2:
                return QString( tr("Artiste"));
                break;
            case 3:
                return QString( tr("Genre"));
                break;
            case 4:
                return QString( tr("Durée"));
                break;
            }
            break;
        }
    case Qt::DecorationRole :
        if(orientation == Qt::Vertical && section == m_currentIndex)
        {
            return QPixmap(m_playingIcon);

        }
        break;
    }
    return QVariant();
}

QString PlaylistTableModel::getLine(int row) const
{
    return m_data[row].join(" ");
}

void PlaylistTableModel::addRow(int pos, QStringList row)
{
    // If of out of range
    if(pos>=m_data.size())
        //push the row at the end
        m_data.push_back(row);

    else
        //insert the row
        m_data.insert(pos,row);

    emit dataChanged();
}

void PlaylistTableModel::removeRow(int pos)
{   
    m_data.removeAt(pos);
    emit dataChanged();
}

void PlaylistTableModel::swapRow(int row1, int row2)
{
    // Swap two lines
    m_data.swap(row1,row2);

    // If the changed is the current playing
    if( row1 == m_currentIndex )
        m_currentIndex = row2;
    else if ( row2 == m_currentIndex )
        m_currentIndex = row1;

    emit dataChanged();
}

void PlaylistTableModel::setCurrentIndex(int pos)
{
    m_currentIndex = pos;
}

void PlaylistTableModel::flush()
{
    m_currentIndex = -1;
    m_data.clear();

    emit dataChanged();
}
