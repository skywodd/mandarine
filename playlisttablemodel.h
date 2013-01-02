#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H


#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <QVariant>
#include <QStringList>

class PlaylistTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PlaylistTableModel(QObject *parent);
    virtual ~PlaylistTableModel();


    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

    QString getLine(int row) const;

protected:
    QList<QStringList> m_data;
    int m_currentIndex;

    /** Playing icon ressource location */
    static const QString m_playingIcon;

signals:
    void dataChanged();

public slots:


    void setCurrentIndex(int pos);
    void flush();

    void addRow(int pos, QStringList row);
    void removeRow(int pos);
    void swapRow(int row1, int row2);
};

#endif // PLAYLISTTABLEMODEL_H
