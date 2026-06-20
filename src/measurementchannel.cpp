#include "measurementchannel.h"
#include <QRandomGenerator>

MeasurementChannel::MeasurementChannel(QObject *parent)
    : QObject(parent)
{
}

QString MeasurementChannel::label() const
{
    return m_label;
}

void MeasurementChannel::setLabel(const QString &label)
{
    // Avoid emitting a change signal if the value didn't actually change
    if (m_label == label)
        return;

    m_label = label;
    emit labelChanged();
}

double MeasurementChannel::currentValue() const
{
    return m_currentValue;
}

void MeasurementChannel::randomize()
{
    m_currentValue = QRandomGenerator::global()->generateDouble() * 100.0;
    emit currentValueChanged();
}