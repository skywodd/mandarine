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
#include <QTime>
#include <QIcon>
#include "playersliders.h"

/* Static members initialization */
const QString PlayerSliders::m_iconMuted(":/sound/mute.png");
const QString PlayerSliders::m_iconUnmuted(":/sound/unmute.png");
const int PlayerSliders::m_maximumSliderValue = 10000;

PlayerSliders::PlayerSliders(QWidget *parent) :
    QWidget(parent), m_showTimeMode(TIME_TOTAL),
    m_currentTimeValue(0), m_maximumTimeValue(0),
    m_isMuted(false), m_isSeekable(true)
{
    /* Setup UI */
    setupUi(this);

    /* Setup max value of time slider */
    player_sliders_time_slider->setMaximum(m_maximumSliderValue);

    /* Connect GUI signals to internal slots */
    connect(player_sliders_time_slider, &QSlider::valueChanged, this, &PlayerSliders::handleTimeSlider);
    connect(player_sliders_volume_slider, &QSlider::valueChanged, this, &PlayerSliders::handleVolumeSlider);
    connect(player_sliders_total_time_label, &QLabelClickable::clicked, this, &PlayerSliders::handleTotalTimeLabel);
    connect(player_sliders_volume_mute, &QAbstractButton::clicked, this, &PlayerSliders::setToggleVolumeMute);
}

PlayerSliders::~PlayerSliders()
{
}

void PlayerSliders::updateTimeLabels()
{
    int hours, minutes, seconds, millis;

    /* Compute current time */
    seconds = m_currentTimeValue / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    millis = m_currentTimeValue;
    QTime currentTime(hours % 60, minutes % 60, seconds % 60, millis % 1000);
    player_sliders_current_time_label->setText(currentTime.toString("mm:ss"));

    /* Branch according display mode */
    if (m_showTimeMode == TIME_TOTAL) {

        /* Compute total time */
        seconds = m_maximumTimeValue / 1000;
        minutes = seconds / 60;
        hours = minutes / 60;
        millis = m_maximumTimeValue;
        QTime totalTime(hours % 60, minutes % 60, seconds % 60, millis % 1000);
        player_sliders_total_time_label->setText(totalTime.toString("mm:ss"));

    } else {

        /* Compute remaining time */
        seconds = (m_maximumTimeValue - m_currentTimeValue) / 1000;
        minutes = seconds / 60;
        hours = minutes / 60;
        millis = m_currentTimeValue;
        QTime totalTime(hours % 60, minutes % 60, seconds % 60, millis % 1000);
        player_sliders_total_time_label->setText(totalTime.toString("-mm:ss"));
    }
}

void PlayerSliders::setCurrentTime(qint64 time)
{
    /* Check if time is in a valid range */
    if (time > m_maximumTimeValue)
        m_currentTimeValue = m_maximumTimeValue;
    else
        m_currentTimeValue = time;

    /* Set slider value */
    player_sliders_time_slider->setValue(AbsoluteTimeToSliderValue(m_currentTimeValue));

    /* Set time labels values */
    updateTimeLabels();
}

void PlayerSliders::setTotalTime(qint64 time)
{
    /* Store maximum value */
    m_maximumTimeValue = time;

    /* Refresh time labels & slider */
    setCurrentTime(m_currentTimeValue);
}

void PlayerSliders::setVolume(int volume)
{
    /* Unmute if necessary */
    if (m_isMuted)
        setMute(false);

    /* Change volume slider value */
    player_sliders_volume_slider->setValue(volume);

    /* Refresh volume label value */
    player_sliders_volume_label->setText(QString("%1%").arg(volume));
}

void PlayerSliders::setMute(bool muted)
{
    /* Check if mute state is already set */
    if (m_isMuted == muted)
        return;

    /* Branch according mode */
    if (muted) {

        /* Display the muted icon */
        player_sliders_volume_mute->setIcon(QIcon(m_iconUnmuted));

        /* Disable the volume slider and label */
        player_sliders_volume_label->setEnabled(false);
        player_sliders_volume_slider->setEnabled(false);

    } else {

        /* Display the unmuted icon */
        player_sliders_volume_mute->setIcon(QIcon(m_iconMuted));

        /* Enable the volume slider and label */
        player_sliders_volume_label->setEnabled(true);
        player_sliders_volume_slider->setEnabled(true);
    }

    /* Store new mute status */
    m_isMuted = muted;

    /* Emit the muteChanged signal */
    emit muteChanged(m_isMuted);
}

void PlayerSliders::setBuffering(int percent)
{
    /* Display buffering message */
    player_sliders_current_time_label->setText(QString("%1%").arg(percent));
}

void PlayerSliders::setSeekable(bool seekable)
{
    /* Store the new seekable status */
    m_isSeekable = seekable;
    player_sliders_time_slider->setEnabled(m_isSeekable);
}

void PlayerSliders::handleTimeSlider(int value)
{
    /* Check if slider is seekable */
    if (!m_isSeekable)
        return;

    /* Store the new time value */
    m_currentTimeValue = SliderValueToAbsoluteTime(value);

    /* Set time labels values */
    updateTimeLabels();

    /* Emit seekChanged signal */
    emit seekChanged(m_currentTimeValue);
}

void PlayerSliders::handleVolumeSlider(int value)
{
    /* Refresh volume label value */
    player_sliders_volume_label->setText(QString("%1%").arg(value));

    /* Emit volumeChanged signal */
    emit volumeChanged(value);
}

void PlayerSliders::handleTotalTimeLabel()
{
    /* Change total time label display mode */
    if(m_showTimeMode == TIME_TOTAL)
        m_showTimeMode = TIME_REMAIN;
    else
        m_showTimeMode = TIME_TOTAL;

    /* Refresh time labels values */
    updateTimeLabels();
}

void PlayerSliders::setToggleVolumeMute()
{
    /* Set the new mute status */
    setMute(!m_isMuted);
}
