#include "login1_manager.h"
#include <qdbuspendingreply.h>
#include <qdbusextratypes.h>
#include <qdbusunixfiledescriptor.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qpair.h>
#include <qstringliteral.h>
#include <qvariant.h>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>

#include "dbusinterface.h"
#include "login1_types.h"

const QString &Service = QStringLiteral("org.freedesktop.login1");
const QString &Path = QStringLiteral("/org/freedesktop/login1");
const QString &Interface = QStringLiteral("org.freedesktop.login1.Manager");

LOGIN1_BEGIN_NAMESPACE

Login1Manager::Login1Manager(QObject *parent)
    : QObject(parent)
    , m_inter(new DBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this))
{
    ScheduledShutdownValue::registerMetaType();
    SessionProperty::registerMetaType();
    Inhibitor::registerMetaType();
    Seat::registerMetaType();
    Session::registerMetaType();
    User::registerMetaType();
}

Login1Manager::~Login1Manager() {}

// properties

QStringList Login1Manager::killExcludeUsers()
{
    return qvariant_cast<QStringList>(m_inter->property("killExcludeUsers"));
}

QStringList Login1Manager::killOnlyUsers()
{
    return qvariant_cast<QStringList>(m_inter->property("killOnlyUsers"));
}

bool Login1Manager::docked()
{
    return qvariant_cast<bool>(m_inter->property("Docked"));
}

bool Login1Manager::enableWallMessages()
{
    return qvariant_cast<bool>(m_inter->property("EnableWallMessages"));
}

void Login1Manager::setEnableWallMessages(const bool enable)
{
    m_inter->setProperty("EnableWallMessages", QVariant::fromValue(enable));
}

bool Login1Manager::ldleHint()
{
   return qvariant_cast<bool>(m_inter->property("LdleHint"));
}

bool Login1Manager::killUserProcesses()
{
    return qvariant_cast<bool>(m_inter->property("KillUserProcesses"));
}

bool Login1Manager::lidClosed()
{
    return qvariant_cast<bool>(m_inter->property("LidClosed"));
}

bool Login1Manager::onExternalPower()
{
    return qvariant_cast<bool>(m_inter->property("OnExternalPower"));
}

bool Login1Manager::preparingForShutdown()
{
    return qvariant_cast<bool>(m_inter->property("PreparingForShutdown"));
}

bool Login1Manager::preparingForSleep()
{
    return qvariant_cast<bool>(m_inter->property("PreparingForSleep"));
}

bool Login1Manager::rebootToFirmwareSetup()
{
    return qvariant_cast<bool>(m_inter->property("RebootToFirmwareSetup"));
}

bool Login1Manager::removeIPC()
{
    return qvariant_cast<bool>(m_inter->property("RemoveIPC"));
}

QString Login1Manager::blockInhibited()
{
    return qvariant_cast<QString>(m_inter->property("BlockInhibited"));
}

QString Login1Manager::delayInhibited()
{
    return qvariant_cast<QString>(m_inter->property("DelayInhibited"));
}

QString Login1Manager::handleHibernateKey()
{
    return qvariant_cast<QString>(m_inter->property("HandleHibernateKey"));
}

QString Login1Manager::handleLidSwitch()
{
    return qvariant_cast<QString>(m_inter->property("HandleLidSwitch"));
}

QString Login1Manager::handleLidSwitchDocked()
{
    return qvariant_cast<QString>(m_inter->property("HandleLidSwitchDocked"));
}

QString Login1Manager::handleLidSwitchExternalPower()
{
    return qvariant_cast<QString>(m_inter->property("HandleLidSwitchExternalPower"));
}

QString Login1Manager::handlePowerKey()
{
    return qvariant_cast<QString>(m_inter->property("HandlePowerKey"));
}

QString Login1Manager::handleSuspendKey()
{
    return qvariant_cast<QString>(m_inter->property("HandleSuspendKey"));
}

QString Login1Manager::ldleAction()
{
    return qvariant_cast<QString>(m_inter->property("LdleAction"));
}

QString Login1Manager::wallMessage()
{
    return qvariant_cast<QString>(m_inter->property("WallMessage"));
}

ScheduledShutdownValue Login1Manager::scheduledShutdown()
{
    return qvariant_cast<ScheduledShutdownValue>(m_inter->property("ScheduledShutdown"));
}

uint Login1Manager::nAutoVTs()
{
    return qvariant_cast<uint>(m_inter->property("NAutoVTs"));
}

quint64 Login1Manager::holdoffTimeoutUSec()
{
    return qvariant_cast<quint64>(m_inter->property("HoldoffTimeoutUSec"));
}

quint64 Login1Manager::ldleActionUSec()
{
    return qvariant_cast<quint64>(m_inter->property("LdleActionUSec"));
}

quint64 Login1Manager::ldleSinceHint()
{
    return qvariant_cast<quint64>(m_inter->property("LdleSinceHint"));
}

