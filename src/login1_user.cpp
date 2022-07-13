#include "login1_user.h"

#include "dbusinterface.h"
#include "login1_user_p.h"
#include <qobject.h>

LOGIN1_BEGIN_NAMESPACE
Login1User::Login1User(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new Login1UserPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    Q_D(Login1User);
    d->m_inter = new DBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

Login1User::~Login1User() {}
LOGIN1_END_NAMESPACE
