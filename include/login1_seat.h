#pragma once

#include <qobject.h>

#include "namespace.h"
#include "login1_types.h"

LOGIN1_BEGIN_NAMESPACE

class Login1SeatPrivate;

class Login1Seat : public QObject
{
    Q_OBJECT
public:
    explicit Login1Seat(const QString &path, QObject *parent = nullptr);
    virtual ~Login1Seat();

    Q_PROPERTY(QList<SessionPath> Sessions READ sessions NOTIFY SessionsChanged)
    Q_PROPERTY(bool CanGraphical READ canGraphical  NOTIFY CanGraphicalChanged)
    Q_PROPERTY(bool CanTTY READ canTTY NOTIFY CanTTYChanged)
    Q_PROPERTY(bool IdleHint READ idleHint NOTIFY IdleHintChanged)
    Q_PROPERTY(QString Id READ id NOTIFY IdChanged)
    Q_PROPERTY(SessionPath ActiveSession READ activeSession NOTIFY ActiveSessionChanged)
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint NOTIFY IdleSinceHintChanged)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic NOTIFY IdleSinceHintMonotonicChanged)

    bool canGraphical();
    bool canTTY();
    bool idleHint();
    QList<SessionPath> sessions();
    QString id();
    SessionPath activeSession();
    quint64 idleSinceHint();
    quint64 idleSinceHintMonotonic();

signals:
    void errorMessageChanged(const QString &message);
// properties changed
    void SessionsChanged(const QList<SessionPath> &value);
    void CanGraphicalChanged(const bool value);
    void CanTTYChanged(const bool value);
    void IdleHintChanged(const bool value);
    void IdChanged(const QString &value);
    void ActiveSessionChanged(const SessionPath &value);
    void IdleSinceHintChanged(const quint64 value);
    void IdleSinceHintMonotonicChanged(const quint64 value);

public slots:
    void activateSession(const QString & session_id);
    void switchTo(const uint vtnr);
    void switchToNext();
    void switchToPrevious();
    void terminate();

private:
    QScopedPointer<Login1SeatPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1Seat)
};
LOGIN1_END_NAMESPACE
