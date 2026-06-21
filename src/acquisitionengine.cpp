#include "acquisitionengine.h"
#include <utility>

AcquisitionEngine::AcquisitionEngine(QObject *parent)
    : QObject(parent)
{
    // Create three channels
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));

    m_channels.at(0)->setLabel("Channel 1");
    m_channels.at(1)->setLabel("Channel 2");
    m_channels.at(2)->setLabel("Channel 3");

    // A single timer drives all channels
    m_timer.setInterval(200);
    connect(&m_timer, &QTimer::timeout, this, &AcquisitionEngine::sampleAllChannels);
}

QQmlListProperty<MeasurementChannel> AcquisitionEngine::channels()
{
    return QQmlListProperty<MeasurementChannel>(this, &m_channels,
        &AcquisitionEngine::channelCount, &AcquisitionEngine::channelAt);
}

bool AcquisitionEngine::isRunning() const
{
    return m_timer.isActive();
}

void AcquisitionEngine::start()
{
    if (m_timer.isActive())
        return;
    m_timer.start();
    emit runningChanged();
}

void AcquisitionEngine::pause()
{
    if (!m_timer.isActive())
        return;
    m_timer.stop();
    emit runningChanged();
}

void AcquisitionEngine::reset()
{
    pause();
    for (auto *channel : std::as_const(m_channels))
        channel->reset();
}

void AcquisitionEngine::sampleAllChannels()
{
    for (auto *channel : std::as_const(m_channels))
        channel->randomize();
}

qsizetype AcquisitionEngine::channelCount(QQmlListProperty<MeasurementChannel> *list)
{
    return static_cast<QList<MeasurementChannel *> *>(list->data)->size();
}

MeasurementChannel *AcquisitionEngine::channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index)
{
    return static_cast<QList<MeasurementChannel *> *>(list->data)->at(index);
}