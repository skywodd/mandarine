#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H

/* Dependencies */
#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QList>

/**
 * @brief Playlist TableView widget's data model
 *
 * This class is the TableModel used by the playlist's TableView widget.
 * This class store and allow display of playlist human-readable data.
 */
class PlaylistTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * Playlist data model constructor
     *
     * @brief PlaylistTableModel constructor
     * @param parent Parent view
     */
    PlaylistTableModel(QObject *parent);

    /**
     * Playlist data model destructor
     *
     * @brief PlaylistTableModel destructor
     * @remarks Ready for overload
     */
    virtual ~PlaylistTableModel();

    /**
     * Return the number of rows stored in the model
     *
     * @brief rowCount
     * @param parent Parent model's index (not used)
     * @return The number of rows stored in the model
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * Return the number of columns stored in the model
     *
     * @brief columnCount
     * @param parent Parent model's index (not used)
     * @return The number of columns stored in the model
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * Return the data and graphics for display in view
     *
     * @brief data
     * @param index Table index to display
     * @param role Table role to retrieve
     * @return The data specified by role for the specified index of the table model
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * Return the data and graphics for header display in view
     *
     * @brief headerData
     * @param section Header index to display
     * @param orientation Orientation of the header (H or V)
     * @param role Table role to retrieve
     * @return The header data specified by role for the selected section and orientation
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

    /**
     * Check if the specified row's data match with the specified search mask or not
     *
     * @brief hasToBeHidden
     * @param row Row index to check
     * @param mask Mask to check against row's data
     * @return True if the data DON'T match, false otherwise
     */
    bool hasToBeHidden(int row, const QString& mask) const;

    /**
     * Get the currently played row index
     *
     * @brief getCurrentIndex
     * @return The currently played row index
     */
    int getCurrentIndex() const;

public:
    /** Row data container */
    typedef struct {
        QString title; /*!< Title */
        QString album; /*!< Album name */
        QString authors; /*!< Authors (separated by ',') */
        QString genre; /*!< Musical genre */
        QString duration; /*!< Sound duration */
    } RowData_t;

    /** Data edit modes */
    typedef enum {
        EDIT_NONE = 0, /*!< No edit */
        EDIT_TITLE = 2, /*!< Edit title */
        EDIT_ALBUM = 4, /*!< Edit album name */
        EDIT_AUTHORS = 8, /*!< Edit authors list */
        EDIT_GENRE = 16, /*!< Edit musical genre */
        EDIT_DURATION = 32 /*!< Edit sound duration */
    } EditMode_t;

protected:
    /** Row and column data container */
    QList<RowData_t> m_data;

    /** Currently played row index */
    int m_currentIndex;

    /** Playing icon ressource location */
    static const QString m_playingIcon;

signals:
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles = QVector<int>());
    void rowsAboutToBeInserted(const QModelIndex& parent, int start, int end);
    void rowsAboutToBeMoved(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationRow);
    void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end);
    void rowsInserted(const QModelIndex& parent, int start, int end);
    void rowsMoved(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationRow);
    void rowsRemoved(const QModelIndex& parent, int start, int end);
    void modelAboutToBeReset();
    void modelReset();

public slots:

    /**
     * Set the currently played index
     *
     * @brief setCurrentIndex
     * @param pos The currently played index
     */
    void setCurrentIndex(int pos);

    /**
     * Flush all data of the model
     *
     * @brief flush
     */
    void flush();

    /**
     * Add a row of data to the model
     *
     * @brief addRow
     * @param data Row's data
     */
    void addRow(const RowData_t& data);

    /**
     * Remove a row of data from the model
     *
     * @brief removeRow
     * @param pos Position of the row to remove
     */
    void removeRow(int pos);

    /**
     * Move a row of data in the model
     *
     * @brief moveRow
     * @param from From position
     * @param to To position
     */
    void moveRow(int from, int to);

    /**
     * Edit data of a row
     *
     * @brief editRow
     * @param pos Row to edit
     * @param how Data's fields to edit (can be logicaly OR'ed)
     * @param data New data to store
     */
    void editRow(int pos, EditMode_t how, RowData_t& data);
};

#endif // PLAYLISTTABLEMODEL_H
