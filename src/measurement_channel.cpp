#include "measurement_channel.h"
#include <QRandomGenerator>

#include "acquisition_engine.h"


MeasurementChannel::MeasurementChannel(QObject *parent)
    : QObject(parent) {
    m_index = AcquisitionEngine::indexCounter;
    AcquisitionEngine::indexCounter++;
}

QString MeasurementChannel::label() const {
    return m_label;
}

int MeasurementChannel::index() const {
    return m_index;
}

void MeasurementChannel::setLabel(const QString &label) {
    // Avoid emitting a change signal if the value didn't actually change
    if (m_label == label)
        return;

    m_label = label;
    emit labelChanged();
}

double MeasurementChannel::currentValue() const {
    return m_currentValue;
}

void MeasurementChannel::randomize() {
    m_currentValue = QRandomGenerator::global()->generateDouble() * 100.0;
    emit currentValueChanged();
}

void MeasurementChannel::reset() {
    // Avoid emitting a signal if the value is already at its default
    if (m_currentValue == 0.0)
        return;

    m_currentValue = 0.0;
    emit currentValueChanged();
}

void MeasurementChannel::updateValue(double value) {
    // Always emit, even if the value is unchanged: this is called once per
    // acquisition tick, and the chart uses this signal to know a new sample
    // arrived. Skipping it on a repeated value (e.g. clamped at 0 or 100)
    // would make this channel's series fall behind the others.
    m_currentValue = value;
    emit currentValueChanged();
}

