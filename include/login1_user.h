#pragma once

#include <qobject.h>

#include "namespace.h"
#include "login1_types.h"

LOGIN1_BEGIN_NAMESPACE

class Login1UserPrivate;

class Login1User : public QObject
{
    Q_OBJECT
public:
    explicit Login1User(const QString &path, QObject *parent = nullptr);
    virtual ~Login1User();

    Q_PROPERTY(QList<SessionPath> Sessions READ sessions NOTIFY SessionsChanged)
    Q_PROPERTY(bool IdleHint READ idleHint NOTIFY IdleHintChanged)
    Q_PROPERTY(bool Linger READ linger NOTIFY LingerChanged)
    Q_PROPERTY(QString Name READ name NOTIFY NameChanged)
    Q_PROPERTY(QString RuntimePath READ runtimePath NOTIFY RuntimePathChanged)
    Q_PROPERTY(QString Service READ service NOTIFY ServiceChanged)
    Q_PROPERTY(QString Slice READ slice NOTIFY SliceChanged)
    Q_PROPERTY(QString State READ state NOTIFY StateChanged)
    Q_PROPERTY(SessionPath Display READ display NOTIFY DisplayChanged)
    Q_PROPERTY(uint GID READ GID NOTIFY GIDChanged)
    Q_PROPERTY(uint UID READ UID NOTIFY UIDChanged)
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint NOTIFY IdleSinceHintChanged)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic NOTIFY IdleSinceHintMonotonicChanged)
    Q_PROPERTY(quint64 Timestamp READ timestamp NOTIFY TimestampChanged)
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic NOTIFY TimestampMonotonicChanged)

    QList<SessionPath> sessions() const;
    bool idleHint() const;
    bool linger() const;
    QString name() const;
    QString runtimePath() const;
    QString service() const;
    QString slice() const;
    QString state() const;
    SessionPath display() const;
    uint GID() const;
    uint UID() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

signals:
    void errorMessageChanged(const QString &message);
    void SessionsChanged(const QList<SessionPath> &sessions);
    void IdleHintChanged(const bool value);
    void LingerChanged(const bool value);
    void NameChanged(const QString &name);
    void RuntimePathChanged(const QString &path);
    void ServiceChanged(const QString &service);
    void SliceChanged(const QString &slice);
    void StateChanged(const QString &state);
    void DisplayChanged(const SessionPath &path);
    void GIDChanged(const uint gid);
    void UIDChanged(const uint uid);
    void IdleSinceHintChanged(const quint64 value);
    void IdleSinceHintMonotonicChanged(const quint64 value);
    void TimestampChanged(const quint64 value);
    void TimestampMonotonicChanged(const quint64 value);

public slots:
    QString lastError();
    void kill(const int signal_number);
    void terminate();

private:
    QScopedPointer<Login1UserPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1User)
};
LOGIN1_END_NAMESPACE
