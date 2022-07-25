// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once
#include "dbusinterface.h"

class QDBusPendingCallWatcher;

class DBusInterfacePrivate : public QObject
{
    Q_OBJECT

public:
    explicit DBusInterfacePrivate(DBusInterface *interface, QObject *parent);
    QVariant updateProp(const char *propname, const QVariant &value);
    void initDBusConnection();
    void setServiceValid(bool valid);

private Q_SLOTS:
    void onPropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);
    void onAsyncPropertyFinished(QDBusPendingCallWatcher *w);
    void onDBusNameHasOwner(bool valid);
    void onDBusNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOWner);

public:
    QObject *m_parent;
    QString m_suffix;
    QVariantMap m_propertyMap;
    bool m_serviceValid;

    DBusInterface *q_ptr;
    Q_DECLARE_PUBLIC(DBusInterface)
};

