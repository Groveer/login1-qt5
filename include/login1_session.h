#pragma once

#include <qobject.h>

#include "login1_types.h"
#include "src/login1_types_p.h"
#include "namespace.h"

LOGIN1_BEGIN_NAMESPACE

class Login1SessionPrivate;

class Login1Session : public QObject
{
    Q_OBJECT
public:
    explicit Login1Session(const QString &path, QObject *parent = nullptr);
    virtual ~Login1Session();
    Q_PROPERTY(bool Active READ active NOTIFY ActiveChanged)
    Q_PROPERTY(bool IdleHint READ idleHint NOTIFY IdleHintChanged)
    Q_PROPERTY(bool LockedHint READ lockedHint NOTIFY LockedHintChanged)
    Q_PROPERTY(bool Remote READ remote NOTIFY RemoteChanged)
    Q_PROPERTY(QString Class READ _class NOTIFY ClassChanged)
    Q_PROPERTY(QString Desktop READ desktop NOTIFY DesktopChanged)
    Q_PROPERTY(QString Display READ display NOTIFY DisplayChanged)
    Q_PROPERTY(QString Id READ id NOTIFY IdChanged)
    Q_PROPERTY(QString Name READ name NOTIFY NameChanged)
    Q_PROPERTY(QString RemoteHost READ remoteHost NOTIFY RemoteHostChanged)
    Q_PROPERTY(QString RemoteUser READ remoteUser NOTIFY RemoteUserChanged)
    Q_PROPERTY(QString Scope READ scope NOTIFY ScopeChanged)
    Q_PROPERTY(QString Service READ service NOTIFY ServiceChanged)
    Q_PROPERTY(QString State READ state NOTIFY StateChanged)
    // Why TTY?
    Q_PROPERTY(QString TTY READ tty NOTIFY TTYChanged)
    Q_PROPERTY(QString Type READ type NOTIFY TypeChanged)

    Q_PROPERTY(SeatPath Seat READ seat NOTIFY SeatChanged)
    Q_PROPERTY(UserPath User READ user NOTIFY UserChanged)

    Q_PROPERTY(uint Audit READ audit NOTIFY AuditChanged)
    Q_PROPERTY(uint Leader READ leader NOTIFY LeaderChanged)
    Q_PROPERTY(uint VTNr READ vtnr NOTIFY VTNrChanged)

    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint NOTIFY IdleSinceHintChanged)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic NOTIFY IdleSinceHintMonotonicChanged)
    Q_PROPERTY(quint64 Timestamp READ timestamp NOTIFY TimestampChanged)
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic NOTIFY TimestampMonotonicChanged)

    bool active() const;
    bool idleHint() const;
    bool lockedHint() const;
    bool remote() const;
    QString _class() const;
    QString desktop() const;
    QString display() const;
    QString id() const;
    QString name() const;
    QString remoteHost() const;
    QString remoteUser() const;
    QString scope() const;
    QString service() const;
    QString state() const;
    QString tty() const;
    QString type() const;
    SeatPath seat() const;
    UserPath user() const;
    uint audit() const;
    uint leader() const;
    uint vtnr() const;

    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

signals:
    void Lock();
    void PauseDevice(const uint value, const uint device, const QString &location);
    void ResumeDevice(const uint value, const uint device, const int descriptor);
    void Unlock();
    void errorMessageChanged(const QString &message);
    // properties changed
    void ActiveChanged(const bool value);
    void IdleHintChanged(const bool value);
    void LockedHintChanged(const bool value);
    void RemoteChanged(const bool value);
    void ClassChanged(const QString &value);
    void DesktopChanged(const QString &value);
    void DisplayChanged(const QString &value);
    void IdChanged(const QString &value);
    void NameChanged(const QString &value);
    void RemoteHostChanged(const QString &value);
    void RemoteUserChanged(const QString &value);
    void ScopeChanged(const QString &value);
    void ServiceChanged(const QString &value);
    void StateChanged(const QString &value);
    void TTYChanged(const QString &value);
    void TypeChanged(const QString &value);
    void SeatChanged(const SeatPath &value);
    void UserChanged(const UserPath &value);
    void AuditChanged(const uint value);
    void LeaderChanged(const uint value);
    void VTNrChanged(const uint value);
    void IdleSinceHintChanged(const quint64 value);
    void IdleSinceHintMonotonicChanged(const quint64 value);
    void TimestampChanged(const quint64 value);
    void TimestampMonotonicChanged(const quint64 value);

    // private signals
    void SeatChanged(const SeatPath_p &value);
    void UserChanged(const UserPath_p &value);

public slots:
    void activate();
    void kill(const QString who, const uint signal_number);
    void lock();
    void pauseDeviceComplete(const uint major, const uint minor);
    void releaseControl();
    void releaseDevice(const uint manjor, const uint minor);
    void setBrightness(const QString &subsystem, const QString &name, const uint brightness);
    void setIdleHint(const bool idle);
    void setLockedHint(const bool locked);
    void setType(const QString &type);
    void takeControl(const bool force);
    std::tuple<int,  // fd
               bool  // inactive
               >
    takeDevice(uint manjor, uint minor);
    void terminate();
    void unlock();

private:
    QScopedPointer<Login1SessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1Session)
};
LOGIN1_END_NAMESPACE
