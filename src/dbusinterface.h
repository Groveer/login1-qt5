// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once
#include <QDBusAbstractInterface>

class DBusInterfacePrivate;

class DBusInterface : public QDBusAbstractInterface
{
    Q_OBJECT

public:
    explicit DBusInterface(const QString &service, const QString &path, const QString &interface = QString(),
                              const QDBusConnection &connection = QDBusConnection::sessionBus(), QObject *parent = nullptr);
    virtual ~DBusInterface() override;

    bool serviceValid() const;
    QString suffix() const;
    void setSuffix(const QString &suffix);

    QVariant property(const char *propname);
    void setProperty(const char *propname, const QVariant &value);

Q_SIGNALS:
    void serviceValidChanged(const bool valid) const;

private:
    QScopedPointer<DBusInterfacePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DBusInterface)
    Q_DISABLE_COPY(DBusInterface)
};

