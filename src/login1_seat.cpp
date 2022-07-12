#include "login1_seat.h"

#include "dbusinterface.h"
#include "login1_seat_p.h"
#include <qobject.h>

LOGIN1_BEGIN_NAMESPACE
Login1Seat::Login1Seat(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1SeatPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    Q_D(Login1Seat);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

Login1Seat::~Login1Seat() {}
LOGIN1_END_NAMESPACE
