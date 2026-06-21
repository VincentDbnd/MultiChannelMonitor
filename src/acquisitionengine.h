#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QTimer>
#include <QtQml/qqmlregistration.h>
#include <QList>

#include "measurementchannel.h"

class AcquisitionEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // CONSTANT: the list of channel pointers never changes after construction.
    // Individual channel VALUES still update via their own NOTIFY signals.
    Q_PROPERTY(QQmlListProperty<MeasurementChannel> channels READ channels CONSTANT)
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)

public:
    explicit AcquisitionEngine(QObject *parent = nullptr);

    QQmlListProperty<MeasurementChannel> channels();
    bool isRunning() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

    signals:
        void runningChanged();

private slots:
    void sampleAllChannels();

private:
    // Static callbacks required by QQmlListProperty's C-style API
    static qsizetype channelCount(QQmlListProperty<MeasurementChannel> *list);
    static MeasurementChannel *channelAt(QQmlListProperty<MeasurementChannel> *list, qsizetype index);

    QList<MeasurementChannel *> m_channels;
    QTimer m_timer;
};