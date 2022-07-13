#include "login1_seat.h"

#include "dbusinterface.h"
#include "login1_seat_p.h"
#include <qobject.h>
#include <qdbuspendingreply.h>

LOGIN1_BEGIN_NAMESPACE
Login1Seat::Login1Seat(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1SeatPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    Q_D(Login1Seat);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

QList<SessionPath> Login1Seat::sessions()
{
    Q_D(Login1Seat);
    return qvariant_cast<QList<SessionPath>>(d->m_inter->property("Sessions"));
}

bool Login1Seat::canGraphical()
{
    Q_D(Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("CanGraphical"));
}

bool Login1Seat::canTTY()
{
    Q_D(Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("CanTTY"));
}

bool Login1Seat::idleHint()
{
    Q_D(Login1Seat);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

QString Login1Seat::id()
{
    Q_D(Login1Seat);
    return qvariant_cast<QString>(d->m_inter->property("Id"));
}

SessionPath Login1Seat::activeSession()
{
    Q_D(Login1Seat);
    return qvariant_cast<SessionPath>(d->m_inter->property("ActiveSession"));
}

quint64 Login1Seat::idleSinceHint()
{
    Q_D(Login1Seat);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 Login1Seat::idleSinceHintMonotonic()
{
    Q_D(Login1Seat);
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
