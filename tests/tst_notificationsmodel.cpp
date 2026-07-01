#include <QtTest>

#include "notifications_model.h"

class TestNotificationsModel : public QObject {
    Q_OBJECT

private slots:
    void startsEmpty();
    void addNotificationPrependsMostRecentFirst();
    void exposesRolesToQml();
    void clearResetsModel();
};

void TestNotificationsModel::startsEmpty() {
    NotificationsModel model;
    QCOMPARE(model.rowCount(), 0);
}

void TestNotificationsModel::addNotificationPrependsMostRecentFirst() {
    NotificationsModel model;
    model.addNotification("WARNING", "first", "Channel 1", NotificationsModel::Warning);
    model.addNotification("DANGER", "second", "Channel 2", NotificationsModel::Danger);

    QCOMPARE(model.rowCount(), 2);

    const QModelIndex top = model.index(0, 0);
    QCOMPARE(model.data(top, NotificationsModel::LabelRole).toString(), QStringLiteral("DANGER"));
    QCOMPARE(model.data(top, NotificationsModel::CoreRole).toString(), QStringLiteral("second"));
    QCOMPARE(model.data(top, NotificationsModel::ChannelRole).toString(), QStringLiteral("Channel 2"));
    QCOMPARE(model.data(top, NotificationsModel::SeverityRole).toInt(), int(NotificationsModel::Danger));

    const QModelIndex bottom = model.index(1, 0);
    QCOMPARE(model.data(bottom, NotificationsModel::LabelRole).toString(), QStringLiteral("WARNING"));
}

void TestNotificationsModel::exposesRolesToQml() {
    NotificationsModel model;
    const auto roles = model.roleNames();

    QCOMPARE(roles.value(NotificationsModel::LabelRole), QByteArrayLiteral("label"));
    QCOMPARE(roles.value(NotificationsModel::CoreRole), QByteArrayLiteral("core"));
    QCOMPARE(roles.value(NotificationsModel::ChannelRole), QByteArrayLiteral("channel"));
    QCOMPARE(roles.value(NotificationsModel::SeverityRole), QByteArrayLiteral("severity"));
}

void TestNotificationsModel::clearResetsModel() {
    NotificationsModel model;
    model.addNotification("WARNING", "core", "Channel 1", NotificationsModel::Warning);
    QCOMPARE(model.rowCount(), 1);

    model.clear();
    QCOMPARE(model.rowCount(), 0);
}

QTEST_GUILESS_MAIN(TestNotificationsModel)
#include "tst_notificationsmodel.moc"
