#include "NotificationsModel.h"

NotificationsModel::NotificationsModel(QObject *parent)
    : QAbstractListModel(parent) {
}

void NotificationsModel::addNotification(const QString &label, const QString &core,
                                        const QString &channel, Severity severity) {
    beginInsertRows({}, 0, 0);
    m_notifications.prepend({label, core, channel, severity});
    endInsertRows();
}

void NotificationsModel::clear() {
    beginResetModel();
    m_notifications.clear();
    endResetModel();
}

int NotificationsModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_notifications.size();
}

QVariant NotificationsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_notifications.size())
        return {};
    const Entry &entry = m_notifications.at(index.row());
    switch (role) {
    case LabelRole:    return entry.label;
    case CoreRole:     return entry.core;
    case ChannelRole:  return entry.channel;
    case SeverityRole: return entry.severity;
    default:           return {};
    }
}


QHash<int, QByteArray> NotificationsModel::roleNames() const {
    return {
        {LabelRole, "label"},
        {CoreRole, "core"},
        {ChannelRole, "channel"},
        {SeverityRole, "severity"},
    };
}
