#include <QtTest>

#include "measurement_channel.h"

class TestMeasurementChannel : public QObject {
    Q_OBJECT

private slots:
    void initialValueIsZero();
    void setLabelOnlyEmitsOnChange();
    void updateValueAlwaysEmits();
    void resetGoesBackToZero();
};

void TestMeasurementChannel::initialValueIsZero() {
    MeasurementChannel channel;
    QCOMPARE(channel.currentValue(), 0.0);
}

void TestMeasurementChannel::setLabelOnlyEmitsOnChange() {
    MeasurementChannel channel;
    QSignalSpy spy(&channel, &MeasurementChannel::labelChanged);

    channel.setLabel("Channel 1");
    QCOMPARE(spy.count(), 1);

    channel.setLabel("Channel 1"); // same label -> no redundant signal
    QCOMPARE(spy.count(), 1);

    channel.setLabel("Channel 2");
    QCOMPARE(spy.count(), 2);
}

void TestMeasurementChannel::updateValueAlwaysEmits() {
    MeasurementChannel channel;
    QSignalSpy spy(&channel, &MeasurementChannel::currentValueChanged);

    channel.updateValue(42.0);
    QCOMPARE(spy.count(), 1);

    channel.updateValue(42.0); // same value again, must still emit
    QCOMPARE(spy.count(), 2);

    channel.updateValue(0.0);
    channel.updateValue(0.0);
    QCOMPARE(spy.count(), 4);
}

void TestMeasurementChannel::resetGoesBackToZero() {
    MeasurementChannel channel;
    channel.updateValue(77.0);

    QSignalSpy spy(&channel, &MeasurementChannel::currentValueChanged);
    channel.reset();
    QCOMPARE(channel.currentValue(), 0.0);
    QCOMPARE(spy.count(), 1);

    channel.reset(); // already zero -> no redundant signal
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(TestMeasurementChannel)
#include "tst_measurementchannel.moc"
