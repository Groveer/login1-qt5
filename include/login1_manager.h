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

    Q_PROPERTY(QStringList KillExcludeUsers READ killExcludeUsers)
    Q_PROPERTY(QStringList KillOnlyUsers READ killOnlyUsers)
    Q_PROPERTY(bool Docked READ docked)
    Q_PROPERTY(bool EnableWallMessages READ enableWallMessages WRITE setEnableWallMessages);
    Q_PROPERTY(bool IdleHint READ idleHint);
    Q_PROPERTY(bool KillUserProcesses READ killUserProcesses);
    Q_PROPERTY(bool LidClosed READ lidClosed);
    Q_PROPERTY(bool OnExternalPower READ onExternalPower);
    Q_PROPERTY(bool PreparingForShutdown READ preparingForShutdown);
    Q_PROPERTY(bool PreparingForSleep READ preparingForSleep);
    Q_PROPERTY(bool RebootToFirmwareSetup READ rebootToFirmwareSetup);
    Q_PROPERTY(bool RemoveIPC READ removeIPC);
    Q_PROPERTY(QString BlockInhibited READ blockInhibited);
    Q_PROPERTY(QString DelayInhibited READ delayInhibited);
    Q_PROPERTY(QString HandleHibernateKey READ handleHibernateKey);
    Q_PROPERTY(QString HandleLidSwitch READ handleLidSwitch);
    Q_PROPERTY(QString HandleLidSwitchDocked READ handleLidSwitchDocked);
    Q_PROPERTY(QString HandleLidSwitchExternalPower READ handleLidSwitchExternalPower);
    Q_PROPERTY(QString HandlePowerKey READ handlePowerKey);
    Q_PROPERTY(QString HandleSuspendKey READ handleSuspendKey);
    Q_PROPERTY(QString IdleAction READ idleAction);
    Q_PROPERTY(QString WallMessage READ wallMessage WRITE setWallMessage);
    Q_PROPERTY(ScheduledShutdownValue ScheduledShutdown READ scheduledShutdown);
    Q_PROPERTY(uint NAutoVTs READ nAutoVTs);
    Q_PROPERTY(quint64 HoldoffTimeoutUSec READ holdoffTimeoutUSec);
    Q_PROPERTY(quint64 IdleActionUSec READ idleActionUSec);
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(quint64 InhibitDelayMaxUSec READ inhibitDelayMaxUSec);
    Q_PROPERTY(quint64 InhibitorsMax READ inhibitorsMax);
    Q_PROPERTY(quint64 NCurrentInhibitors READ nCurrentInhibitors);
    Q_PROPERTY(quint64 NCurrentSessions READ nCurrentSessions);
    Q_PROPERTY(quint64 RuntimeDirectorySize READ runtimeDirectorySize);
    Q_PROPERTY(quint64 SessionMax READ sessionMax);
    Q_PROPERTY(quint64 UserStopDelayUSec READ userStopDelayUSec);

    QStringList killExcludeUsers() const;
    QStringList killOnlyUsers() const;
    bool docked() const;
    bool enableWallMessages() const;
    void setEnableWallMessages(const bool enable);
    bool idleHint() const;
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
    QString idleAction() const;
    QString wallMessage() const;
    ScheduledShutdownValue scheduledShutdown() const;
    uint nAutoVTs() const;
    quint64 holdoffTimeoutUSec() const;
    quint64 idleActionUSec() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
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
    // private signals
    void ScheduledShutdownChanged(const ScheduledShutdownValue_p &value);
    void SeatNew(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SeatRemoved(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SessionNew(const QString &session_id, const QDBusObjectPath &session_path);
    void SessionRemoved(const QString &session_id, const QDBusObjectPath &session_path);
    void UserNew(const uint uid, const QDBusObjectPath &path);
    void UserRemoved(const uint uid, const QDBusObjectPath &path);


public slots:
    QString lastError() const;
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
