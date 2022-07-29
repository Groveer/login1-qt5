// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include "include/namespace.h"
#include "dlogin1manager.h"
#include <qobject.h>

class DBusInterface;
DLOGIN1_BEGIN_NAMESPACE

class DLogin1ManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLogin1ManagerPrivate(DLogin1Manager *parent = nullptr) : QObject(parent), q_ptr(parent) {}

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
    DLogin1Manager *q_ptr;
    Q_DECLARE_PUBLIC(DLogin1Manager)
};

DLOGIN1_END_NAMESPACE
