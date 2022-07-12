#include "login1_manager.h"
#include <qdbuspendingreply.h>
#include <qdbusextratypes.h>
#include <qdbusunixfiledescriptor.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpair.h>
#include <qstringliteral.h>
#include <qvariant.h>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>

#include "dbusinterface.h"
#include "login1_types.h"
#include "src/login1_manager_p.h"

const QString &Service = QStringLiteral("org.freedesktop.login1");
const QString &Path = QStringLiteral("/org/freedesktop/login1");
const QString &Interface = QStringLiteral("org.freedesktop.login1.Manager");

LOGIN1_BEGIN_NAMESPACE

Login1Manager::Login1Manager(QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1ManagerPrivate(this)) 
{
    Q_D(Login1Manager);
    ScheduledShutdownValue::registerMetaType();
    SessionProperty::registerMetaType();
    Inhibitor::registerMetaType();
    Seat::registerMetaType();
    Session::registerMetaType();
    User::registerMetaType();
    d->m_inter = new DBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this);
}

Login1Manager::~Login1Manager() {}

// properties

QStringList Login1Manager::killExcludeUsers()
{
    Q_D(Login1Manager);
    return qvariant_cast<QStringList>(d->m_inter->property("killExcludeUsers"));
}

QStringList Login1Manager::killOnlyUsers()
{
    Q_D(Login1Manager);
    return qvariant_cast<QStringList>(d->m_inter->property("killOnlyUsers"));
}

bool Login1Manager::docked()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("Docked"));
}

bool Login1Manager::enableWallMessages()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("EnableWallMessages"));
}

void Login1Manager::setEnableWallMessages(const bool enable)
{
    Q_D(Login1Manager);
    d->m_inter->setProperty("EnableWallMessages", QVariant::fromValue(enable));
}

bool Login1Manager::ldleHint()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("LdleHint"));
}

bool Login1Manager::killUserProcesses()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("KillUserProcesses"));
}

bool Login1Manager::lidClosed()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("LidClosed"));
}

bool Login1Manager::onExternalPower()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("OnExternalPower"));
}

bool Login1Manager::preparingForShutdown()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("PreparingForShutdown"));
}

bool Login1Manager::preparingForSleep()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("PreparingForSleep"));
}

bool Login1Manager::rebootToFirmwareSetup()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("RebootToFirmwareSetup"));
}

bool Login1Manager::removeIPC()
{
    Q_D(Login1Manager);
    return qvariant_cast<bool>(d->m_inter->property("RemoveIPC"));
}

QString Login1Manager::blockInhibited()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("BlockInhibited"));
}

QString Login1Manager::delayInhibited()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("DelayInhibited"));
}

QString Login1Manager::handleHibernateKey()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandleHibernateKey"));
}

QString Login1Manager::handleLidSwitch()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandleLidSwitch"));
}

QString Login1Manager::handleLidSwitchDocked()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandleLidSwitchDocked"));
}

QString Login1Manager::handleLidSwitchExternalPower()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandleLidSwitchExternalPower"));
}

QString Login1Manager::handlePowerKey()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandlePowerKey"));
}

QString Login1Manager::handleSuspendKey()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("HandleSuspendKey"));
}

QString Login1Manager::ldleAction()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("LdleAction"));
}

QString Login1Manager::wallMessage()
{
    Q_D(Login1Manager);
    return qvariant_cast<QString>(d->m_inter->property("WallMessage"));
}

ScheduledShutdownValue Login1Manager::scheduledShutdown()
{
    Q_D(Login1Manager);
    return qvariant_cast<ScheduledShutdownValue>(d->m_inter->property("ScheduledShutdown"));
}

uint Login1Manager::nAutoVTs()
{
    Q_D(Login1Manager);
    return qvariant_cast<uint>(d->m_inter->property("NAutoVTs"));
}

quint64 Login1Manager::holdoffTimeoutUSec()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("HoldoffTimeoutUSec"));
}

quint64 Login1Manager::ldleActionUSec()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("LdleActionUSec"));
}

quint64 Login1Manager::ldleSinceHint()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("LdleSinceHint"));
}

quint64 Login1Manager::ldleSinceHintMonotonic()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("LdleSinceHintMonotonic"));
}

quint64 Login1Manager::inhibitDelayMaxUSec()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("InhibitDelayMaxUSec"));
}

