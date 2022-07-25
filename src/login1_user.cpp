// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#include "login1_user.h"

#include "dbusinterface.h"
#include "login1_types.h"
#include "login1_types_p.h"
#include "login1_user_p.h"
#include <qlist.h>
#include <qobject.h>
#include <qdbuspendingreply.h>

LOGIN1_BEGIN_NAMESPACE
Login1User::Login1User(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1UserPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    SessionPath_p::registerMetaType();

    Q_D(Login1User);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

Login1User::~Login1User() {}

QList<SessionPath> Login1User::sessions() const
{
    Q_D(const Login1User);
    const auto &result = qvariant_cast<QList<SessionPath_p>>(d->m_inter->property("Sessions"));
    QList<SessionPath> sessions;
    for (auto && session_p : result) {
        SessionPath session;
        session.session_id = session_p.session_id;
        session.path =session_p.path.path();
        sessions.append(session);
    }
    return sessions;
}

bool Login1User::idleHint() const
{
    Q_D(const Login1User);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

bool Login1User::linger() const
{
    Q_D(const Login1User);
    return qvariant_cast<bool>(d->m_inter->property("Linger"));
}

QString Login1User::name() const
{
    Q_D(const Login1User);
    return qvariant_cast<QString>(d->m_inter->property("Name"));
}

QString Login1User::runtimePath() const
{
    Q_D(const Login1User);
    return qvariant_cast<QString>(d->m_inter->property("RuntimePath"));
}

QString Login1User::service() const
{
    Q_D(const Login1User);
    return qvariant_cast<QString>(d->m_inter->property("Service"));
}

QString Login1User::slice() const
{
    Q_D(const Login1User);
    return qvariant_cast<QString>(d->m_inter->property("Slice"));
}

QString Login1User::state() const
{
    Q_D(const Login1User);
    return qvariant_cast<QString>(d->m_inter->property("State"));
}

SessionPath Login1User::display() const
{
    Q_D(const Login1User);
    const auto &result = qvariant_cast<SessionPath_p>(d->m_inter->property("Display"));
    SessionPath session;
    session.path = result.path.path();
    session.session_id = result.session_id;
    return session;
}

uint Login1User::GID() const
{
    Q_D(const Login1User);
    return qvariant_cast<uint>(d->m_inter->property("GID"));
}

uint Login1User::UID() const
{
    Q_D(const Login1User);
    return qvariant_cast<uint>(d->m_inter->property("UID"));
}

quint64 Login1User::idleSinceHint() const
{
    Q_D(const Login1User);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 Login1User::idleSinceHintMonotonic() const
{
    Q_D(const Login1User);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 Login1User::timestamp() const
{
    Q_D(const Login1User);
    return qvariant_cast<quint64>(d->m_inter->property("Timestamp"));
}

quint64 Login1User::timestampMonotonic() const
{
    Q_D(const Login1User);
    return qvariant_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

// public slots

QString Login1User::lastError() const
{
    Q_D(const Login1User);
    return d->m_errorMessage;
}

void Login1User::kill(const int signal_number)
{
    Q_D(Login1User);
    QVariantList args {QVariant::fromValue(signal_number)};
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("Kill", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1User::terminate()
{
    Q_D(Login1User);
    QDBusPendingReply<> replay = d->m_inter->asyncCall("Terminate");
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

LOGIN1_END_NAMESPACE
