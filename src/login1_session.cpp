#include "login1_session.h"

#include "dbusinterface.h"
#include "login1_session_p.h"
#include "src/login1_types_p.h"
#include <QDBusError>
#include <qdbuspendingreply.h>
#include <qdbusunixfiledescriptor.h>
#include <qobject.h>
#include <qvariant.h>
LOGIN1_BEGIN_NAMESPACE

Login1Session::Login1Session(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1SessionPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Session");

    Q_D(Login1Session);
    SeatPath_p::registerMetaType();
    UserPath_p::registerMetaType();
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

Login1Session::~Login1Session(){};

bool Login1Session::active() const
{
    Q_D(const Login1Session);
    return qvariant_cast<bool>(d->m_inter->property("Active"));
}

bool Login1Session::idleHint() const
{
    Q_D(const Login1Session);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

bool Login1Session::lockedHint() const
{
    Q_D(const Login1Session);
    return qvariant_cast<bool>(d->m_inter->property("LockedHint"));
}

bool Login1Session::remote() const
{
    Q_D(const Login1Session);
    return qvariant_cast<bool>(d->m_inter->property("Remote"));
}
QString Login1Session::_class() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Class"));
}
QString Login1Session::desktop() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Desktop"));
}
QString Login1Session::display() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Display"));
}
QString Login1Session::id() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Id"));
}
QString Login1Session::name() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Name"));
}

QString Login1Session::remoteHost() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("RemoteHost"));
}
QString Login1Session::remoteUser() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("RemoteUser"));
}

QString Login1Session::scope() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Scope"));
}

QString Login1Session::service() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Service"));
}

QString Login1Session::state() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("State"));
}

QString Login1Session::tty() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("TTY"));
}

QString Login1Session::type() const
{
    Q_D(const Login1Session);
    return qvariant_cast<QString>(d->m_inter->property("Type"));
}

SeatPath Login1Session::seat() const
{
    Q_D(const Login1Session);
    const auto &result = qvariant_cast<SeatPath_p>(d->m_inter->property("Seat"));
    SeatPath seatPath;
    seatPath.path = result.path.path();
    seatPath.seat_id = result.seat_id;
    return seatPath;
}
UserPath Login1Session::user() const
{
    Q_D(const Login1Session);
    const auto &result = qvariant_cast<UserPath_p>(d->m_inter->property("User"));
    UserPath userPath;
    userPath.path = result.path.path();
    userPath.user_id = result.user_id;
    return userPath;
}

uint Login1Session::audit() const
{
    Q_D(const Login1Session);
    return qvariant_cast<uint>(d->m_inter->property("Audit"));
}

uint Login1Session::leader() const
{
    Q_D(const Login1Session);
    return qvariant_cast<uint>(d->m_inter->property("Leader"));
}
uint Login1Session::vtnr() const
{
    Q_D(const Login1Session);
    return qvariant_cast<uint>(d->m_inter->property("VTNr"));
}

quint64 Login1Session::idleSinceHint() const
{
    Q_D(const Login1Session);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 Login1Session::idleSinceHintMonotonic() const
{
    Q_D(const Login1Session);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 Login1Session::timestamp() const
{
    Q_D(const Login1Session);
    return qvariant_cast<quint64>(d->m_inter->property("Timestamp"));
}
quint64 Login1Session::timestampMonotonic() const
{
    Q_D(const Login1Session);
    return qvariant_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

void Login1Session::activate()
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("Activate"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Session::kill(const QString who, const uint signal_number)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Kill"),
                                                                       {
                                                                           QVariant::fromValue(who),
                                                                           QVariant::fromValue(signal_number),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::lock()
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("Lock"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::pauseDeviceComplete(const uint major, const uint minor)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("pauseDeviceComplete"),
                                                                       {
                                                                           QVariant::fromValue(major),
                                                                           QVariant::fromValue(minor),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::releaseControl()
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("ReleaseControl"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::releaseDevice(const uint major, const uint minor)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseDevice"),
                                                                       {
                                                                           QVariant::fromValue(major),
                                                                           QVariant::fromValue(minor),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Session::setBrightness(const QString &subsystem, const QString &name, const uint brightness)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetBrightness"),
                                                                       {
                                                                           QVariant::fromValue(subsystem),
                                                                           QVariant::fromValue(name),
                                                                           QVariant::fromValue(brightness),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Session::setIdleHint(const bool idle)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetIdleHint"),
                                                                       {
                                                                           QVariant::fromValue(idle),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::setLockedHint(const bool locked)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetLockedHint"),
                                                                       {
                                                                           QVariant::fromValue(locked),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Session::setType(const QString &type)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetType"),
                                                                       {
                                                                           QVariant::fromValue(type),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Session::takeControl(const bool force)
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TakeControl"),
                                                                       {
                                                                           QVariant::fromValue(force),
                                                                       });
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

std::tuple<int,  // fd
           bool  // inactive
           >
Login1Session::takeDevice(uint manjor, uint minor)
{
    Q_D(Login1Session);
    QDBusPendingReply<QDBusUnixFileDescriptor, bool> replay = d->m_inter->asyncCallWithArgumentList(
        QStringLiteral("TakeDevice"), {QVariant::fromValue(manjor), QVariant::fromValue(minor)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return std::tuple<int, bool>();
    }
    return std::make_tuple<int, bool>(replay.argumentAt<0>().fileDescriptor(), replay.argumentAt<1>());
}
void Login1Session::terminate()
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void Login1Session::unlock()
{
    Q_D(Login1Session);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("Unlock"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
LOGIN1_END_NAMESPACE
