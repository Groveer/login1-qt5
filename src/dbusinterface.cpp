/*
 * Copyright (C) 2021 ~ 2023 Deepin Technology Co., Ltd.
 *
 * Author:     caixiangrong <caixiangrong@uniontech.com>
 *
 * Maintainer: caixiangrong <caixiangrong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dbusinterface.h"
#include "dbusinterface_p.h"

#include <QMetaObject>
#include <qmetaobject.h>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusPendingReply>
#include <QDebug>

const QString &FreedesktopService = QStringLiteral("org.freedesktop.DBus");
const QString &FreedesktopPath = QStringLiteral("/org/freedesktop/DBus");
const QString &FreedesktopInterface = QStringLiteral("org.freedesktop.DBus");
const QString &NameOwnerChanged = QStringLiteral("NameOwnerChanged");

const QString &PropertiesInterface = QStringLiteral("org.freedesktop.DBus.Properties");
const QString &PropertiesChanged = QStringLiteral("PropertiesChanged");
const char *PropertyName = "propname";

DBusInterfacePrivate::DBusInterfacePrivate(DBusInterface *interface, QObject *parent)
    : QObject(interface)
    , m_parent(parent)
    , m_serviceValid(false)
    , q_ptr(interface)
{
    QDBusMessage message = QDBusMessage::createMethodCall(FreedesktopService, FreedesktopPath, FreedesktopInterface, "NameHasOwner");
    message << interface->service();
    interface->connection().callWithCallback(message, this, SLOT(onDBusNameHasOwner(bool)));

    QStringList argumentMatch;
    argumentMatch << interface->interface();
    interface->connection().connect(interface->service(), interface->path(), PropertiesInterface, PropertiesChanged, argumentMatch, QString(), this, SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));
}

QVariant DBusInterfacePrivate::updateProp(const char *propname, const QVariant &value)
{
    const QMetaObject *metaObj = m_parent->metaObject();
    const char *signalName = propname + QStringLiteral("Changed").toLatin1();
    int i = metaObj->indexOfSignal(signalName);
    if (i != -1) {
        m_propertyMap.insert(propname, value);
        QMetaObject::invokeMethod(m_parent, signalName, Qt::DirectConnection, QGenericArgument(value.typeName(), value.data()));
    } else
        qWarning() << "invalid property changed:" << propname << value;

    return value;
}

void DBusInterfacePrivate::initDBusConnection()
{
    Q_Q(DBusInterface);
    QDBusConnection connection = q->connection();
    QStringList signalList;
    QDBusInterface inter(q->service(), q->path(), q->interface(), connection);
    const QMetaObject *meta = inter.metaObject();
    for (int i = meta->methodOffset(); i < meta->methodCount(); ++i) {
        const QMetaMethod &method = meta->method(i);
        if (method.methodType() == QMetaMethod::Signal) {
            signalList << method.methodSignature();
        }
    }
    const QMetaObject *parentMeta = m_parent->metaObject();
    for (const QString &signal : signalList) {
        int i = parentMeta->indexOfSignal(QMetaObject::normalizedSignature(signal.toLatin1()));
        if (i != -1) {
            const QMetaMethod &parentMethod = parentMeta->method(i);
            connection.connect(q->service(), q->path(), q->interface(), parentMethod.name(), m_parent, QT_STRINGIFY(QSIGNAL_CODE) + parentMethod.methodSignature());
        }
    }
}

void DBusInterfacePrivate::onPropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(interfaceName)
    Q_UNUSED(invalidatedProperties)
    for (QVariantMap::const_iterator it = changedProperties.cbegin(); it != changedProperties.cend(); ++it)
        updateProp((it.key() + m_suffix).toLatin1(), it.value());
}

void DBusInterfacePrivate::onAsyncPropertyFinished(QDBusPendingCallWatcher *w)
{
    QDBusPendingReply<QVariant> reply = *w;
    if (!reply.isError()) {
        updateProp(w->property(PropertyName).toString().toLatin1(), reply.value());
    }
    w->deleteLater();
}

void DBusInterfacePrivate::setServiceValid(bool valid)
{
    if (m_serviceValid != valid) {
        Q_Q(DBusInterface);
        m_serviceValid = valid;
        Q_EMIT q->serviceValidChanged(m_serviceValid);
    }
}

void DBusInterfacePrivate::onDBusNameHasOwner(bool valid)
{
    Q_Q(DBusInterface);
    setServiceValid(valid);
    if (valid)
        initDBusConnection();
    else
        q->connection().connect(FreedesktopService, FreedesktopPath, FreedesktopInterface, NameOwnerChanged, this, SLOT(onDBusNameOwnerChanged(QString, QString, QString)));
}

void DBusInterfacePrivate::onDBusNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOWner)
{
    Q_Q(DBusInterface);
    if (name == q->service() && oldOwner.isEmpty()) {
        initDBusConnection();
        q->connection().disconnect(FreedesktopService, FreedesktopPath, FreedesktopInterface, NameOwnerChanged, this, SLOT(onDBusNameOwnerChanged(QString, QString, QString)));
        setServiceValid(true);
    } else if (name == q->service() && newOWner.isEmpty())
        setServiceValid(false);
}
//////////////////////////////////////////////////////////
DBusInterface::DBusInterface(const QString &service, const QString &path, const QString &interface, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, interface.toLatin1(), connection, parent)
    , d_ptr(new DBusInterfacePrivate(this, parent))
{
}

DBusInterface::~DBusInterface()
{
}

bool DBusInterface::serviceValid() const
{
    Q_D(const DBusInterface);
    return d->m_serviceValid;
}

QString DBusInterface::suffix() const
{
    Q_D(const DBusInterface);
    return d->m_suffix;
}

void DBusInterface::setSuffix(const QString &suffix)
{
    Q_D(DBusInterface);
    d->m_suffix = suffix;
}

inline QString originalPropname(const char *propname, QString suffix)
{
    QString propStr(propname);
    return propStr.left(propStr.length() - suffix.length());
}

QVariant DBusInterface::property(const char *propname)
{
    Q_D(DBusInterface);
    if (d->m_propertyMap.contains(propname))
        return d->m_propertyMap.value(propname);

    QDBusMessage msg = QDBusMessage::createMethodCall(service(), path(), PropertiesInterface, QStringLiteral("Get"));
    msg << interface() << originalPropname(propname, d->m_suffix);
    QDBusPendingReply<QVariant> prop = connection().asyncCall(msg);
    if (prop.value().isValid())
        return d->updateProp(propname, prop.value());

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(prop, this);
    watcher->setProperty(PropertyName, propname);
    connect(watcher, &QDBusPendingCallWatcher::finished, d, &DBusInterfacePrivate::onAsyncPropertyFinished);
    if (d->m_propertyMap.contains(propname))
        return d->m_propertyMap.value(propname);

    return QVariant();
}

void DBusInterface::setProperty(const char *propname, const QVariant &value)
{
    Q_D(const DBusInterface);
    QDBusMessage msg = QDBusMessage::createMethodCall(service(), path(), PropertiesInterface, QStringLiteral("Set"));
    msg << interface() << originalPropname(propname, d->m_suffix) << value;
    connection().asyncCall(msg);
}
