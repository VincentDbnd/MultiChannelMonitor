#include "acquisitionengine.h"
#include <utility>

AcquisitionEngine::AcquisitionEngine(QObject *parent)
    : QObject(parent)
{
    // Channels live on the GUI thread: parented to "this", their
    // Q_PROPERTYs are read directly by QML bindings.
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));

    m_channels.at(0)->setLabel("Channel 1");
    m_channels.at(1)->setLabel("Channel 2");
    m_channels.at(2)->setLabel("Channel 3");

    // The worker must NOT have a parent before moveToThread: a parented
    // QObject cannot be moved to another thread.
    m_worker = new AcquisitionWorker(m_channels.size());
    m_worker->moveToThread(&m_workerThread);

    // Worker -> GUI: Qt automatically uses a queued connection here since
    // sender and receiver live on different threads. No mutex needed.
    connect(m_worker, &AcquisitionWorker::sampleReady,
            this, &AcquisitionEngine::onSampleReady);

    // GUI -> worker control signals, also auto-queued across threads.
    connect(this, &AcquisitionEngine::requestStart, m_worker, &AcquisitionWorker::start);
    connect(this, &AcquisitionEngine::requestStop, m_worker, &AcquisitionWorker::stop);

    // Delete the worker once the thread's event loop actually stops.
    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    m_workerThread.start();
}

AcquisitionEngine::~AcquisitionEngine()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

QQmlListProperty<MeasurementChannel> AcquisitionEngine::channels()
{
    return QQmlListProperty<MeasurementChannel>(this, &m_channels,
        &AcquisitionEngine::channelCount, &AcquisitionEngine::channelAt);
}

bool AcquisitionEngine::isRunning() const
{
    return m_running;
}

void AcquisitionEngine::start()
{
    if (m_running)
        return;
    m_running = true;
    emit requestStart();
    emit runningChanged();
}

void AcquisitionEngine::pause()
{
    if (!m_running)
        return;
    m_running = false;
    emit requestStop();
    emit runningChanged();
}

void AcquisitionEngine::reset()
{
    pause();
    for (auto *channel : std::as_const(m_channels))
        channel->reset();
}

void AcquisitionEngine::onSampleReady(int channelIndex, double value)
{
    if (channelIndex < 0 || channelIndex >= m_channels.size())
        return;
    m_channels.at(channelIndex)->updateValue(value);
}

qsizetype AcquisitionEngine::channelCount(QQmlListProperty<MeasurementChannel> *list)
{
    return static_cast<QList<MeasurementChannel *> *>(list->data)->size();
}

MeasurementChannel *AcquisitionEngine::channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index)
{
    return static_cast<QList<MeasurementChannel *> *>(list->data)->at(index);
}