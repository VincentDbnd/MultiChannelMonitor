#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QThread>
#include <QtQml/qqmlregistration.h>
#include <QList>

#include "measurementchannel.h"
#include "acquisitionworker.h"

// Owns a fixed collection of MeasurementChannel instances (GUI thread) and
// an AcquisitionWorker running on a dedicated QThread that generates
// simulated samples. Samples cross from the worker thread to the GUI
// thread via a queued signal/slot connection, with no manual locking.
class AcquisitionEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QQmlListProperty<MeasurementChannel> channels READ channels CONSTANT)
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)

public:
    explicit AcquisitionEngine(QObject *parent = nullptr);
    ~AcquisitionEngine() override;

    QQmlListProperty<MeasurementChannel> channels();
    bool isRunning() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

    signals:
        void runningChanged();

    // Internal control signals sent to the worker thread (auto-queued)
    void requestStart();
    void requestStop();

private slots:
    // Invoked on the GUI thread whenever the worker emits a new sample
    void onSampleReady(int channelIndex, double value);

private:
    static qsizetype channelCount(QQmlListProperty<MeasurementChannel> *list);
    static MeasurementChannel *channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index);

    QList<MeasurementChannel *> m_channels;
    QThread m_workerThread;
    AcquisitionWorker *m_worker = nullptr;
    bool m_running = false;
};