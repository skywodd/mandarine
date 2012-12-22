#ifndef QLABELCLICKABLE_H
#define QLABELCLICKABLE_H

/* Dependencies */
#include <QLabel>

/**
 * @brief Clickable label widget
 *
 * This class is a extension of the classical QLabel widget with clicked() signal support.
 */
class QLabelClickable : public QLabel
{
    Q_OBJECT

public:
    /**
     * Default constructor of the widget
     *
     * @brief QLabelClickable constructor
     * @param parent Parent widget
     */
    explicit QLabelClickable(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief QLabelClickable destructor
     */
    virtual ~QLabelClickable();

protected:
    /**
     * "Mouse Press Event" handler
     *
     * @brief mousePressEvent overload
     * @param ev Received mouse event
     */
    virtual void mousePressEvent(QMouseEvent *ev);

signals:
    /**
     * Clicked signal
     *
     * @brief clicked
     */
    void clicked();
};

#endif // QLABELCLICKABLE_H
