#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QtQml/qqmlregistration.h>

class NotificationsModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT

public:
    enum Severity { Warning, Danger };
    Q_ENUM(Severity)

    enum Roles {
        LabelRole = Qt::UserRole,
        CoreRole,
        ChannelRole,
        SeverityRole
    };

    explicit NotificationsModel(QObject *parent = nullptr);

    void addNotification(const QString &label, const QString &core, const QString &channel, Severity severity);
    void clear();

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    struct Entry {
        QString label;
        QString core;
        QString channel;
        Severity severity;
    };

    QList<Entry> m_notifications;
};
