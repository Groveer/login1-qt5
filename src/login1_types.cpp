#include "include/login1_types.h"

LOGIN1_BEGIN_NAMESPACE

QDBusArgument &operator<< (QDBusArgument &arg, const ScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg << value.type;
    arg << value.usec;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, ScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg >> value.type;
    arg >> value.usec;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SessionProperty &property)
{
    arg.beginStructure();
    arg << property.name;
    arg << property.var;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SessionProperty &property)
{
    arg.beginStructure();
    arg >> property.name;
    arg >> property.var;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Inhibitor &inhibitor)
{
    arg.beginStructure();
    arg << inhibitor.what;
    arg << inhibitor.who;
    arg << inhibitor.why;
    arg << inhibitor.mode;
    arg << inhibitor.uid;
    arg << inhibitor.pid;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Inhibitor &inhibitor)
{
    arg.beginStructure();
    arg >> inhibitor.what;
    arg >> inhibitor.who;
    arg >> inhibitor.why;
    arg >> inhibitor.mode;
    arg >> inhibitor.uid;
    arg >> inhibitor.pid;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Seat &seat)
{
    arg.beginStructure();
    arg << seat.seat_id;
    arg << seat.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Seat &seat)
{
    arg.beginStructure();
    arg >> seat.seat_id;
    arg >> seat.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Session &session)
{
    arg.beginStructure();
    arg << session.session_id;
    arg << session.user_id;
    arg << session.user_name;
    arg << session.seat_id;
    arg << session.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Session &session)
{
    arg.beginStructure();
    arg >> session.session_id;
    arg >> session.user_id;
    arg >> session.user_name;
    arg >> session.seat_id;
    arg >> session.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const User &user)
{
    arg.beginStructure();
    arg << user.user_id;
    arg << user.user_name;
    arg << user.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, User &user)
{
    arg.beginStructure();
    arg >> user.user_id;
    arg >> user.user_name;
    arg >> user.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SeatPath &path)
{
    arg.beginStructure();
    arg << path.seat_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SeatPath &path)
{
    arg.beginStructure();
    arg >> path.seat_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SessionPath &path)
{
    arg.beginStructure();
    arg << path.session_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SessionPath &path)
{
    arg.beginStructure();
    arg >> path.session_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const UserPath &path)
{
    arg.beginStructure();
    arg << path.user_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, UserPath &path)
{
    arg.beginStructure();
    arg >> path.user_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

void ScheduledShutdownValue::registerMetaType()
{
    qRegisterMetaType<ScheduledShutdownValue>("ScheduledShutdownValue");
    qDBusRegisterMetaType<ScheduledShutdownValue>();
}

void SessionProperty::registerMetaType()
{
    qRegisterMetaType<SessionProperty>("SessionProperty");
    qDBusRegisterMetaType<SessionProperty>();
}

void Inhibitor::registerMetaType()
{
    qRegisterMetaType<Inhibitor>("Inhibitor");
    qDBusRegisterMetaType<Inhibitor>();
}

void Seat::registerMetaType()
{
    qRegisterMetaType<Seat>("Seat");
    qDBusRegisterMetaType<Seat>();
}

void Session::registerMetaType()
{
    qRegisterMetaType<Session>("Session");
    qDBusRegisterMetaType<Session>();
}

void User::registerMetaType()
{
    qRegisterMetaType<User>("User");
    qDBusRegisterMetaType<User>();
}

void SeatPath::registerMetaType()
{
    qRegisterMetaType<SeatPath>("SeatPath");
    qDBusRegisterMetaType<SeatPath>();
}

void SessionPath::registerMetaType()
{
    qRegisterMetaType<SessionPath>("SessionPath");
    qDBusRegisterMetaType<SessionPath>();
}

void UserPath::registerMetaType()
{
    qRegisterMetaType<UserPath>("UserPath");
    qDBusRegisterMetaType<UserPath>();
}

LOGIN1_END_NAMESPACE