quint64 Login1Manager::ldleSinceHintMonotonic()
{
    return qvariant_cast<quint64>(m_inter->property("LdleSinceHintMonotonic"));
}

quint64 Login1Manager::inhibitDelayMaxUSec()
{
    return qvariant_cast<quint64>(m_inter->property("InhibitDelayMaxUSec"));
}

quint64 Login1Manager::inhibitorsMax()
{
    return qvariant_cast<quint64>(m_inter->property("inhibitorsMax"));
}

quint64 Login1Manager::nCurrentInhibitors()
{
    return qvariant_cast<quint64>(m_inter->property("NCurrentInhibitors"));
}

quint64 Login1Manager::nCurrentSessions()
{
    return qvariant_cast<quint64>(m_inter->property("NCurrentSessions"));
}

quint64 Login1Manager::runtimeDirectorySize()
{
    return qvariant_cast<quint64>(m_inter->property("RuntimeDirectorySize"));
}

quint64 Login1Manager::sessionMax()
{
    return qvariant_cast<quint64>(m_inter->property("SessionMax"));
}

quint64 Login1Manager::userStopDelayUSec()
{
    return qvariant_cast<quint64>(m_inter->property("UserStopDelayUSec"));
}

// public slots

void Login1Manager::activateSession(const QString &session_id)
{
    QVariantList args {QVariant::fromValue(session_id)};
    m_inter->asyncCallWithArgumentList("ActivateSession", args);
}

void Login1Manager::activateSessionOnSeat(const QString &session_id, const QString &seat_id)
{
    QVariantList args {QVariant::fromValue(session_id), QVariant::fromValue(seat_id)};
    m_inter->asyncCallWithArgumentList("ActivateSessionOnSeat", args);
}

void Login1Manager::attachDevice(const QString &seat_id, const QString &sysfs_path, const bool interactive)
{
    QVariantList args {QVariant::fromValue(seat_id), QVariant::fromValue(sysfs_path), QVariant::fromValue(interactive)};
    m_inter->asyncCallWithArgumentList("attachDevice", {seat_id, sysfs_path, interactive});
}

QString Login1Manager::canHalt()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanHalt"));
}

QString Login1Manager::canHibernate()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanHibernate"));
}

QString Login1Manager::canHybridSleep()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanHybridSleep"));
}

QString Login1Manager::canPowerOff()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanPowerOff"));
}

QString Login1Manager::canReboot()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanReboot"));
}

QString Login1Manager::canRebootParameter()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanRebootParameter"));
}

QString Login1Manager::canRebootToBootLoaderEntry()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanRebootToBootLoaderEntry"));
}

QString Login1Manager::canRebootToBootLoaderMenu()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanRebootToBootLoaderMenu"));
}

QString Login1Manager::canRebootToFirmwareSetup()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanRebootToFirmwareSetup"));
}

QString Login1Manager::canSuspend()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanSuspend"));
}

QString Login1Manager::canSuspendThenHibernate()
{
    return QDBusPendingReply<QString>(m_inter->asyncCall("CanSuspendThenHibernate"));
}

bool Login1Manager::cancelScheduledShutdown()
{
    return QDBusPendingReply<bool>(m_inter->asyncCall("CancelScheduledShutdown"));
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
    QVariantList args;
    args << QVariant::fromValue(uid) << QVariant::fromValue(pid) << QVariant::fromValue(service) << QVariant::fromValue(type)
        << QVariant::fromValue(_class) << QVariant::fromValue(desktop) << QVariant::fromValue(seat_id)
        << QVariant::fromValue(vtnr) << QVariant::fromValue(tty) << QVariant::fromValue(display) << QVariant::fromValue(remote)
        << QVariant::fromValue(remote_user) << QVariant::fromValue(remote_host) << QVariant::fromValue(properties);
    QDBusPendingReply<QString, QDBusObjectPath, QString, QDBusUnixFileDescriptor, uint, QString, uint, bool>
        replay = m_inter->asyncCallWithArgumentList(QStringLiteral("CreateSession"), args);
    replay.waitForFinished();
    return std::make_tuple(replay.argumentAt<0>(), replay.argumentAt<1>().path(), replay.argumentAt<2>(),
        replay.argumentAt<3>().fileDescriptor(), replay.argumentAt<4>(), replay.argumentAt<5>(), replay.argumentAt<6>(),
        replay.argumentAt<7>());
}

void Login1Manager::flushDevices(const bool value)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("flushDevices"), {QVariant::fromValue(value)});
}

QString Login1Manager::getSeat(const QString &seat_id)
{
    return QDBusPendingReply<QDBusObjectPath>(m_inter->asyncCallWithArgumentList(QStringLiteral("GetSeat"),
        {QVariant::fromValue(seat_id)})).argumentAt<0>().path();
}

QString Login1Manager::getSession(const QString &session_id)
{
    return QDBusPendingReply<QDBusObjectPath>(m_inter->asyncCallWithArgumentList(QStringLiteral("GetSession"),
        {QVariant::fromValue(session_id)})).argumentAt<0>().path();
}

