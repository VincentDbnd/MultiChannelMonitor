#pragma once

#include <QObject>
#include <QTimer>

// Generates simulated samples on a background thread and emits them per channel.
class AcquisitionWorker : public QObject {
    Q_OBJECT

public:
    explicit AcquisitionWorker(int channelCount, QObject *parent = nullptr);

public slots:
    // Triggered from the GUI thread via queued connections
    void start();

    void stop();

signals:
    // Emitted once per channel, per timer tick.
    void sampleReady(int channelIndex, double value);

private slots:
    void generateSamples();

private:
    int m_channelCount;
    QTimer *m_timer = nullptr;
};
