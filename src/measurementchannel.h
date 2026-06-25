#pragma once

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

// Represents a single measurement source exposed to QML.
class MeasurementChannel : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(double currentValue READ currentValue NOTIFY currentValueChanged)
    Q_PROPERTY(double threshold READ threshold NOTIFY thresholdChanged)

public:
    explicit MeasurementChannel(QObject *parent = nullptr);

    QString label() const;

    void setLabel(const QString &label);

    double currentValue() const;

    double threshold() const;

    void setThreshold(const double &threshold);

    // Callable from QML; generates a new random value and notifies listeners
    Q_INVOKABLE void randomize();

    Q_INVOKABLE void reset();

    // Called by AcquisitionEngine on the GUI thread.
    // Safe to call directly here — never call from the worker thread.
    void updateValue(double value);

signals:
    void labelChanged();
    void currentValueChanged();
    void thresholdChanged();

private:
    QString m_label;
    double m_currentValue = 0.0;
    double m_threshold = 90.0;
};
