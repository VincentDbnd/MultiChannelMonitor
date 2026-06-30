#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QThread>
#include <QtQml/qqmlregistration.h>
#include <QList>

#include "measurement_channel.h"
#include "acquisition_worker.h"
#include "notifications_model.h"

// Owns the channels (GUI thread) and drives the AcquisitionWorker on a background thread.
class AcquisitionEngine : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QQmlListProperty<MeasurementChannel> channels READ channels CONSTANT)
    Q_PROPERTY(NotificationsModel* notifications READ notifications CONSTANT)
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(double warningThreshold READ warningThreshold WRITE setWarningThreshold NOTIFY warningThresholdChanged)
    Q_PROPERTY(double dangerThreshold READ dangerThreshold WRITE setDangerThreshold NOTIFY dangerThresholdChanged)

public:
    explicit AcquisitionEngine(QObject *parent = nullptr);

    ~AcquisitionEngine() override;

    static int indexCounter;

    QQmlListProperty<MeasurementChannel> channels();

    NotificationsModel *notifications() const;

    bool isRunning() const;

    double warningThreshold() const;
    void setWarningThreshold(double threshold);

    double dangerThreshold() const;
    void setDangerThreshold(double threshold);

    Q_INVOKABLE void start();

    Q_INVOKABLE void pause();

    Q_INVOKABLE void reset();

signals:
    void runningChanged();
    void warningThresholdChanged();
    void dangerThresholdChanged();

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
    double m_warningThreshold = 95.0;
    double m_dangerThreshold = 98.0;
};
