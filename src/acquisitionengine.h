#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QThread>
#include <QtQml/qqmlregistration.h>
#include <QList>

#include "measurementchannel.h"
#include "acquisitionworker.h"
#include "NotificationsModel.h"

// Owns the channels (GUI thread) and drives the AcquisitionWorker on a background thread.
class AcquisitionEngine : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QQmlListProperty<MeasurementChannel> channels READ channels CONSTANT)
    Q_PROPERTY(NotificationsModel* notifications READ notifications CONSTANT)
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)

public:
    explicit AcquisitionEngine(QObject *parent = nullptr);
    ~AcquisitionEngine() override;

    QQmlListProperty<MeasurementChannel> channels();
    NotificationsModel *notifications() const;
    bool isRunning() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

signals:
    void runningChanged();
    void requestStart();
    void requestStop();

private slots:
    void onSampleReady(int channelIndex, double value);

private:
    void verifySample(int channelIndex, double value);

    static qsizetype channelCount(QQmlListProperty<MeasurementChannel> *list);
    static MeasurementChannel *channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index);

    QList<MeasurementChannel *> m_channels;
    NotificationsModel *m_notifications = nullptr;
    QThread m_workerThread;
    AcquisitionWorker *m_worker = nullptr;
    bool m_running = false;
};
