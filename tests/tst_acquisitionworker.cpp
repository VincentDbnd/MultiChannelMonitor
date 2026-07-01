#include <QtTest>

#include "acquisition_worker.h"

class TestAcquisitionWorker : public QObject {
    Q_OBJECT

private slots:
    void samplesStayWithinChannelCountAndValueBounds();
    void stopStopsEmitting();
};

void TestAcquisitionWorker::samplesStayWithinChannelCountAndValueBounds() {
    constexpr int channelCount = 3;
    AcquisitionWorker worker(channelCount);
    QSignalSpy spy(&worker, &AcquisitionWorker::sampleReady);

    worker.start();
    // Interval is 500ms; wait for a few ticks worth of samples.
    QVERIFY(spy.wait(1000));
    QVERIFY(spy.wait(1000));
    QVERIFY(spy.wait(1000));
    worker.stop();

    QVERIFY(spy.count() >= channelCount * 2);
    for (const QList<QVariant> &sample : spy) {
        const int channelIndex = sample.at(0).toInt();
        const double value = sample.at(1).toDouble();
        QVERIFY(channelIndex >= 0 && channelIndex < channelCount);
        QVERIFY(value >= 0.0 && value <= 100.0);
    }
}

void TestAcquisitionWorker::stopStopsEmitting() {
    AcquisitionWorker worker(1);
    QSignalSpy spy(&worker, &AcquisitionWorker::sampleReady);

    worker.start();
    QVERIFY(spy.wait(1000));
    worker.stop();

    const int countAfterStop = spy.count();
    QTest::qWait(700); // longer than the 500ms tick interval
    QCOMPARE(spy.count(), countAfterStop);
}

QTEST_GUILESS_MAIN(TestAcquisitionWorker)
#include "tst_acquisitionworker.moc"
