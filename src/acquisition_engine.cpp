#include "acquisition_engine.h"
#include <utility>

int AcquisitionEngine::indexCounter = 0;

AcquisitionEngine::AcquisitionEngine(QObject *parent)
    : QObject(parent) {
    m_notifications = new NotificationsModel(this);

    // Channels live on the GUI thread
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));
    m_channels.append(new MeasurementChannel(this));

    m_channels.at(0)->setLabel("Channel 1");
    m_channels.at(1)->setLabel("Channel 2");
    m_channels.at(2)->setLabel("Channel 3");

    // No parent before moveToThread: parented QObjects cannot be moved to another thread.
    m_worker = new AcquisitionWorker(m_channels.size());
    m_worker->moveToThread(&m_workerThread);

    connect(m_worker, &AcquisitionWorker::sampleReady,
            this, &AcquisitionEngine::onSampleReady);
    connect(this, &AcquisitionEngine::requestStart, m_worker, &AcquisitionWorker::start);
    connect(this, &AcquisitionEngine::requestStop, m_worker, &AcquisitionWorker::stop);

    // Delete the worker once the thread's event loop actually stops.
    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    m_workerThread.start();
}

AcquisitionEngine::~AcquisitionEngine() {
    m_workerThread.quit();
    m_workerThread.wait();
}

QQmlListProperty<MeasurementChannel> AcquisitionEngine::channels() {
    return QQmlListProperty<MeasurementChannel>(this, &m_channels,
                                                &AcquisitionEngine::channelCount,
                                                &AcquisitionEngine::channelAt);
}

NotificationsModel *AcquisitionEngine::notifications() const {
    return m_notifications;
}

bool AcquisitionEngine::isRunning() const {
    return m_running;
}

void AcquisitionEngine::start() {
    if (m_running)
        return;
    m_running = true;
    emit requestStart();
    emit runningChanged();
}

void AcquisitionEngine::pause() {
    if (!m_running)
        return;
    m_running = false;
    emit requestStop();
    emit runningChanged();
}

void AcquisitionEngine::reset() {
    pause();
    for (auto *channel: std::as_const(m_channels))
        channel->reset();
    m_notifications->clear();
}

void AcquisitionEngine::onSampleReady(int channelIndex, double value) {
    if (channelIndex < 0 || channelIndex >= m_channels.size())
        return;
    m_channels.at(channelIndex)->updateValue(value);
    verifySample(channelIndex, value);
}

void AcquisitionEngine::verifySample(int channelIndex, double value) {
    MeasurementChannel *channel = m_channels.at(channelIndex);
    if (value > m_dangerThreshold) {
        m_notifications->addNotification(
            "DANGER",
            QString("Value %1 exceeds %2 threshold.").arg(value).arg(m_dangerThreshold),
            channel->label(),
            NotificationsModel::Danger
        );
    } else if (value > m_warningThreshold) {
        m_notifications->addNotification(
            "WARNING",
            QString("Value %1 exceeds %2 threshold.").arg(value).arg(m_warningThreshold),
            channel->label(),
            NotificationsModel::Warning
        );
    }
}

double AcquisitionEngine::warningThreshold() const { return m_warningThreshold; }

void AcquisitionEngine::setWarningThreshold(double threshold) {
    if (m_warningThreshold == threshold) return;
    m_warningThreshold = threshold;
    emit warningThresholdChanged();
}

double AcquisitionEngine::dangerThreshold() const { return m_dangerThreshold; }

void AcquisitionEngine::setDangerThreshold(double threshold) {
    if (m_dangerThreshold == threshold) return;
    m_dangerThreshold = threshold;
    emit dangerThresholdChanged();
}

qsizetype AcquisitionEngine::channelCount(QQmlListProperty<MeasurementChannel> *list) {
    return static_cast<QList<MeasurementChannel *> *>(list->data)->size();
}

MeasurementChannel *AcquisitionEngine::channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index) {
    return static_cast<QList<MeasurementChannel *> *>(list->data)->at(index);
}
