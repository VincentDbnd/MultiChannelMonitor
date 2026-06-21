#include "acquisitionworker.h"
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>


AcquisitionWorker::AcquisitionWorker(int channelCount, QObject *parent)
    : QObject(parent)
    , m_channelCount(channelCount)
{
}

void AcquisitionWorker::start()
{
    if (!m_timer) {
        m_timer = new QTimer(this);
        m_timer->setInterval(500);
        connect(m_timer, &QTimer::timeout, this, &AcquisitionWorker::generateSamples);
    }
    qDebug() << "Worker thread:" << QThread::currentThread();
    m_timer->start();
}

void AcquisitionWorker::stop()
{
    if (m_timer)
        m_timer->stop();
}

void AcquisitionWorker::generateSamples()
{
    for (int i = 0; i < m_channelCount; ++i) {
        const double value = QRandomGenerator::global()->generateDouble() * 100.0;
        emit sampleReady(i, value);
    }
}