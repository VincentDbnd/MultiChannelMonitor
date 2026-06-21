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

public:
    explicit MeasurementChannel(QObject *parent = nullptr);

    QString label() const;

    void setLabel(const QString &label);

    double currentValue() const;

    // Callable from QML; generates a new random value and notifies listeners
    Q_INVOKABLE void randomize();

    Q_INVOKABLE void reset();

    // Called by AcquisitionEngine on the GUI thread.
    // Safe to call directly here — never call from the worker thread.
    void updateValue(double value);

signals:
    void labelChanged();

    void currentValueChanged();

private:
    QString m_label;
    double m_currentValue = 0.0;
};
