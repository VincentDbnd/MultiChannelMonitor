#pragma once

#include <QObject>
#include <QTimer>
#include <QVector>

// Generates simulated samples on a background thread and emits them per channel.
class AcquisitionWorker : public QObject {
    Q_OBJECT

public:
    explicit AcquisitionWorker(int channelCount, QObject *parent = nullptr);

public slots:
    // Triggered from the GUI thread via queued connections
    void start();

    void stop();

    // Reinitializes the random-walk state so it matches a freshly reset channel.
    void reset();

signals:
    // Emitted once per channel, per timer tick.
    void sampleReady(int channelIndex, double value);

private slots:
    void generateSamples();

private:
    int m_channelCount;
    QTimer *m_timer = nullptr;

    QVector<double> m_lastValues;
};
