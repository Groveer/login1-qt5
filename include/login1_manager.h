#pragma once

#include <qobject.h>

#include <qscopedpointer.h>
#include <tuple>

#include "namespace.h"
#include "login1_types.h"
#include "src/login1_types_p.h"

LOGIN1_BEGIN_NAMESPACE

class Login1ManagerPrivate;

class Login1Manager : public QObject
{
    Q_OBJECT
public:
    explicit Login1Manager(QObject *parent = nullptr);
    virtual ~Login1Manager();

    Q_PROPERTY(QStringList KillExcludeUsers READ killExcludeUsers NOTIFY KillExcludeUsersChanged)
    Q_PROPERTY(QStringList KillOnlyUsers READ killOnlyUsers NOTIFY KillOnlyUsersChanged)
    Q_PROPERTY(bool Docked READ docked NOTIFY DockedChanged)
    Q_PROPERTY(bool EnableWallMessages READ enableWallMessages WRITE setEnableWallMessages NOTIFY EnableWallMessagesChanged);
    Q_PROPERTY(bool LdleHint READ ldleHint NOTIFY LdleHintChanged);
    Q_PROPERTY(bool KillUserProcesses READ killUserProcesses NOTIFY KillUserProcessesChanged);
    Q_PROPERTY(bool LidClosed READ lidClosed NOTIFY LidClosedChanged);
    Q_PROPERTY(bool OnExternalPower READ onExternalPower NOTIFY OnExternalPowerChanged);
    Q_PROPERTY(bool PreparingForShutdown READ preparingForShutdown NOTIFY PreparingForShutdownChanged);
    Q_PROPERTY(bool PreparingForSleep READ preparingForSleep NOTIFY PreparingForSleepChanged);
    Q_PROPERTY(bool RebootToFirmwareSetup READ rebootToFirmwareSetup NOTIFY RebootToFirmwareSetupChanged);
    Q_PROPERTY(bool RemoveIPC READ removeIPC NOTIFY RemoveIPCChanged);
    Q_PROPERTY(QString BlockInhibited READ blockInhibited NOTIFY BlockInhibitedChanged);
    Q_PROPERTY(QString DelayInhibited READ delayInhibited NOTIFY DelayInhibitedChanged);
    Q_PROPERTY(QString HandleHibernateKey READ handleHibernateKey NOTIFY HandleHibernateKeyChanged);
    Q_PROPERTY(QString HandleLidSwitch READ handleLidSwitch NOTIFY HandleLidSwitchChanged);
    Q_PROPERTY(QString HandleLidSwitchDocked READ handleLidSwitchDocked NOTIFY HandleLidSwitchDockedChanged);
    Q_PROPERTY(QString HandleLidSwitchExternalPower READ handleLidSwitchExternalPower NOTIFY HandleLidSwitchExternalPowerChanged);
    Q_PROPERTY(QString HandlePowerKey READ handlePowerKey NOTIFY HandlePowerKeyChanged);
    Q_PROPERTY(QString HandleSuspendKey READ handleSuspendKey NOTIFY HandleSuspendKeyChanged);
    Q_PROPERTY(QString LdleAction READ ldleAction NOTIFY LdleActionChanged);
    Q_PROPERTY(QString WallMessage READ wallMessage WRITE setWallMessage NOTIFY WallMessageChanged);
    Q_PROPERTY(ScheduledShutdownValue ScheduledShutdown READ scheduledShutdown NOTIFY ScheduledShutdownChanged);
    Q_PROPERTY(uint NAutoVTs READ nAutoVTs NOTIFY NAutoVTsChanged);
    Q_PROPERTY(quint64 HoldoffTimeoutUSec READ holdoffTimeoutUSec NOTIFY HoldoffTimeoutUSecChanged);
    Q_PROPERTY(quint64 LdleActionUSec READ ldleActionUSec NOTIFY LdleActionUSecChanged);
    Q_PROPERTY(quint64 LdleSinceHint READ ldleSinceHint NOTIFY LdleSinceHintChanged);
    Q_PROPERTY(quint64 LdleSinceHintMonotonic READ ldleSinceHintMonotonic NOTIFY LdleSinceHintMonotonicChanged);
    Q_PROPERTY(quint64 InhibitDelayMaxUSec READ inhibitDelayMaxUSec NOTIFY InhibitDelayMaxUSecChanged);
    Q_PROPERTY(quint64 InhibitorsMax READ inhibitorsMax NOTIFY InhibitorsMaxChanged);
    Q_PROPERTY(quint64 NCurrentInhibitors READ nCurrentInhibitors NOTIFY NCurrentInhibitorsChanged);
    Q_PROPERTY(quint64 NCurrentSessions READ nCurrentSessions NOTIFY NCurrentSessionsChanged);
    Q_PROPERTY(quint64 RuntimeDirectorySize READ runtimeDirectorySize NOTIFY RuntimeDirectorySizeChanged);
    Q_PROPERTY(quint64 SessionMax READ sessionMax NOTIFY SessionMaxChanged);
    Q_PROPERTY(quint64 UserStopDelayUSec READ userStopDelayUSec NOTIFY UserStopDelayUSecChanged);