QString Login1Manager::getSessionByPID(const uint pid)
{
    return QDBusPendingReply<QDBusObjectPath>(m_inter->asyncCallWithArgumentList(QStringLiteral("GetSessionByPID"),
        {QVariant::fromValue(pid)})).argumentAt<0>().path();
}

QString Login1Manager::getUser(const uint uid)
{
    return QDBusPendingReply<QDBusObjectPath>(m_inter->asyncCallWithArgumentList(QStringLiteral("GetUser"),
        {QVariant::fromValue(uid)})).argumentAt<0>().path();
}

QString Login1Manager::getUserByPID(const uint pid)
{
    return QDBusPendingReply<QDBusObjectPath>(m_inter->asyncCallWithArgumentList(QStringLiteral("GetUserByPID"),
        {QVariant::fromValue(pid)})).argumentAt<0>().path();
}

void Login1Manager::halt(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("Halt"), {QVariant::fromValue(interactive)});
}

void Login1Manager::hibernate(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("Hibernate"), {QVariant::fromValue(interactive)});
}

void Login1Manager::hybridSleep(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("HybridSleep"), {QVariant::fromValue(interactive)});
}

int Login1Manager::inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    return QDBusPendingReply<QDBusUnixFileDescriptor>(m_inter->asyncCallWithArgumentList(QStringLiteral("Inhibit"),
        {QVariant::fromValue(what), QVariant::fromValue(who), QVariant::fromValue(why), QVariant::fromValue(mode)}))
        .argumentAt<0>().fileDescriptor();
}

void Login1Manager::killSession(const QString &session_id, const QString &who, const int signal_number)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("KillSession"),
        {QVariant::fromValue(session_id), QVariant::fromValue(who), QVariant::fromValue(signal_number)});
}

void Login1Manager::killUser(const uint uid, const int signal_number)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("KillUser"),
        {QVariant::fromValue(uid), QVariant::fromValue(signal_number)});
}

QList<Inhibitor> Login1Manager::listInhibitors()
{
    return QDBusPendingReply<QList<Inhibitor>>(m_inter->asyncCall(QStringLiteral("ListInhibitors")));
}

QList<Seat> Login1Manager::listSeats()
{
    return QDBusPendingReply<QList<Seat>>(m_inter->asyncCall(QStringLiteral("ListSeats")));
}

QList<Session> Login1Manager::listSessions()
{
    return QDBusPendingReply<QList<Session>>(m_inter->asyncCall(QStringLiteral("ListSessions")));
}

QList<User> Login1Manager::listUsers()
{
    return QDBusPendingReply<QList<User>>(m_inter->asyncCall(QStringLiteral("ListUsers")));
}

void Login1Manager::lockSession(const QString &session_id)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("LockSession"), {QVariant::fromValue(session_id)});
}

void Login1Manager::lockSessions()
{
    m_inter->asyncCall(QStringLiteral("LockSessions"));
}

void Login1Manager::powerOff(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("PowerOff"), {QVariant::fromValue(interactive)});
}

void Login1Manager::reboot(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("Reboot"), {QVariant::fromValue(interactive)});
}

void Login1Manager::releaseSession(const QString &session_id)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseSession"), {QVariant::fromValue(session_id)});
}

void Login1Manager::scheduleShutdown(const QString type, qint64 usec)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("ScheduleShutdown"), {QVariant::fromValue(type), QVariant::fromValue(usec)});
}

void Login1Manager::setRebootTofirmwareSetup(const bool enable)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootTofirmwareSetup"), {QVariant::fromValue(enable)});
}

void Login1Manager::setUserLinger(const uint uid, const bool enable, const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("SetUserLinger"), {QVariant::fromValue(uid),
        QVariant::fromValue(enable), QVariant::fromValue(interactive)});
}

void Login1Manager::setWallMessage(const QString &message, const bool enable)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("SetWallMessage"), {QVariant::fromValue(message), QVariant::fromValue(enable)});
}

void Login1Manager::suspend(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("Suspend"), {QVariant::fromValue(interactive)});
}

void Login1Manager::suspendThenHibernate(const bool interactive)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("SuspendThenHibernate"), {QVariant::fromValue(interactive)});
}

void Login1Manager::terminateSeat(const QString &seat_id)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSeat"), {QVariant::fromValue(seat_id)});
}

void Login1Manager::terminateSession(const QString session_id)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSession"), {QVariant::fromValue(session_id)});
}

void Login1Manager::terminateUser(const uint uid)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateUser"), {QVariant::fromValue(uid)});
}

void Login1Manager::unlockSession(const QString &session_id)
{
    m_inter->asyncCallWithArgumentList(QStringLiteral("UnlockSession"), {QVariant::fromValue(session_id)});
}

void Login1Manager::unlockSessions()
{
    m_inter->asyncCall(QStringLiteral("UnlockSessions"));
}
LOGIN1_END_NAMESPACE