quint64 Login1Manager::inhibitorsMax()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("inhibitorsMax"));
}

quint64 Login1Manager::nCurrentInhibitors()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("NCurrentInhibitors"));
}

quint64 Login1Manager::nCurrentSessions()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("NCurrentSessions"));
}

quint64 Login1Manager::runtimeDirectorySize()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("RuntimeDirectorySize"));
}

quint64 Login1Manager::sessionMax()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("SessionMax"));
}

quint64 Login1Manager::userStopDelayUSec()
{
    Q_D(Login1Manager);
    return qvariant_cast<quint64>(d->m_inter->property("UserStopDelayUSec"));
}

// public slots

QString Login1Manager::lastError()
{
    Q_D(Login1Manager);
    return d->m_errorMessage;    
}

void Login1Manager::activateSession(const QString &session_id)
{
    Q_D(Login1Manager);
    QVariantList args {QVariant::fromValue(session_id)};
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::activateSessionOnSeat(const QString &session_id, const QString &seat_id)
{
    Q_D(Login1Manager);
    QVariantList args {QVariant::fromValue(session_id), QVariant::fromValue(seat_id)};
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("ActivateSessionOnSeat", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::attachDevice(const QString &seat_id, const QString &sysfs_path, const bool interactive)
{
    Q_D(Login1Manager);
    QVariantList args {QVariant::fromValue(seat_id), QVariant::fromValue(sysfs_path), QVariant::fromValue(interactive)};
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("attachDevice", {seat_id, sysfs_path, interactive});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString Login1Manager::canHalt()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanHalt"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canHibernate()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanHibernate"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canHybridSleep()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanHybridSleep"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canPowerOff()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanPowerOff"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canReboot()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanReboot"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canRebootParameter()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanRebootParameter"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canRebootToBootLoaderEntry()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderEntry"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canRebootToBootLoaderMenu()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderMenu"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canRebootToFirmwareSetup()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanRebootToFirmwareSetup"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canSuspend()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanSuspend"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

QString Login1Manager::canSuspendThenHibernate()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QString> replay = d->m_inter->asyncCall(QStringLiteral("CanSuspendThenHibernate"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value();
}

bool Login1Manager::cancelScheduledShutdown()
{
    Q_D(Login1Manager);
    QDBusPendingReply<bool> replay = d->m_inter->asyncCall(QStringLiteral("CancelScheduledShutdown"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return false; 
    }
    return replay.value();
}

std::tuple<QString,     // session_id
    QString,        // path
    QString,        // runtime_path
    int,            // fifo_fd
    uint,           // uid
    QString,        // seat_id
    uint,           // vtnr
    bool            // existing
    > Login1Manager::createSession(uint uid, uint pid, const QString &service, const QString &type,
        const QString &_class, const QString &desktop, const QString &seat_id,
        uint vtnr, const QString &tty, const QString &display, const QString &remote,
        const QString &remote_user, const QString &remote_host, const QList<SessionProperty> &properties)
{
    Q_D(Login1Manager);
    QVariantList args;
    args << QVariant::fromValue(uid) << QVariant::fromValue(pid) << QVariant::fromValue(service) << QVariant::fromValue(type)
        << QVariant::fromValue(_class) << QVariant::fromValue(desktop) << QVariant::fromValue(seat_id)
        << QVariant::fromValue(vtnr) << QVariant::fromValue(tty) << QVariant::fromValue(display) << QVariant::fromValue(remote)
        << QVariant::fromValue(remote_user) << QVariant::fromValue(remote_host) << QVariant::fromValue(properties);
    QDBusPendingReply<QString, QDBusObjectPath, QString, QDBusUnixFileDescriptor, uint, QString, uint, bool>
        replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("CreateSession"), args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return std::tuple<QString, QString, QString, int, uint, QString, uint, bool>(); 
    }
    return std::make_tuple(replay.argumentAt<0>(), replay.argumentAt<1>().path(), replay.argumentAt<2>(),
        replay.argumentAt<3>().fileDescriptor(), replay.argumentAt<4>(), replay.argumentAt<5>(), replay.argumentAt<6>(),
        replay.argumentAt<7>());
}

void Login1Manager::flushDevices(const bool value)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("flushDevices"), {QVariant::fromValue(value)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString Login1Manager::getSeat(const QString &seat_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusObjectPath> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSeat"),
        {QVariant::fromValue(seat_id)});
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value().path();
}

QString Login1Manager::getSession(const QString &session_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusObjectPath> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSession"),
        {QVariant::fromValue(session_id)});
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value().path();
}

QString Login1Manager::getSessionByPID(const uint pid)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusObjectPath> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSessionByPID"),
        {QVariant::fromValue(pid)});
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value().path();
}

QString Login1Manager::getUser(const uint uid)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusObjectPath> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetUser"),
        {QVariant::fromValue(uid)});
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value().path();
}

