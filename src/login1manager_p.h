// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include "include/namespace.h"
#include "login1manager.h"
#include <qobject.h>

class DBusInterface;
LOGIN1_BEGIN_NAMESPACE

class Login1ManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit Login1ManagerPrivate(Login1Manager *parent = nullptr) : QObject(parent), q_ptr(parent) {}

signals:
    // private signals
    void PrepareForShutdown(const bool value);
    void PrepareForSleep(const bool value);
    void SeatNew(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SeatRemoved(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SessionNew(const QString &session_id, const QDBusObjectPath &session_path);
    void SessionRemoved(const QString &session_id, const QDBusObjectPath &session_path);
    void UserNew(const uint uid, const QDBusObjectPath &path);
    void UserRemoved(const uint uid, const QDBusObjectPath &path);

public:
    QString m_errorMessage;
    DBusInterface *m_inter;
    Login1Manager *q_ptr;
    Q_DECLARE_PUBLIC(Login1Manager)
};

LOGIN1_END_NAMESPACE
