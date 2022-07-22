#pragma once

#include <qobject.h>

#include "namespace.h"
#include "login1_types.h"
#include "src/login1_types_p.h"

LOGIN1_BEGIN_NAMESPACE

class Login1SeatPrivate;

class Login1Seat : public QObject
{
    Q_OBJECT
public:
    explicit Login1Seat(const QString &path, QObject *parent = nullptr);
    virtual ~Login1Seat();

    Q_PROPERTY(QList<SessionPath> Sessions READ sessions)
    Q_PROPERTY(bool CanGraphical READ canGraphical)
    Q_PROPERTY(bool CanTTY READ canTTY)
    Q_PROPERTY(bool IdleHint READ idleHint)
    Q_PROPERTY(QString Id READ id)
    Q_PROPERTY(SessionPath ActiveSession READ activeSession)
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic)

    bool canGraphical() const;
    bool canTTY() const;
    bool idleHint() const;
    QList<SessionPath> sessions() const;
    QString id() const;
    SessionPath activeSession() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;

signals:
    void errorMessageChanged(const QString &message);
    // private signals
    void SessionsChanged(const QList<SessionPath_p> &value);
    void ActiveSessionChanged(const SessionPath_p &value);

public slots:
    QString lastError() const;
    void activateSession(const QString &session_id);
    void switchTo(const uint vtnr);
    void switchToNext();
    void switchToPrevious();
    void terminate();

private:
    QScopedPointer<Login1SeatPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1Seat)
};
LOGIN1_END_NAMESPACE