    QStringList killExcludeUsers() const;
    QStringList killOnlyUsers() const;
    bool docked() const;
    bool enableWallMessages() const;
    void setEnableWallMessages(const bool enable);
    bool ldleHint() const;
    bool killUserProcesses() const;
    bool lidClosed() const;
    bool onExternalPower() const;
    bool preparingForShutdown() const;
    bool preparingForSleep() const;
    bool rebootToFirmwareSetup() const;
    bool removeIPC() const;
    QString blockInhibited() const;
    QString delayInhibited() const;
    QString handleHibernateKey() const;
    QString handleLidSwitch() const;
    QString handleLidSwitchDocked() const;
    QString handleLidSwitchExternalPower() const;
    QString handlePowerKey() const;
    QString handleSuspendKey() const;
    QString ldleAction() const;
    QString wallMessage() const;
    ScheduledShutdownValue scheduledShutdown() const;
    uint nAutoVTs() const;
    quint64 holdoffTimeoutUSec() const;
    quint64 ldleActionUSec() const;
    quint64 ldleSinceHint() const;
    quint64 ldleSinceHintMonotonic() const;
    quint64 inhibitDelayMaxUSec() const;
    quint64 inhibitorsMax() const;
    quint64 nCurrentInhibitors() const;
    quint64 nCurrentSessions() const;
    quint64 runtimeDirectorySize() const;
    quint64 sessionMax() const;
    quint64 userStopDelayUSec() const;

signals:
    void errorMessageChanged(const QString &message);
    void PrepareForShutdown(const bool value);
    void PrepareForSleep(const bool value);
    void SeatNew(const QString &seat_id, const QString &seat_path);
    void SeatRemoved(const QString &seat_id, const QString &seat_path);
    void SessionNew(const QString &session_id, const QString &session_path);
    void SessionRemoved(const QString &session_id, const QString &session_path);
    void UserNew(const uint uid, const QString &path);
    void UserRemoved(const uint uid, const QString &path);
    // properties changed
    void KillExcludeUsersChanged(const QStringList &users);
    void KillOnlyUsersChanged(const QStringList &users);
    void DockedChanged(const bool value);
    void EnableWallMessagesChanged(const bool value);
    void LdleHintChanged(const bool value);
    void KillUserProcessesChanged(const bool value);
    void LidClosedChanged(const bool value);
    void OnExternalPowerChanged(const bool value);
    void PreparingForShutdownChanged(const bool value);
    void PreparingForSleepChanged(const bool value);
    void RebootToFirmwareSetupChanged(const bool value);
    void RemoveIPCChanged(const bool value);
    void BlockInhibitedChanged(const QString &value);
    void DelayInhibitedChanged(const QString &value);
    void HandleHibernateKeyChanged(const QString &value);
    void HandleLidSwitchChanged(const QString &value);
    void HandleLidSwitchDockedChanged(const QString &value);
    void HandleLidSwitchExternalPowerChanged(const QString &value);
    void HandlePowerKeyChanged(const QString &value);
    void HandleSuspendKeyChanged(const QString &value);
    void LdleActionChanged(const QString &value);
    void WallMessageChanged(const QString &value);
    void ScheduledShutdownChanged(const ScheduledShutdownValue &value);
    void NAutoVTsChanged(const uint value);
    void HoldoffTimeoutUSecChanged(const quint64 value);
    void LdleActionUSecChanged(const quint64 value);
    void LdleSinceHintChanged(const quint64 value);
    void LdleSinceHintMonotonicChanged(const quint64 value);
    void InhibitDelayMaxUSecChanged(const quint64 value);
    void InhibitorsMaxChanged(const quint64 value);
    void NCurrentInhibitorsChanged(const quint64 value);
    void NCurrentSessionsChanged(const quint64 value);
    void RuntimeDirectorySizeChanged(const quint64 value);
    void SessionMaxChanged(const quint64 value);
    void UserStopDelayUSecChanged(const quint64 value);
    // private signals
    void ScheduledShutdownChanged(const ScheduledShutdownValue_p &value);
    void SeatNew(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SeatRemoved(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SessionNew(const QString &session_id, const QDBusObjectPath &session_path);
    void SessionRemoved(const QString &session_id, const QDBusObjectPath &session_path);
    void UserNew(const uint uid, const QDBusObjectPath &path);
    void UserRemoved(const uint uid, const QDBusObjectPath &path);


public slots:
    QString lastError();
    void activateSession(const QString &session_id);
    void activateSessionOnSeat(const QString &session_id, const QString &seat_id);
    void attachDevice(const QString &seat_id, const QString &sysfs_path, const bool interactive);
    QString canHalt();
    QString canHibernate();
    QString canHybridSleep();
    QString canPowerOff();
    QString canReboot();
    QString canRebootParameter();
    QString canRebootToBootLoaderEntry();
    QString canRebootToBootLoaderMenu();
    QString canRebootToFirmwareSetup();
    QString canSuspend();
    QString canSuspendThenHibernate();
    bool cancelScheduledShutdown();
    std::tuple<QString,     // session_id
            QString,        // path
            QString,        // runtime_path
            int,            // fifo_fd
            uint,           // uid
            QString,        // seat_id
            uint,           // vtnr
            bool            // existing
            > createSession(uint uid, uint pid, const QString &service, const QString &type,
                    const QString &_class, const QString &desktop, const QString &seat_id,
                    uint vtnr, const QString &tty, const QString &display, const QString &remote,
                    const QString &remote_user, const QString &remote_host, const QList<SessionProperty> &properties);
    void flushDevices(const bool value);
    QString getSeat(const QString &seat_id);
    QString getSession(const QString &session_id);
    QString getSessionByPID(const uint pid);
    QString getUser(const uint uid);
    QString getUserByPID(const uint pid);
    void halt(const bool interactive);
    void hibernate(const bool interactive);
    void hybridSleep(const bool interactive);
    int inhibit(const QString &what, const QString &who, const QString &why, const QString &mode);
    void killSession(const QString &session_id, const QString &who, const int signal_number);
    void killUser(const uint uid, const int signal_number);
    QList<Inhibitor> listInhibitors();
    QList<Seat> listSeats();
    QList<Session> listSessions();
    QList<User> listUsers();
    void lockSession(const QString &session_id);
    void lockSessions();
    void powerOff(const bool interactive);
    void reboot(const bool interactive);
    void releaseSession(const QString &session_id);
    void scheduleShutdown(const QString type, qint64 usec);
    void setRebootTofirmwareSetup(const bool enbale);
    void setUserLinger(const uint uid, const bool enable, const bool interactive);
    void setWallMessage(const QString &message, const bool enable = false);
    void suspend(const bool interactive);
    void suspendThenHibernate(const bool interactive);
    void terminateSeat(const QString &seat_id);
    void terminateSession(const QString session_id);
    void terminateUser(const uint uid);
    void unlockSession(const QString &session_id);
    void unlockSessions();

private:
    QScopedPointer<Login1ManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1Manager)
};
LOGIN1_END_NAMESPACE
