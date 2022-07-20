#include "login1_seat.h"

#include "dbusinterface.h"
#include "login1_seat_p.h"
#include "login1_types.h"
#include "src/login1_types_p.h"
#include <qlist.h>
#include <qobject.h>
#include <qdbuspendingreply.h>

LOGIN1_BEGIN_NAMESPACE
Login1Seat::Login1Seat(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1SeatPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    SessionPath_p::registerMetaType();
    Q_D(Login1Seat);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

QList<SessionPath> Login1Seat::sessions() const
{
    Q_D(const Login1Seat);
    const auto &result = qvariant_cast<QList<SessionPath_p>>(d->m_inter->property("Sessions"));
    QList<SessionPath> sessionPaths;
    for (auto sessionPath_p : result) {
        SessionPath sessionPath;
        sessionPath.path = sessionPath_p.path.path();
        sessionPath.session_id =sessionPath_p.session_id;
        sessionPaths.append(sessionPath);
    }
    return sessionPaths;
}

bool Login1Seat::canGraphical() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("CanGraphical"));
}

bool Login1Seat::canTTY() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("CanTTY"));
}

bool Login1Seat::idleHint() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

QString Login1Seat::id() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<QString>(d->m_inter->property("Id"));
}

QString Login1Seat::lastError() const
{
    Q_D(const Login1Seat);
    return d->m_errorMessage;
}

SessionPath Login1Seat::activeSession() const
{
    Q_D(const Login1Seat);
    const auto & result = qvariant_cast<SessionPath_p>(d->m_inter->property("ActiveSession"));
    SessionPath path;
    path.path = result.path.path();
    path.session_id = result.session_id;
    return path;
}

quint64 Login1Seat::idleSinceHint() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 Login1Seat::idleSinceHintMonotonic() const
{
    Q_D(const Login1Seat);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

void Login1Seat::activateSession(const QString &session_id)
{
    Q_D(Login1Seat);
    QVariantList args {QVariant::fromValue(session_id)};
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Seat::switchTo(const uint vtnr)
{
    Q_D(Login1Seat);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SwitchTo"),
        {QVariant::fromValue(vtnr)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Seat::switchToNext()
{
    Q_D(Login1Seat);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("SwitchToNext"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Seat::switchToPrevious()
{
    Q_D(Login1Seat);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("SwitchToPrevious"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Seat::terminate()
{
    Q_D(Login1Seat);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

Login1Seat::~Login1Seat() {}
LOGIN1_END_NAMESPACE