QString Login1Manager::getUserByPID(const uint pid)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusObjectPath> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetUserByPID"),
        {QVariant::fromValue(pid)});
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return replay.value().path();
}

void Login1Manager::halt(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("Halt", {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::hibernate(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("Hibernate", {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::hybridSleep(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("HybridSleep", {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

int Login1Manager::inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    Q_D(Login1Manager);
    QDBusPendingReply<QDBusUnixFileDescriptor> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Inhibit"),
        {QVariant::fromValue(what), QVariant::fromValue(who), QVariant::fromValue(why), QVariant::fromValue(mode)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return -1;
    }
    return replay.value().fileDescriptor();
}

void Login1Manager::killSession(const QString &session_id, const QString &who, const int signal_number)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList("KillSession",
        {QVariant::fromValue(session_id), QVariant::fromValue(who), QVariant::fromValue(signal_number)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::killUser(const uint uid, const int signal_number)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("KillUser"),
        {QVariant::fromValue(uid), QVariant::fromValue(signal_number)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QList<Inhibitor> Login1Manager::listInhibitors()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QList<Inhibitor>> replay = d->m_inter->asyncCall(QStringLiteral("ListInhibitors"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QList<Inhibitor>();
    }
    return replay.value();
}

QList<Seat> Login1Manager::listSeats()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QList<Seat>> replay = d->m_inter->asyncCall(QStringLiteral("ListSeats"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QList<Seat>();
    }
    return replay.value();
}

QList<Session> Login1Manager::listSessions()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QList<Session>> replay = d->m_inter->asyncCall(QStringLiteral("ListSessions"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QList<Session>();
    }
    return replay.value();
}

QList<User> Login1Manager::listUsers()
{
    Q_D(Login1Manager);
    QDBusPendingReply<QList<User>> replay = d->m_inter->asyncCall(QStringLiteral("ListUsers"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QList<User>();
    }
    return replay.value();
}

void Login1Manager::lockSession(const QString &session_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("LockSession"),
        {QVariant::fromValue(session_id)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::lockSessions()
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("LockSessions"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::powerOff(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("PowerOff"),
        {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::reboot(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Reboot"),
        {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::releaseSession(const QString &session_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseSession"),
        {QVariant::fromValue(session_id)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::scheduleShutdown(const QString type, qint64 usec)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ScheduleShutdown"),
        {QVariant::fromValue(type), QVariant::fromValue(usec)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::setRebootTofirmwareSetup(const bool enable)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootTofirmwareSetup"),
        {QVariant::fromValue(enable)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::setUserLinger(const uint uid, const bool enable, const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetUserLinger"),
        {QVariant::fromValue(uid), QVariant::fromValue(enable), QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::setWallMessage(const QString &message, const bool enable)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetWallMessage"),
        {QVariant::fromValue(message), QVariant::fromValue(enable)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::suspend(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Suspend"),
        {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::suspendThenHibernate(const bool interactive)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SuspendThenHibernate"),
        {QVariant::fromValue(interactive)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::terminateSeat(const QString &seat_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSeat"),
        {QVariant::fromValue(seat_id)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::terminateSession(const QString session_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSession"),
        {QVariant::fromValue(session_id)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::terminateUser(const uint uid)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateUser"),
        {QVariant::fromValue(uid)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::unlockSession(const QString &session_id)
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCallWithArgumentList(QStringLiteral("UnlockSession"),
        {QVariant::fromValue(session_id)});
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void Login1Manager::unlockSessions()
{
    Q_D(Login1Manager);
    QDBusPendingReply<> replay = d->m_inter->asyncCall(QStringLiteral("UnlockSessions"));
    replay.waitForFinished();
    if (!replay.isValid()) {
        d->m_errorMessage = replay.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
LOGIN1_END_NAMESPACE
