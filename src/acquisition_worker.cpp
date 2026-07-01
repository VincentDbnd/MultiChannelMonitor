#include "acquisition_worker.h"
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>
#include <algorithm>

namespace {
    constexpr double kMaxStep = 15.0; // max absolute change per tick
    constexpr double kMinValue = 0.0;
    constexpr double kMaxValue = 100.0;
}

AcquisitionWorker::AcquisitionWorker(int channelCount, QObject *parent)
    : QObject(parent)
    , m_channelCount(channelCount)
    , m_lastValues(channelCount, 0.0)
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

void AcquisitionWorker::reset()
{
    std::fill(m_lastValues.begin(), m_lastValues.end(), 0.0);
}

void AcquisitionWorker::generateSamples()
{
    for (int i = 0; i < m_channelCount; ++i) {
        const double step = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * kMaxStep;
        const double value = std::clamp(m_lastValues[i] + step, kMinValue, kMaxValue);
        m_lastValues[i] = value;
        emit sampleReady(i, value);
    }
}