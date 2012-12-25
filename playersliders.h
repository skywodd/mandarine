#ifndef PLAYERSLIDERS_H
#define PLAYERSLIDERS_H

/* Dependencies */
#include "ui_playersliders.h"

/**
 * @brief Player's sliders controls widget
 *
 * This class is designed to handle all sliders operation of the media player.
 * \n
 * This widget handle :
 * - Time slider, with current time and total time or remaining time labels
 * - Volume slider, with volume label and mute button
 */
class PlayerSliders : public QWidget, protected Ui::PlayerSliders
{
    Q_OBJECT
    
public:

    /**
     * Time display mode of the "total time" label
     */
    typedef enum {
        TIME_TOTAL, /*!< Total time display */
        TIME_REMAIN /*!< Remaining time display */
    } TimeDisplayMode_t;

    /**
     * Default constructor of the widget
     *
     * @brief PlayerSliders constructor
     * @param parent Parent widget
     */
    explicit PlayerSliders(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief PlayerSliders destructor
     * @remarks Ready for overload
     */
    virtual ~PlayerSliders();

protected:
    /** Time display mode of the "remaining time" label */
    TimeDisplayMode_t m_showTimeMode;

    /** Current value of the time slider */
    qint64 m_currentTimeValue;

    /** Maximum value of the time slider */
    qint64 m_maximumTimeValue;

    /** Current mute statuts of the widget */
    bool m_isMuted;

    /** Current seekable status of the widget */
    bool  m_isSeekable;

    /** Muted sound output icon ressource location */
    static const QString m_iconMuted;

    /** Unmuted sound output icon ressource location  */
    static const QString m_iconUnmuted;

    /** Maximum value of the time slider */
    static const int m_maximumSliderValue;

    /**
     * Scale an absolute time value into a slider time range value
     *
     * @brief AbsoluteTimeToSliderValue
     * @param time The absolute time value to scale
     * @return The scaled time value into slider range
     */
    inline int AbsoluteTimeToSliderValue(qint64 time)
    {
        return time * m_maximumSliderValue / m_maximumTimeValue;
    }

    /**
     * Scale a slider time value into an absolute time value
     *
     * @brief SliderValueToAbsoluteTime
     * @param value The slider time value
     * @return The scaled time value in absolute time range
     */
    inline qint64 SliderValueToAbsoluteTime(int value)
    {
        return (qint64) value * m_maximumTimeValue / m_maximumSliderValue;
    }

    /**
     * Update time's labels values according the display mode
     *
     * @brief updateTimeLabels
     */
    void updateTimeLabels();

signals:
    /**
     * Mute status changed signal
     *
     * @brief muteChanged
     * @param muted True if muted, false otherwise
     */
    void muteChanged(bool muted);

    /**
     * Volume changed signal
     *
     * @brief volumeChanged
     * @param volume The new volume value
     */
    void volumeChanged(int volume);

    /**
     * Time seek changed signal
     *
     * @brief seekChanged
     * @param time The new time seek value
     */
    void seekChanged(qint64 time);

public slots:
    /**
     * Set the current time of the time seek slider
     *
     * @brief setCurrentTime
     * @param time The current time in absolute value
     */
    void setCurrentTime(qint64 time);

    /**
     * Set the maximum time of the time seek slider
     *
     * @brief setTotalTime
     * @param time The total time in absolute value
     */
    void setTotalTime(qint64 time);

    /**
     * Set the volume
     *
     * @brief setVolume
     * @param volume The new volume
     */
    void setVolume(int volume);

    /**
     * Set the mute status
     *
     * @brief setMute
     * @param muted The new mute status
     */
    void setMute(bool muted);

    /**
     * Set the buffering percent display value
     *
     * @brief setBuffering
     * @param percent The buffering percent value
     */
    void setBuffering(int percent);

    /**
     * Set the seekable status of the widget
     *
     * @brief setSeekable
     * @param seekable The new seekable status of the widget
     */
    void setSeekable(bool seekable);

    /**
     * Handle volume mute "clicked" signal
     *
     * @brief handleVolumeMute
     */
    void setToggleVolumeMute();

protected slots:
    /**
     * Handle time slider "moved" signal
     *
     * @brief handleTimeSlider
     */
    void handleTimeSlider(int value);

    /**
     * Handle volume slider "moved" signal
     *
     * @brief handleVolumeSlider
     */
    void handleVolumeSlider(int value);

    /**
     * Handle total time label "clicked" signal
     *
     * @brief handleTotalTimeLabel
     */
    void handleTotalTimeLabel();

};

#endif // PLAYERSLIDERS_H
