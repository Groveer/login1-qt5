#include "login1_user.h"

#include "dbusinterface.h"
#include "login1_types.h"
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

    SessionPath::registerMetaType();

    Q_D(Login1User);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

Login1User::~Login1User() {}

QList<SessionPath> Login1User::sessions() const
{
    Q_D(const Login1User);
    return qvariant_cast<QList<SessionPath>>(d->m_inter->property("Sessions"));
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
    return qvariant_cast<SessionPath>(d->m_inter->property("Display"));
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

QString Login1User::lastError()
{
    Q_D(Login1User);
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
